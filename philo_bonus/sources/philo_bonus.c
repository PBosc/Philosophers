/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pibosc <pibosc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 19:17:52 by pibosc            #+#    #+#             */
/*   Updated: 2024/01/21 03:07:07 by pibosc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	while (s1 && s2 && s1[i] && s2[i] && s1[i] == s2[i])
		++i;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

void	sim_wait_end(t_vars *vars)
{
	int	i;
	int	ret;

	i = 0;
	while (i < vars->nb_philo)
	{
		waitpid(-1, &ret, 0);
		if (WIFEXITED(ret))
		{
			kill_processes(vars->pid_tab, vars->nb_philo);
			break ;
		}
		++i;
	}
}

int	main(int argc, char **argv)
{
	t_vars	vars;

	if (argc != 5 && argc != 6)
	{
		printf("Error: wrong number of arguments\n");
		return (1);
	}
	if (parsing(argc, argv, &vars))
		return (1);
	init_vars(&vars);
	init_sem(&vars);
	start_meals_monitor(&vars);
	init_forks(&vars);
	sim_wait_end(&vars);
	return (0);
}
