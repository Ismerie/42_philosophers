/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igeorge <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 18:34:38 by igeorge           #+#    #+#             */
/*   Updated: 2022/09/02 18:34:38 by igeorge          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	destroy_sem(t_main *instance)
{
	sem_close(instance->check_meal);
	sem_close(instance->fork);
	sem_close(instance->write);
	sem_unlink("check_meal");
	sem_unlink("fork");
	sem_unlink("write");
	free(instance->philo);
}

void	destroy_fork(t_main *instance, int nbr_fork)
{
	int	i;

	i = -1;
	while (++i < nbr_fork)
		kill(instance->philo[i].pid, SIGTERM);
}
