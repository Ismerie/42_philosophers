/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igeorge <igeorge@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 18:59:10 by igeorge           #+#    #+#             */
/*   Updated: 2022/09/08 16:13:02 by igeorge          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static int	take_forks(t_philo *philo, t_main *instance)
{
	sem_wait(instance->fork);
	action_print(instance, philo, "has taken a fork");
	while (instance->nbr_philo < 2)
	{
		if (instance->nbr_philo > 2)
		{
			sem_post(instance->fork);
			return (0);
		}
	}
	sem_wait(instance->fork);
	action_print(instance, philo, "has taken a fork");
	return (1);
}

static void	run_eat(t_philo *philo, t_main *instance)
{
	if (!take_forks(philo, instance))
		return ;
	sem_wait(instance->check_meal);
	action_print(instance, philo, "is eating");
	philo->nbr_meal = philo->nbr_meal + 1;
	if (philo->nbr_meal != instance->nbr_must_eat)
		philo->last_meal = timestamp();
	else
		philo->last_meal = 0;
	sem_post(instance->check_meal);
	if (philo->died == 0)
		new_sleep(instance->tteat);
	sem_post(instance->fork);
	sem_post(instance->fork);
}

static void	run_sleep(t_philo *philo, t_main *instance)
{
	action_print(instance, philo, "is sleeping");
	new_sleep(instance->ttsleep);
	action_print(instance, philo, "is thinking");
}

void	exit_fork(t_philo *philo, int code)
{
	pthread_join(philo->tid, NULL);
	exit(code);
}

void	run_fork(t_philo *philo, t_main *instance)
{
	if (!instance->nbr_must_eat)
		exit(EXIT_SUCCESS);
	if (pthread_create(&philo->tid, NULL, run_thread, philo))
	{
		sem_wait(instance->write);
		error_msg(PTHREAD_ERROR);
	}
	if (philo->id % 2 == 0)
		run_sleep(philo, instance);
	while (philo->nbr_meal != instance->nbr_must_eat)
	{
		run_eat(philo, instance);
		if (philo->nbr_meal != instance->nbr_must_eat)
			run_sleep(philo, instance);
	}
	exit_fork(philo, EXIT_SUCCESS);
}
