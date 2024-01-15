/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pibosc <pibosc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 19:38:24 by pibosc            #+#    #+#             */
/*   Updated: 2024/01/15 15:33:49 by pibosc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <limits.h>
# include <unistd.h>

typedef struct s_philo {
	int				id;
	int				is_eating;
	int				is_sleeping;
	int				is_thinking;
	int				is_dead;
	int				nb_eat;
	int				last_eat;
	pthread_mutex_t	*fork_mutex;
	pthread_mutex_t	*print_mutex;
	pthread_mutex_t	*eat_mutex;
	struct s_philo	*next;
	struct s_philo	*prev;
	pthread_t		thread;
	int				nb_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				start_time;
	int				nb_eat_max;
}		t_philo;

t_philo	*init_philos(int nb_philo, int time_to_sleep,
			int time_to_eat, int time_to_die, int nb_eat_max);
int		ft_atoi(const char *nptr);
void	init_threads(t_philo *philo);
int		get_time(void);
void	*routine(void *philo);
void	init_mutex(t_philo *philo);
int		monitor(t_philo *philo);
void	*ft_calloc(size_t nmemb, size_t size);
void	print_eat(t_philo *philo);
void	print_fork(t_philo *philo);
void	print_sleep(t_philo *philo);
void	print_think(t_philo *philo);

#endif