/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igeorge <igeorge@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 18:53:45 by igeorge           #+#    #+#             */
/*   Updated: 2022/09/08 17:13:38 by igeorge          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	error_time(t_philo *philo, t_main *instance)
{
	sem_wait(instance->write);
	philo->died = 1;
	error_msg(TIME_ERROR);
}

void	*run_thread(void *arg)
{
	t_main		*instance;
	long long	time;
	t_philo		*philo;

	philo = (t_philo *) arg;
	instance = philo->instance;
	while (1)
	{
		sem_wait(instance->check_meal);
		if (philo->last_meal == 0)
		{
			sem_post(instance->check_meal);
			return (NULL);
		}
		time = time_diff(philo->last_meal, timestamp());
		if (time < 0)
			error_time(philo, instance);
		else if (time >= (long long) instance->ttdie)
			print_death(philo, instance);
		sem_post(instance->check_meal);
	}
	return (NULL);
}
