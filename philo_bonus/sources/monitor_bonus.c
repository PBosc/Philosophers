/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pibosc <pibosc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 02:22:21 by pibosc            #+#    #+#             */
/*   Updated: 2024/01/21 03:16:16 by pibosc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*thread_check_death(void *tmp)
{
	t_vars	*vars;

	vars = (t_vars *)tmp;
	while (1)
	{
		usleep(50);
		sem_wait(vars->eat_sem);
		if (get_time() - vars->last_eat > vars->ttd)
		{
			philo_print("died", vars);
			close_sem(vars);
			exit(0);
		}
		sem_post(vars->eat_sem);
	}
	return (NULL);
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
	while (i < vars->nb_philo)
	{
		sem_wait(vars->ate_enough);
		i++;
	}
	kill_processes(vars->pid_tab, vars->nb_philo);
	close_sem(vars);
	unlink_sems();
	free(vars->pid_tab);
	exit(0);
	return (0);
}

int	start_meals_monitor(t_vars *vars)
{
	pthread_t	meals_thread;

	if (vars->nb_max_meal != -1)
	{
		if (pthread_create(&meals_thread, NULL, &meals_monitor, vars) != 0)
			return (-1);
		pthread_detach(meals_thread);
	}
	return (0);
}

int	start_death_monitor(t_vars *vars)
{
	pthread_t	death_thread;
	static char	sem_name[10] = "/died_000";

	sem_name[8] = vars->id % 10 + '0';
	sem_name[7] = (vars->id / 10) % 10 + '0';
	sem_name[6] = (vars->id / 100) % 10 + '0';
	sem_unlink(sem_name);
	vars->eat_sem = sem_open(sem_name, O_CREAT, 0660, 1);
	if (pthread_create(&death_thread, NULL, &thread_check_death, vars) != 0)
		return (-1);
	pthread_detach(death_thread);
	return (0);
}
