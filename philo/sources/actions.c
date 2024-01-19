/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pibosc <pibosc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 10:28:47 by pibosc            #+#    #+#             */
/*   Updated: 2024/01/18 19:42:42 by pibosc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eat(t_philo *philo, t_vars *vars)
{
	print_eat(philo, vars);
	pthread_mutex_lock(&philo->last_eat_mutex);
	philo->last_eat = get_time();
	pthread_mutex_unlock(&philo->last_eat_mutex);
	++(philo->meal_number);
	if (philo->meal_number == vars->nb_max_meal)
	{
		pthread_mutex_lock(&vars->ate_mutex);
		++(vars->ate_enough);
		pthread_mutex_unlock(&vars->ate_mutex);
	}
	ft_usleep(vars->tte);
}

void	give_back_forks(t_philo *philo)
{
	if (philo->id % 2)
	{
		pthread_mutex_unlock(&philo->fork);
		pthread_mutex_unlock(&philo->next->fork);
	}
	else
	{
		pthread_mutex_unlock(&philo->next->fork);
		pthread_mutex_unlock(&philo->fork);
	}
}

void	take_forks(t_philo *philo, t_vars *vars)
{
	if (philo->id % 2)
	{
		pthread_mutex_lock(&philo->fork);
		print_fork(philo, vars);
		pthread_mutex_lock(&philo->next->fork);
		print_fork(philo, vars);
	}
	else
	{
		pthread_mutex_lock(&philo->next->fork);
		print_fork(philo, vars);
		pthread_mutex_lock(&philo->fork);
		print_fork(philo, vars);
	}
}
