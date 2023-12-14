/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pibosc <pibosc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 19:56:18 by pibosc            #+#    #+#             */
/*   Updated: 2023/12/14 20:28:41 by pibosc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static t_philo	*last_philo(t_philo *philo)
{
	t_philo	*tmp;

	tmp = philo;
	while (tmp->next)
		tmp = tmp->next;
	return (tmp);
}

static void	philo_push_back(t_philo **philo, t_philo *new)
{
	t_philo	*tmp;

	if (!*philo)
	{
		*philo = new;
		return ;
	}
	tmp = *philo;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	new->prev = tmp;
}

static void	zero_values(t_philo *philo, int time_to_sleep, int time_to_eat,
		int time_to_die)
{
	t_philo	*tmp;

	tmp = philo;
	while (tmp->id < tmp->nb_philo - 1)
	{
		tmp->is_eating = 1;
		tmp->is_sleeping = 0;
		tmp->is_thinking = 0;
		tmp->is_dead = 0;
		tmp->nb_eat = 0;
		tmp->last_eat = 0;
		tmp = tmp->next;
		tmp->time_to_sleep = time_to_sleep;
		tmp->time_to_eat = time_to_eat;
		tmp->time_to_die = time_to_die;
	}
}

t_philo	*init_philos(int nb_philo, int time_to_sleep, int time_to_eat,
		int time_to_die)
{
	t_philo	*philo;
	t_philo	*tmp;
	int		i;

	i = 0;
	philo = NULL;
	while (i < nb_philo)
	{
		tmp = malloc(sizeof(t_philo));
		tmp->id = i;
		tmp->fork_mutex = NULL;
		tmp->print_mutex = NULL;
		tmp->next = NULL;
		tmp->prev = NULL;
		tmp->nb_philo = nb_philo;
		tmp->start_time = get_time();
		philo_push_back(&philo, tmp);
		i++;
	}
	zero_values(philo, time_to_sleep, time_to_eat, time_to_die);
	tmp = last_philo(philo);
	tmp->next = philo;
	philo->prev = tmp;
	return (philo);
}

void	init_threads(t_philo *philo)
{
	t_philo	*tmp;

	tmp = philo;
	while (tmp->id < tmp->nb_philo - 1)
	{
		if (pthread_create(&tmp->thread, NULL, &routine, (void *)tmp) != 0)
			printf("Error: pthread_create failed\n");
		tmp = tmp->next;
	}
	if (pthread_create(&tmp->thread, NULL, &routine, tmp) != 0)
		printf("Error: pthread_create failed\n");
}
