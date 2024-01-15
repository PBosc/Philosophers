/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pibosc <pibosc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 19:38:27 by pibosc            #+#    #+#             */
/*   Updated: 2024/01/15 18:12:28 by pibosc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eat(t_philo *philo)
{
	if (philo->is_dead)
		return ;
	if (philo->id == philo->nb_philo - 1)
	{
		pthread_mutex_lock(philo->fork_mutex);
		print_fork(philo);
		pthread_mutex_lock(philo->next->fork_mutex);
		print_fork(philo);
	}
	else
	{
		pthread_mutex_lock(philo->next->fork_mutex);
		print_fork(philo);
		pthread_mutex_lock(philo->fork_mutex);
		print_fork(philo);
	}
	pthread_mutex_lock(philo->eat_mutex);
	philo->last_eat = get_time();
	philo->nb_eat++;
	pthread_mutex_unlock(philo->eat_mutex);
	print_eat(philo);
	usleep(1000 * philo->time_to_eat);
	if (philo->id == philo->nb_philo - 1)
	{
		pthread_mutex_unlock(philo->fork_mutex);
		pthread_mutex_unlock(philo->next->fork_mutex);
	}
	else
	{
		pthread_mutex_unlock(philo->next->fork_mutex);
		pthread_mutex_unlock(philo->fork_mutex);
	}
}

void	psleep(t_philo *philo)
{
	if (philo->is_dead)
		return ;
	print_sleep(philo);
	usleep(1000 * philo->time_to_sleep);
}

void	think(t_philo *philo)
{
	if (philo->is_dead)
		return ;
	print_think(philo);
}

void	*routine(void *tmp)
{
	t_philo	*philo;

	philo = (t_philo *)tmp;
	while (1)
	{
		if (philo->is_dead)
			return (NULL);
		eat(philo);
		psleep(philo);
		think(philo);
	}
}

int	main(int argc, char const *argv[])
{
	t_philo	*philo;
	int		i;
	int		count_eat;

	if (argc != 5 && argc != 6)
	{
		printf("Error: wrong number of arguments\n");
		return (1);
	}
	if (argc == 5)
		count_eat = -1;
	else
		count_eat = ft_atoi(argv[5]);
	philo = init_philos(ft_atoi(argv[1]), ft_atoi(argv[4]), ft_atoi(argv[3]),
			ft_atoi(argv[2]), count_eat);
	init_mutex(philo);
	init_threads(philo);
	i = 0;
	while (1)
	{
		if (monitor(philo))
			break ;
	}
	while (i < ft_atoi(argv[1]))
	{
		pthread_join(philo->thread, NULL);
		philo = philo->next;
		i++;
	}
	return (0);
}
