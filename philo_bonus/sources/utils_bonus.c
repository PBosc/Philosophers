/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pibosc <pibosc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 19:58:34 by pibosc            #+#    #+#             */
/*   Updated: 2024/01/21 03:16:10 by pibosc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	get_time(void)
{
	struct timeval	tv;
	int				time;

	gettimeofday(&tv, NULL);
	time = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	return (time);
}

void	ft_usleep(int time)
{
	unsigned long	start;

	start = get_time();
	while ((int)(get_time() - start) < time)
		usleep(10);
}

int	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

long long	ft_atoi(const char *nptr)
{
	int			i;
	int			sign;
	long long	nb;

	i = 0;
	sign = 1;
	nb = 0;
	while ((nptr[i] >= '\a' && nptr[i] <= '\r') || nptr[i] == ' ')
		i++;
	if (nptr[i] == '-')
		sign = -1;
	if (nptr[i] == '+' || nptr[i] == '-')
		i++;
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		if (nb > LONG_MAX / 10)
			return (-1 * (sign == 1));
		nb = nb * 10 + nptr[i] - '0';
		if (nb < 0)
			return (-1 * (sign == 1));
		i++;
	}
	return (sign * nb);
}

void	philo_print(char *str, t_vars *vars)
{
	sem_wait(vars->print_sem);
	printf("%ld %d %s\n", get_time() - vars->start_time, vars->id, str);
	if (ft_strcmp(str, "died") != 0)
		sem_post(vars->print_sem);
}
