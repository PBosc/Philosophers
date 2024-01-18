/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   management.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pibosc <pibosc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 10:57:41 by pibosc            #+#    #+#             */
/*   Updated: 2024/01/18 11:48:18 by pibosc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	stop_philos(t_vars *vars)
{
	int	must_end;

	pthread_mutex_lock(&vars->end_mutex);
	must_end = vars->end;
	pthread_mutex_unlock(&vars->end_mutex);
	pthread_mutex_lock(&vars->ate_mutex);
	if (vars->ate_enough >= vars->nb_philo)
		must_end = 1;
	pthread_mutex_unlock(&vars->ate_mutex);
	return (must_end);
}

int	monitor(t_philo *philo, t_vars *vars)
{
	t_philo	*tmp;

	tmp = philo;
	ft_usleep(vars->ttd * 1000);
	while (tmp->id < vars->nb_philo + 1)
	{
		pthread_mutex_lock(&tmp->eat_mutex);
		if ((int)(get_time() - tmp->last_eat) > vars->ttd)
		{
			pthread_mutex_unlock(&tmp->eat_mutex);
			pthread_mutex_lock(&vars->end_mutex);
			vars->end = 1;
			pthread_mutex_unlock(&vars->end_mutex);
			pthread_mutex_lock(&vars->print_mutex);
			printf("%ld %d died\n", get_time() - vars->start_time, tmp->id);
			pthread_mutex_unlock(&vars->print_mutex);
			return (1);
		}
		pthread_mutex_unlock(&tmp->eat_mutex);
		if (stop_philos(vars))
			return (1);
		tmp = tmp->next;
	}
	return (0);
}
