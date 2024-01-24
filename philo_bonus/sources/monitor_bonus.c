/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pibosc <pibosc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 02:22:21 by pibosc            #+#    #+#             */
/*   Updated: 2024/01/24 02:29:14 by pibosc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*death_monitor(void *args)
{
	t_vars	*vars;

	vars = (t_vars *)args;
	while (1)
	{
		usleep(50);
		sem_wait(vars->death_sem);
		if (vars->end_thread)
			return (0);
		sem_wait(vars->eat_sem);
		if (get_time() - vars->last_eat >= vars->ttd)
		{
			philo_print("died", vars);
			vars->end = 1;
			sem_post(vars->eat_sem);
			sem_post(vars->forks);
			sem_post(vars->forking);
			return (0);
		}
		else
			sem_post(vars->eat_sem);
		sem_post(vars->death_sem);
	}
	return (0);
}

void	kill_processes(pid_t *pid_tab, int nb_philo)
{
	int		i;

	i = 0;
	while (i < nb_philo)
	{
		kill(pid_tab[i], SIGKILL);
		i++;
	}
}

void	*meals_monitor(void *tmp)
{
	int		i;
	t_vars	*vars;

	i = 0;
	vars = (t_vars *)tmp;
	ft_usleep(10);
	while (i < vars->nb_philo)
	{
		sem_wait(vars->ate_enough);
		i++;
	}
	kill_processes(vars->pid_tab, vars->nb_philo);
	return (0);
}

int	start_meals_monitor(t_vars *vars)
{
	if (vars->nb_max_meal != -1)
	{
		if (pthread_create(&vars->meals_thread,
				NULL, &meals_monitor, vars) != 0)
			return (-1);
		pthread_detach(vars->meals_thread);
	}
	return (0);
}

int	start_death_monitor(t_vars *vars)
{
	pthread_t	philo_thread;
	static char	sem_name[10] = "/died_000";

	sem_name[8] = vars->id % 10 + '0';
	sem_name[7] = (vars->id / 10) % 10 + '0';
	sem_name[6] = (vars->id / 100) % 10 + '0';
	sem_unlink(sem_name);
	vars->eat_sem = sem_open(sem_name, O_CREAT, 0660, 1);
	philo_thread = vars->monitor_death[vars->id - 1];
	pthread_create(&philo_thread, NULL, &death_monitor, vars);
	pthread_detach(philo_thread);
	free(vars->monitor_death);
	return (0);
}
