/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pibosc <pibosc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 19:53:59 by pibosc            #+#    #+#             */
/*   Updated: 2024/01/24 01:10:05 by pibosc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	take_forks(t_vars *vars)
{
	vars->end = 0;
	sem_wait(vars->forking);
	sem_wait(vars->forks);
	usleep(50);
	if (!vars->end)
		(sem_wait(vars->death_sem), sem_post(vars->death_sem));
	if (vars->end)
	{
		philo_print("died", vars);
		close_sem(vars);
		sem_close(vars->eat_sem);
		exit(0);
	}
	philo_print("has taken a fork", vars);
	sem_wait(vars->forks);
	if (vars->end)
	{
		philo_print("died", vars);
		close_sem(vars);
		sem_close(vars->eat_sem);
		exit(0);
	}
	philo_print("has taken a fork", vars);
	sem_post(vars->forking);
}

void	eat(t_vars *vars)
{
	sem_wait(vars->eat_sem);
	vars->last_eat = get_time();
	vars->meal_number++;
	philo_print("is eating", vars);
	if (vars->nb_max_meal != -1 && vars->meal_number == vars->nb_max_meal)
		sem_post(vars->ate_enough);
	sem_post(vars->eat_sem);
	ft_usleep(vars->tte);
	sem_post(vars->forks);
	sem_post(vars->forks);
}

void	sleeping(t_vars *vars)
{
	philo_print("is sleeping", vars);
	ft_usleep(vars->tts);
}

int	routine(t_vars *vars)
{
	vars->last_eat = vars->start_time;
	start_death_monitor(vars);
	sem_wait(vars->ate_enough);
	while (1)
	{
		sem_post(vars->death_sem);
		take_forks(vars);
		eat(vars);
		sleeping(vars);
		philo_print("is thinking", vars);
	}
	return (0);
}
