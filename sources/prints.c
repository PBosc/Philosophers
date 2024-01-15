/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prints.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pibosc <pibosc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 15:19:31 by pibosc            #+#    #+#             */
/*   Updated: 2024/01/15 15:55:37 by pibosc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_eat(t_philo *philo)
{
	pthread_mutex_lock(philo->print_mutex);
	if (!philo->is_dead)
		printf("%d %d is eating\n",
			philo->last_eat - philo->start_time, philo->id);
	pthread_mutex_unlock(philo->print_mutex);
}

void	print_fork(t_philo *philo)
{
	pthread_mutex_lock(philo->print_mutex);
	if (!philo->is_dead)
		printf("%d %d has taken a fork\n",
			get_time() - philo->start_time, philo->id);
	pthread_mutex_unlock(philo->print_mutex);
}

void	print_sleep(t_philo *philo)
{
	pthread_mutex_lock(philo->print_mutex);
	if (!philo->is_dead)
		printf("%d %d is sleeping\n",
			get_time() - philo->start_time, philo->id);
	pthread_mutex_unlock(philo->print_mutex);
}

void	print_think(t_philo *philo)
{
	pthread_mutex_lock(philo->print_mutex);
	if (!philo->is_dead)
		printf("%d %d is thinking\n",
			get_time() - philo->start_time, philo->id);
	pthread_mutex_unlock(philo->print_mutex);
}
