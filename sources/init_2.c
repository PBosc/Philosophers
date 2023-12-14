/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pibosc <pibosc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 19:40:20 by pibosc            #+#    #+#             */
/*   Updated: 2023/12/14 19:40:40 by pibosc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void init_mutex(t_philo *philo)
{
	t_philo *tmp;

	tmp = philo;
	while (tmp->id < tmp->nb_philo - 1)
	{
		tmp->fork_mutex = malloc(sizeof(pthread_mutex_t));
		pthread_mutex_init(tmp->fork_mutex, NULL);
		tmp->print_mutex = malloc(sizeof(pthread_mutex_t));
		pthread_mutex_init(tmp->print_mutex, NULL);
		tmp = tmp->next;
	}
}
