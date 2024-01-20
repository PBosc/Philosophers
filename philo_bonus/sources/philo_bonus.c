/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pibosc <pibosc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 19:17:52 by pibosc            #+#    #+#             */
/*   Updated: 2024/01/20 03:51:10 by pibosc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

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
			i = 0;
			while (i < vars->nb_philo)
			{
				kill(vars->pid_tab[i], SIGKILL);
				i++;
			}
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
	init_forks(&vars);
	sim_wait_end(&vars);
	return (0);
}
