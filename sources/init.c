/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pibosc <pibosc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 19:56:18 by pibosc            #+#    #+#             */
/*   Updated: 2024/01/18 11:38:27 by pibosc           ###   ########.fr       */
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

t_philo	*create_philo(int id)
{
	t_philo	*philo;

	philo = malloc(sizeof(t_philo));
	if (!philo)
		return (NULL);
	philo->id = id;
	philo->is_eating = 0;
	philo->last_eat = 0;
	philo->meal_number = 0;
	philo->next = NULL;
	philo->prev = NULL;
	return (philo);
}

t_philo	*init_philos(t_vars *vars)
{
	t_philo	*philo;
	t_philo	*tmp;
	t_philo	*tmp2;
	int		i;

	i = 1;
	philo = NULL;
	tmp = NULL;
	while (i < vars->nb_philo + 1)
	{
		tmp2 = tmp;
		tmp = create_philo(i);
		if (!tmp)
			return (free_philos(philo, vars), NULL);
		tmp->prev = tmp2;
		philo_push_back(&philo, tmp);
		i++;
	}
	tmp = last_philo(philo);
	tmp->next = philo;
	philo->prev = tmp;
	return (philo);
}

int	init_threads(t_philo *philo, t_vars *vars)
{
	t_philo	*tmp;

	tmp = philo;
	while (tmp->id < vars->nb_philo)
	{
		if (pthread_create(&tmp->thread, NULL, &routine, (void *)tmp) != 0)
			return(printf("Error: pthread_create failed\n"), 1);
		tmp = tmp->next;
	}
	if (pthread_create(&tmp->thread, NULL, &routine, tmp) != 0)
			return(printf("Error: pthread_create failed\n"), 1);
	return (0);
}
