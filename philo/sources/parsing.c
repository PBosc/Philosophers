/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pibosc <pibosc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 11:28:50 by pibosc            #+#    #+#             */
/*   Updated: 2024/01/18 16:09:06 by pibosc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	parsing(int ac, char **av, t_vars *vars)
{
	vars->nb_philo = ft_atoi(av[1]);
	vars->ttd = ft_atoi(av[2]);
	vars->tte = ft_atoi(av[3]);
	vars->tts = ft_atoi(av[4]);
	if (ac == 6)
		vars->nb_max_meal = ft_atoi(av[5]);
	else
		vars->nb_max_meal = -1;
	if (vars->nb_philo < 1 || vars->ttd > INT_MAX || vars->tte > INT_MAX
		|| vars->tts > INT_MAX || vars->nb_max_meal < -1 || ft_strlen(av[1]) > 11 || ft_strlen(av[2]) > 11 || ft_strlen(av[3]) > 11 || ft_strlen(av[4]) > 11 || (ac == 6 && ft_strlen(av[5]) > 11))
	{
		printf("Error: wrong arguments\n");
		return (1);
	}
	return (0);
}

void	single_philo(t_vars *vars)
{
	print_fork(vars->philo, vars);
	ft_usleep(vars->ttd);
	printf("%ld %d died\n", get_time() - vars->start_time, vars->philo->id);
}

int	init_vars(t_vars *vars)
{
	vars->start_time = get_time();
	vars->philo = init_philos(vars);
	if (!vars->philo)
		return (1);
	init_mutex(vars->philo, vars);
	vars->end = 0;
	vars->ate_enough = 0;
	if (vars->nb_philo == 1)
	{
		single_philo(vars);
		return (1);
	}
	if (init_threads(vars->philo, vars))
		return (1);
	return (0);
}
