/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prints.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pibosc <pibosc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 15:19:31 by pibosc            #+#    #+#             */
/*   Updated: 2024/01/18 19:33:55 by pibosc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_eat(t_philo *philo, t_vars *vars)
{
	pthread_mutex_lock(&vars->end_mutex);
	if (!vars->end)
		printf("%ld %d is eating\n",
			get_time() - vars->start_time, philo->id);
	pthread_mutex_unlock(&vars->end_mutex);
}

void	print_fork(t_philo *philo, t_vars *vars)
{
	pthread_mutex_lock(&vars->end_mutex);
	if (!vars->end)
		printf("%ld %d has taken a fork\n",
			get_time() - vars->start_time, philo->id);
	pthread_mutex_unlock(&vars->end_mutex);
}

void	print_sleep(t_philo *philo, t_vars *vars)
{
	pthread_mutex_lock(&vars->end_mutex);
	if (!vars->end)
		printf("%ld %d is sleeping\n",
			get_time() - vars->start_time, philo->id);
	pthread_mutex_unlock(&vars->end_mutex);
}

void	print_think(t_philo *philo, t_vars *vars)
{
	pthread_mutex_lock(&vars->end_mutex);
	if (!vars->end)
		printf("%ld %d is thinking\n",
			get_time() - vars->start_time, philo->id);
	pthread_mutex_unlock(&vars->end_mutex);
}
