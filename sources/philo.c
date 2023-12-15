/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pibosc <pibosc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 19:38:27 by pibosc            #+#    #+#             */
/*   Updated: 2023/12/15 23:06:21 by pibosc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eat(t_philo *philo)
{
	if (philo->id % 2)
	{
		pthread_mutex_lock(philo->fork_mutex);
		printf("%d: %d has taken a fork\n", get_time() - philo->start_time, philo->id);
		pthread_mutex_lock(philo->next->fork_mutex);
		printf("%d: %d has taken a fork\n", get_time() - philo->start_time, philo->id);
	}
	else
	{
		pthread_mutex_lock(philo->next->fork_mutex);
		printf("%d: %d has taken a fork\n", get_time() - philo->start_time, philo->id);
		pthread_mutex_lock(philo->fork_mutex);
		printf("%d: %d has taken a fork\n", get_time() - philo->start_time, philo->id);
	}
	philo->is_eating = 0;
	philo->is_sleeping = 1;
	philo->last_eat = get_time();
	philo->nb_eat++;
	printf("%d: %d is eating\n", philo->last_eat - philo->start_time, philo->id);
	usleep(1000 * philo->time_to_eat);
	pthread_mutex_unlock(philo->fork_mutex);
	pthread_mutex_unlock(philo->next->fork_mutex);
}

void	psleep(t_philo *philo)
{
	philo->is_sleeping = 0;
	philo->is_thinking = 1;
	printf("%d: %d is sleeping\n", get_time() - philo->start_time, philo->id);
	usleep(1000 * philo->time_to_sleep);
}

void	think(t_philo *philo)
{
	philo->is_thinking = 0;
	philo->is_eating = 1;
	printf("%d: %d is thinking\n", get_time() - philo->start_time, philo->id);
}

void	*routine(void *tmp)
{
	t_philo	*philo;

	philo = (t_philo *)tmp;
	while (1)
	{
		if (philo->is_dead)
			return (NULL);
		if (philo->is_eating)
			eat(philo);
		else if (philo->is_sleeping)
			psleep(philo);
		else if (philo->is_thinking)
			think(philo);
	}
}

int	main(int argc, char const *argv[])
{
	t_philo	*philo;
	int		i;

	if (argc != 5 && argc != 6)
	{
		printf("Error: wrong number of arguments\n");
		return (1);
	}
	philo = init_philos(ft_atoi(argv[1]), ft_atoi(argv[4]), ft_atoi(argv[3]),
			ft_atoi(argv[2]));
	init_mutex(philo);
	init_threads(philo);
	i = 0;
	while (i < ft_atoi(argv[1]))
	{
		pthread_join(philo->thread, NULL);
		philo = philo->next;
		i++;
	}
	return (0);
}
