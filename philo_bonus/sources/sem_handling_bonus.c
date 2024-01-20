/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sem_handling_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pibosc <pibosc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 20:12:55 by pibosc            #+#    #+#             */
/*   Updated: 2024/01/20 03:51:56 by pibosc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	unlink_sems(void)
{
	//int			i;
	//static char	sem_name[10] = "/died_000";

	//i = 0;
	sem_unlink("/forks");
	sem_unlink("/ate_enough");
	sem_unlink("/died");
	sem_unlink("/print");
	//while (i < vars->nb_philo)
	//{
	//	sem_name[8] = vars->id % 10 + '0';
	//	sem_name[7] = (vars->id / 10) % 10 + '0';
	//	sem_name[6] = (vars->id / 100) % 10 + '0';
	//	sem_unlink(sem_name);
	//	i++;
	//}
}

void	init_sem(t_vars	*vars)
{
	unlink_sems();
	vars->forks = sem_open("/forks", O_CREAT, 0660, vars->nb_philo);
	vars->ate_enough = sem_open("/ate_enough", O_CREAT, 0660, vars->nb_philo);
	vars->died = sem_open("/died", O_CREAT, 0660, vars->nb_philo);
	vars->print = sem_open("/print", O_CREAT, 0660, 1);
}

void	init_vars(t_vars *vars)
{
	vars->id = 1;
	vars->meal_number = 0;
	vars->start_time = get_time();
	vars->last_eat = get_time();
	vars->pid_tab = malloc(sizeof(int) * vars->nb_philo);
}

void	init_forks(t_vars *vars)
{
	pid_t	pid;

	vars->pid = fork();
	pid = vars->pid;
	if (vars->pid == 0)
	{
		routine(vars);
		exit(0);
	}
	else
	{
		vars->pid_tab[vars->id - 1] = vars->pid;
		if (vars->id < vars->nb_philo)
		{
			vars->id++;
			init_forks(vars);
		}
		waitpid(pid, NULL, 0);
	}
}