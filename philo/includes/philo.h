/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pibosc <pibosc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 19:38:24 by pibosc            #+#    #+#             */
/*   Updated: 2024/01/18 19:49:22 by pibosc           ###   ########.fr       */
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

typedef struct s_vars	t_vars;

typedef struct s_philo
{
	pthread_t			thread;
	pthread_mutex_t		fork;
	int					id;
	unsigned long		last_eat;
	pthread_mutex_t		last_eat_mutex;
	int					meal_number;
	int					is_eating;
	pthread_mutex_t		eat_mutex;
	struct s_philo		*next;
	struct s_philo		*prev;
	t_vars				*vars;
}				t_philo;

typedef struct s_vars
{
	int					nb_philo;
	long long			ttd;
	long long			tte;
	long long			tts;
	int					nb_max_meal;
	unsigned long		start_time;
	int					end;
	pthread_mutex_t		end_mutex;
	int					ate_enough;
	pthread_mutex_t		ate_mutex;
	t_philo				*philo;
}						t_vars;

t_philo		*init_philos(t_vars *vars);
int			ft_strlen(const char *s);
long long	ft_atoi(const char *nptr);
int			init_threads(t_philo *philo, t_vars *vars);
void		free_philos(t_philo *philo, t_vars *vars);
int			get_time(void);
void		*routine(void *philo);
void		init_mutex(t_philo *philo, t_vars *vars);
int			monitor(t_philo *philo, t_vars *vars);
void		*ft_calloc(size_t nmemb, size_t size);
void		print_eat(t_philo *philo, t_vars *vars);
void		print_fork(t_philo *philo, t_vars *vars);
void		print_sleep(t_philo *philo, t_vars *vars);
void		print_think(t_philo *philo, t_vars *vars);
int			stop_philos(t_vars *vars);
void		eat(t_philo *philo, t_vars *vars);
void		give_back_forks(t_philo *philo);
void		take_forks(t_philo *philo, t_vars *vars);
int			parsing(int ac, char **av, t_vars *vars);
int			init_vars(t_vars *vars);
void		free_philos(t_philo *philo, t_vars *vars);
void		destroy_mutex(t_vars *vars);
void		ft_usleep(int time);

#endif