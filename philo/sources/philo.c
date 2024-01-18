/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pibosc <pibosc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 19:38:27 by pibosc            #+#    #+#             */
/*   Updated: 2024/01/18 15:58:49 by pibosc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_usleep(int time)
{
	unsigned long	start;

	start = get_time();
	while ((int)(get_time() - start) < time)
		usleep(10);
}

void	*routine(void *tmp)
{
	t_philo	*philo;
	t_vars	*vars;

	philo = (t_philo *)tmp;
	vars = philo->vars;
	if (philo->id % 2 == 0)
		ft_usleep(500);
	while (!stop_philos(vars))
	{
		take_forks(philo, vars);
		eat(philo, vars);
		give_back_forks(philo);
		print_sleep(philo, vars);
		ft_usleep(vars->tts);
		print_think(philo, vars);
		if (vars->tte >= vars->tts)
			ft_usleep(vars->tte - vars->tts + 1);
	}
	return(NULL);
}

int	main(int argc, char **argv)
{
	t_philo	*philo;
	int		i;
	t_vars	vars;

	if (argc != 5 && argc != 6)
	{
		printf("Error: wrong number of arguments\n");
		return (1);
	}
	if (parsing(argc, argv, &vars))
		return (1);
	if (init_vars(&vars))
		return (destroy_mutex(&vars), free_philos(vars.philo, &vars), 1);
	while (1)
	{
		if (monitor(vars.philo, &vars))
			break ;
	}
	philo = vars.philo;
	i = 0;
	while (i < ft_atoi(argv[1]))
	{
		pthread_join(philo->thread, NULL);
		philo = philo->next;
		i++;
	}
	destroy_mutex(&vars);
	free_philos(vars.philo, &vars);
	return (0);
}
