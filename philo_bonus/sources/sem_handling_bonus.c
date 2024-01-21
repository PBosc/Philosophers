/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sem_handling_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pibosc <pibosc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 20:12:55 by pibosc            #+#    #+#             */
/*   Updated: 2024/01/21 03:15:56 by pibosc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	close_sem(t_vars *vars)
{
	sem_close(vars->forks);
	sem_close(vars->ate_enough);
	sem_close(vars->died);
	sem_close(vars->forking);
	sem_close(vars->print_sem);
}

void	unlink_sems(void)
{
	sem_unlink("/forks");
	sem_unlink("/ate_enough");
	sem_unlink("/died");
	sem_unlink("/forking");
	sem_unlink("/print_sem");
}

void	init_sem(t_vars	*vars)
{
	unlink_sems();
	vars->forks = sem_open("/forks", O_CREAT, 0660, vars->nb_philo);
	vars->ate_enough = sem_open("/ate_enough", O_CREAT, 0660, vars->nb_philo);
	vars->forking = sem_open("/forking", O_CREAT, 0660, 1);
	vars->print_sem = sem_open("/print_sem", O_CREAT, 0660, 1);
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

	while (vars->id < vars->nb_philo + 1)
	{
		vars->pid = fork();
		pid = vars->pid;
		if (pid != 0)
			vars->pid_tab[vars->id - 1] = pid;
		else
		{
			free(vars->pid_tab);
			routine(vars);
		}
		vars->id++;
	}
}
