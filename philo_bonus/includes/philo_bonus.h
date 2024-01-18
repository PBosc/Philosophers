/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pibosc <pibosc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 16:49:44 by pibosc            #+#    #+#             */
/*   Updated: 2024/01/18 17:05:55 by pibosc           ###   ########.fr       */
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
}						t_vars;

#endif