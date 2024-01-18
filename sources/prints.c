/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prints.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pibosc <pibosc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 15:19:31 by pibosc            #+#    #+#             */
/*   Updated: 2024/01/18 11:46:58 by pibosc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_eat(t_philo *philo, t_vars *vars)
{
	pthread_mutex_lock(&vars->end_mutex);
	pthread_mutex_lock(&vars->print_mutex);
	if (!vars->end)
		printf("%ld %d is eating\n",
			philo->last_eat - vars->start_time, philo->id);
	pthread_mutex_unlock(&vars->print_mutex);
	pthread_mutex_unlock(&vars->end_mutex);
}

void	print_fork(t_philo *philo, t_vars *vars)
{
	
	pthread_mutex_lock(&vars->end_mutex);
	pthread_mutex_lock(&vars->print_mutex);
	if (!vars->end)
		printf("%ld %d has taken a fork\n",
			philo->last_eat - vars->start_time, philo->id);
	pthread_mutex_unlock(&vars->print_mutex);
	pthread_mutex_unlock(&vars->end_mutex);
}

void	print_sleep(t_philo *philo, t_vars *vars)
{
	pthread_mutex_lock(&vars->end_mutex);
	pthread_mutex_lock(&vars->print_mutex);
	if (!vars->end)
		printf("%ld %d has taken a fork\n",
			philo->last_eat - vars->start_time, philo->id);
	pthread_mutex_unlock(&vars->print_mutex);
	pthread_mutex_unlock(&vars->end_mutex);
}

void	print_think(t_philo *philo, t_vars *vars)
{
	pthread_mutex_lock(&vars->end_mutex);
	pthread_mutex_lock(&vars->print_mutex);
	if (!vars->end)
		printf("%ld %d has taken a fork\n",
			philo->last_eat - vars->start_time, philo->id);
	pthread_mutex_unlock(&vars->print_mutex);
	pthread_mutex_unlock(&vars->end_mutex);
}
