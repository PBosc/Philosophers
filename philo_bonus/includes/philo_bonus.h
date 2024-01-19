/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pibosc <pibosc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 16:49:44 by pibosc            #+#    #+#             */
/*   Updated: 2024/01/19 22:04:49 by pibosc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <limits.h>
# include <unistd.h>
# include <semaphore.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <signal.h>

typedef struct s_vars
{
	pid_t				pid;
	int					id;
	int					meal_number;
	int					nb_philo;
	int					*pid_tab;
	unsigned long		ttd;
	unsigned long		tte;
	unsigned long		tts;
	int					nb_max_meal;
	unsigned long		start_time;
	unsigned long		last_eat;
	sem_t				*forks;
	sem_t				*ate_enough;
	sem_t				*died;
	pthread_t			monitor;
}						t_vars;

int			parsing(int ac, char **av, t_vars *vars);
int			get_time(void);
void		ft_usleep(int time);
void		init_sem(t_vars	*vars);
void		init_vars(t_vars *vars);
void		init_forks(t_vars *vars);
long long	ft_atoi(const char *nptr);
int			ft_strlen(const char *s);
int			routine(t_vars *vars);

#endif