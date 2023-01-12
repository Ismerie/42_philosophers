/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igeorge <igeorge@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 14:53:17 by igeorge           #+#    #+#             */
/*   Updated: 2022/09/08 14:22:52 by igeorge          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	philo_action_eat(t_philo *philo, t_main *instance)
{
	pthread_mutex_lock(&(instance->check_meal[(philo->id) - 1]));
	action_print(instance, philo->id, "is eating");
	philo->last_meal = timenow();
	(philo->nbr_meal)++;
	if (philo->nbr_meal == instance->nbr_must_eat)
		philo->last_meal = 0;
	pthread_mutex_unlock(&(instance->check_meal[(philo->id) - 1]));
	new_sleep(instance->tteat, instance);
	return ;
}

static int	philo_eat(t_philo *philo, t_main *instance)
{
	pthread_mutex_lock(&(instance->mutex_fork[philo->r_fork]));
	instance->fork[philo->r_fork] = 0;
	action_print(instance, philo->id, "has taken a fork");
	while (instance->nbr_philo < 2)
	{
		pthread_mutex_lock(&(instance->mutex_die));
		if (instance->dieded == 1)
		{
			pthread_mutex_unlock(&(instance->mutex_die));
			pthread_mutex_unlock(&(instance->mutex_fork[philo->r_fork]));
			return (0);
		}
		pthread_mutex_unlock(&(instance->mutex_die));
	}
	pthread_mutex_lock(&(instance->mutex_fork[philo->l_fork]));
	instance->fork[philo->l_fork] = 0;
	action_print(instance, philo->id, "has taken a fork");
	philo_action_eat(philo, instance);
	instance->fork[philo->r_fork] = 1;
	pthread_mutex_unlock(&(instance->mutex_fork[philo->r_fork]));
	instance->fork[philo->l_fork] = 1;
	pthread_mutex_unlock(&(instance->mutex_fork[philo->l_fork]));
	return (1);
}

static void	sleep_and_think(t_philo *philo, t_main *instance)
{
	action_print(instance, philo->id, "is sleeping");
	new_sleep(instance->ttsleep, instance);
	action_print(instance, philo->id, "is thinking");
}

static void	increase_all_ate(t_main *instance)
{
	pthread_mutex_lock(&(instance->mutex_all_ate));
	instance->all_ate = instance->all_ate + 1;
	pthread_mutex_unlock(&(instance->mutex_all_ate));
}

void	*routine(void *philosopher)
{
	t_main	*instance;
	t_philo	*philo;

	philo = (t_philo *) philosopher;
	instance = philo->instance;
	if ((philo->id) % 2 == 0)
		sleep_and_think(philo, instance);
	pthread_mutex_lock(&(instance->mutex_die));
	while (instance->dieded == 0)
	{
		pthread_mutex_unlock(&(instance->mutex_die));
		if (!philo_eat(philo, instance))
			break ;
		if (philo->nbr_meal == instance->nbr_must_eat)
		{
			increase_all_ate(instance);
			break ;
		}
		sleep_and_think(philo, instance);
		pthread_mutex_lock(&(instance->mutex_die));
	}
	if ((philo->nbr_meal != instance->nbr_must_eat
			&& instance->nbr_philo != 1))
		pthread_mutex_unlock(&(instance->mutex_die));
	return (NULL);
}
