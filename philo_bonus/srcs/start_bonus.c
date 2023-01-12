/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igeorge <igeorge@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 20:12:11 by igeorge           #+#    #+#             */
/*   Updated: 2022/09/08 14:30:30 by igeorge          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	print_end_msg(t_main *instance)
{
	printf("All philosophers have finished eating ");
	printf("%d times.\n", instance->nbr_must_eat);
}

static void	exit_philo(t_main *instance, int last_philo)
{
	int	i_philo;
	int	status;

	i_philo = -1;
	while (++i_philo < last_philo)
	{
		if (waitpid(-1, &status, 0) < 0)
		{
			destroy_fork(instance, last_philo);
			destroy_sem(instance);
			error_msg(WAITPID_ERROR);
		}
		if (WEXITSTATUS(status) == EXIT_FAILURE)
		{
			destroy_fork(instance, last_philo);
			break ;
		}
	}
	if (i_philo == last_philo)
		print_end_msg(instance);
	destroy_sem(instance);
	exit(EXIT_SUCCESS);
}

void	run_philosophers(t_main *instance)
{
	int		i;

	i = -1;
	while (++i < instance->nbr_philo)
	{
		instance->philo[i].pid = fork();
		if (instance->philo[i].pid == -1)
		{
			destroy_fork(instance, i);
			destroy_sem(instance);
			error_msg(FORK_ERROR);
		}
		else if (instance->philo[i].pid == 0)
			run_fork(&instance->philo[i], instance);
	}
	exit_philo(instance, instance->nbr_philo);
}
