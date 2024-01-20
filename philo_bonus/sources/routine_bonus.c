/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pibosc <pibosc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 19:53:59 by pibosc            #+#    #+#             */
/*   Updated: 2024/01/20 03:58:03 by pibosc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*thread_m(void *tmp)
{
	t_vars	*vars;

	ft_usleep(10);
	vars = (t_vars *)tmp;
	sem_wait(vars->died);
	sem_post(vars->died);
	exit(0);
	return (NULL);
}

void	*thread_check_death(void *tmp)
{
	t_vars	*vars;

	vars = (t_vars *)tmp;
	while (1)
	{
		ft_usleep(5);
		sem_wait(vars->eat_sem);
		if (get_time() - vars->last_eat > vars->ttd)
		{
			sem_post(vars->eat_sem);
			sem_post(vars->died);
			philo_print("died", vars);
			exit(0);
		}
		sem_post(vars->eat_sem);
	}
	return (NULL);
}

int	eat(t_vars *vars)
{
	if (vars->meal_number == vars->nb_max_meal)
	{
		sem_post(vars->ate_enough);
		return (1);
	}
	sem_wait(vars->forks);
	philo_print("has taken a fork", vars);
	sem_wait(vars->forks);
	philo_print("has taken a fork", vars);
	philo_print("is eating", vars);
	sem_wait(vars->eat_sem);
	vars->last_eat = get_time();
	sem_post(vars->eat_sem);
	ft_usleep(vars->tte);
	sem_post(vars->forks);
	sem_post(vars->forks);
	vars->meal_number++;
	return (0);
}

int	routine(t_vars *vars)
{
	//static char	sem_name[10] = "/died_000";

	//sem_name[8] = vars->id % 10 + '0';
	//sem_name[7] = (vars->id / 10) % 10 + '0';
	//sem_name[6] = (vars->id / 100) % 10 + '0';
	//sem_unlink(sem_name);
	//vars->died = sem_open(sem_name, O_CREAT, 0660, 1);
	sem_unlink("/eat_sem");
	vars->eat_sem = sem_open("/eat_sem", O_CREAT, 0660, 1);
	sem_wait(vars->died);
	pthread_create(&vars->monitor, NULL, (void *)thread_m, vars);
	pthread_create(&vars->monitor_death, NULL, (void *)thread_check_death, vars);
	while (1)
	{
		if (eat(vars))
			return (0);
		philo_print("is sleeping", vars);
		ft_usleep(vars->tts);
		philo_print("is thinking", vars);
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

int	monitor(t_vars *vars)
{
	int		i;

	i = 0;
	while (i < vars->nb_philo)
	{
		sem_wait(vars->ate_enough);
		i++;
	}
	kill_processes(vars->pid_tab, vars->nb_philo);
	return (0);
}
