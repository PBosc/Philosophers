/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   management.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pibosc <pibosc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 10:57:41 by pibosc            #+#    #+#             */
/*   Updated: 2024/01/24 01:29:20 by pibosc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	get_min_end(t_vars *vars)
{
	int	min;

	min = vars->tte;
	if (vars->nb_max_meal != -1)
		min *= vars->nb_max_meal;
	else
		min = vars->ttd;
	if (vars->ttd < min)
		min = vars->ttd;
	return (min);
}

int	stop_philos(t_vars *vars)
{
	int	ate_enough;

	pthread_mutex_lock(&vars->end_mutex);
	ate_enough = vars->end;
	pthread_mutex_unlock(&vars->end_mutex);
	pthread_mutex_lock(&vars->ate_mutex);
	if (vars->ate_enough >= vars->nb_philo)
		ate_enough = 1;
	pthread_mutex_unlock(&vars->ate_mutex);
	if (ate_enough)
	{
		pthread_mutex_lock(&vars->end_mutex);
		vars->end = 1;
		pthread_mutex_unlock(&vars->end_mutex);
	}
	return (ate_enough);
}

int	monitor(t_philo *philo, t_vars *vars)
{
	t_philo	*tmp;

	tmp = philo;
	ft_usleep(get_min_end(vars));
	while (tmp->id < vars->nb_philo + 1)
	{
		pthread_mutex_lock(&tmp->last_eat_mutex);
		if ((int)(get_time() - tmp->last_eat) > vars->ttd)
		{
			pthread_mutex_unlock(&tmp->last_eat_mutex);
			pthread_mutex_lock(&vars->end_mutex);
			vars->end = 1;
			pthread_mutex_unlock(&vars->end_mutex);
			printf("%ld %d died\n", get_time() - vars->start_time, tmp->id);
			return (1);
		}
		pthread_mutex_unlock(&tmp->last_eat_mutex);
		tmp = tmp->next;
		if (stop_philos(vars))
			return (1);
	}
	return (0);
}
