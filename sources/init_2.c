/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pibosc <pibosc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 19:40:20 by pibosc            #+#    #+#             */
/*   Updated: 2024/01/15 18:04:44 by pibosc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void init_mutex(t_philo *philo)
{
	t_philo *tmp;

	tmp = philo;
	while (tmp->id < tmp->nb_philo)
	{
		tmp->fork_mutex = malloc(sizeof(pthread_mutex_t));
		pthread_mutex_init(tmp->fork_mutex, NULL);
		tmp->print_mutex = malloc(sizeof(pthread_mutex_t));
		pthread_mutex_init(tmp->print_mutex, NULL);
		tmp->eat_mutex = malloc(sizeof(pthread_mutex_t));
		pthread_mutex_init(tmp->eat_mutex, NULL);
		tmp = tmp->next;
	}
	tmp->fork_mutex = malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(tmp->fork_mutex, NULL);
	tmp->print_mutex = malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(tmp->print_mutex, NULL);
	tmp->eat_mutex = malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(tmp->eat_mutex, NULL);
}

void	stop_philos(t_philo *philo)
{
	t_philo	*tmp;

	tmp = philo;
	while (tmp->id < tmp->nb_philo)
	{
		tmp->is_dead = 1;
		pthread_mutex_destroy(tmp->fork_mutex);
		pthread_mutex_destroy(tmp->print_mutex);
		tmp = tmp->next;
	}
	tmp->is_dead = 1;
	pthread_mutex_destroy(tmp->fork_mutex);
	pthread_mutex_destroy(tmp->print_mutex);
}

int	monitor(t_philo *philo)
{
	t_philo	*tmp;
	int		done;

	tmp = philo;
	done = 0;
	usleep(philo->time_to_die * 1000);
	while (tmp->id < tmp->nb_philo + 1)
	{
		pthread_mutex_lock(tmp->eat_mutex);
		if (get_time() - tmp->last_eat > tmp->time_to_die)
		{
			pthread_mutex_unlock(tmp->eat_mutex);
			tmp->is_dead = 1;
			stop_philos(philo);
			pthread_mutex_lock(tmp->print_mutex);
			printf("%d %d died\n", get_time() - tmp->start_time, tmp->id);
			pthread_mutex_unlock(tmp->print_mutex);
			return (1);
		}
		pthread_mutex_unlock(tmp->eat_mutex);
		if (tmp->nb_eat != -1 && tmp->nb_eat == tmp->nb_eat_max)
		{
			done++;
			tmp->nb_eat++;
			if (done == tmp->nb_philo)
				return (stop_philos(philo), 1);
		}
		tmp = tmp->next;
	}
	return (0);
}
