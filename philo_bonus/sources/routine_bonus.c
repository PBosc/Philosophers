/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pibosc <pibosc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 19:53:59 by pibosc            #+#    #+#             */
/*   Updated: 2024/01/19 23:15:18 by pibosc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*thread_m(void *tmp)
{
	t_vars	*vars;

	vars = (t_vars *)tmp;
	sem_wait(vars->died);
	sem_close(vars->ate_enough);
	sem_close(vars->forks);
	sem_close(vars->died);
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
	printf("%ld %d has taken a fork\n", get_time() - vars->start_time, vars->id);
	sem_wait(vars->forks);
	printf("%ld %d has taken a fork\n", get_time() - vars->start_time, vars->id);
	printf("%ld %d is eating\n", get_time() - vars->start_time, vars->id);
	vars->last_eat = get_time();
	ft_usleep(vars->tte);
	sem_post(vars->forks);
	sem_post(vars->forks);
	vars->meal_number++;
	return (0);
}

int	routine(t_vars *vars)
{
	static char	sem_name[10] = "/died_000";

	sem_name[8] = vars->id % 10 + '0';
	sem_name[7] = (vars->id / 10) % 10 + '0';
	sem_name[6] = (vars->id / 100) % 10 + '0';
	sem_unlink(sem_name);
	vars->died = sem_open(sem_name, O_CREAT, 0660, 1);
	sem_wait(vars->died);
	pthread_create(&vars->monitor, NULL, (void *)thread_m, vars);
	while (1)
	{
		if (get_time() - vars->last_eat > vars->ttd)
		{
			printf("%ld %d died\n", get_time() - vars->start_time, vars->id);
			sem_post(vars->died);
			return (0);
		}
		if (eat(vars))
			return (0);
		printf("%ld %d is sleeping\n", get_time() - vars->start_time, vars->id);
		ft_usleep(vars->tts);
		printf("%ld %d is thinking\n", get_time() - vars->start_time, vars->id);
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
