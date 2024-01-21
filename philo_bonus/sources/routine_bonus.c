/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pibosc <pibosc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 19:53:59 by pibosc            #+#    #+#             */
/*   Updated: 2024/01/21 03:12:18 by pibosc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	take_forks(t_vars *vars)
{
	sem_wait(vars->forking);
	sem_wait(vars->forks);
	philo_print("has taken a fork", vars);
	sem_wait(vars->forks);
	philo_print("has taken a fork", vars);
	sem_post(vars->forking);
}

void	eat(t_vars *vars)
{
	sem_wait(vars->eat_sem);
	vars->last_eat = get_time();
	sem_post(vars->eat_sem);
	philo_print("is eating", vars);
	ft_usleep(vars->tte);
	sem_post(vars->forks);
	sem_post(vars->forks);
	if (vars->nb_max_meal != -1 && vars->meal_number == vars->nb_max_meal)
		sem_post(vars->ate_enough);
}

void	sleeping(t_vars *vars)
{
	philo_print("is sleeping", vars);
	ft_usleep(vars->tts);
}

int	routine(t_vars *vars)
{
	vars->start_time = get_time();
	vars->last_eat = vars->start_time;
	start_death_monitor(vars);
	if (vars->id % 2)
		ft_usleep(1);
	while (1)
	{
		take_forks(vars);
		eat(vars);
		sleeping(vars);
		philo_print("is thinking", vars);
		sem_wait(vars->eat_sem);
		if (get_time() - vars->last_eat > vars->ttd)
		{
			philo_print("died", vars);
			close_sem(vars);
			exit(0);
		}
		sem_post(vars->eat_sem);
	}
	return (0);
}
