/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pibosc <pibosc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 02:22:21 by pibosc            #+#    #+#             */
/*   Updated: 2024/01/23 00:38:00 by pibosc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	kill_processes(pid_t *pid_tab, int nb_philo)
{
	int		i;

	i = 0;
	while (i < nb_philo)
	{
		kill(pid_tab[i], SIGKILL);
		i++;
	}
}

void	*meals_monitor(void *tmp)
{
	int		i;
	t_vars	*vars;

	i = 0;
	vars = (t_vars *)tmp;
	ft_usleep(10);
	while (i < vars->nb_philo)
	{
		sem_wait(vars->ate_enough);
		i++;
	}
	kill_processes(vars->pid_tab, vars->nb_philo);
	return (0);
}

int	start_meals_monitor(t_vars *vars)
{
	if (vars->nb_max_meal != -1)
	{
		if (pthread_create(&vars->meals_thread, NULL, &meals_monitor, vars) != 0)
			return (-1);
		pthread_detach(vars->meals_thread);
	}
	return (0);
}

int	start_death_monitor(t_vars *vars)
{
	static char	sem_name[10] = "/died_000";

	sem_name[8] = vars->id % 10 + '0';
	sem_name[7] = (vars->id / 10) % 10 + '0';
	sem_name[6] = (vars->id / 100) % 10 + '0';
	sem_unlink(sem_name);
	vars->eat_sem = sem_open(sem_name, O_CREAT, 0660, 1);
	return (0);
}
