/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pibosc <pibosc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 19:40:20 by pibosc            #+#    #+#             */
/*   Updated: 2024/01/18 19:50:26 by pibosc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_mutex_p(t_philo *philo, t_vars *vars)
{
	t_philo	*tmp;

	tmp = philo;
	while (tmp->id < vars->nb_philo)
	{
		pthread_mutex_init(&tmp->last_eat_mutex, NULL);
		pthread_mutex_init(&tmp->fork, NULL);
		pthread_mutex_init(&tmp->eat_mutex, NULL);
		tmp = tmp->next;
	}
	pthread_mutex_init(&tmp->last_eat_mutex, NULL);
	pthread_mutex_init(&tmp->fork, NULL);
	pthread_mutex_init(&tmp->eat_mutex, NULL);
}

void	init_mutex(t_philo *philo, t_vars *vars)
{
	pthread_mutex_init(&vars->end_mutex, NULL);
	pthread_mutex_init(&vars->ate_mutex, NULL);
	init_mutex_p(philo, vars);
}

void	destroy_mutex_p(t_philo *philo, t_vars *vars)
{
	t_philo	*tmp;

	tmp = philo;
	while (tmp->id < vars->nb_philo)
	{
		pthread_mutex_destroy(&tmp->last_eat_mutex);
		pthread_mutex_destroy(&tmp->fork);
		pthread_mutex_destroy(&tmp->eat_mutex);
		tmp = tmp->next;
	}
	pthread_mutex_destroy(&tmp->last_eat_mutex);
	pthread_mutex_destroy(&tmp->fork);
	pthread_mutex_destroy(&tmp->eat_mutex);
}

void	destroy_mutex(t_vars *vars)
{
	pthread_mutex_destroy(&vars->ate_mutex);
	pthread_mutex_destroy(&vars->end_mutex);
	destroy_mutex_p(vars->philo, vars);
}
