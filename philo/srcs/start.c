/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igeorge <igeorge@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 20:21:57 by igeorge           #+#    #+#             */
/*   Updated: 2022/09/08 14:22:01 by igeorge          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	exit_start(t_main *instance, t_philo *philo, int error)
{
	int	i;

	i = -1;
	while (++i < instance->nbr_philo)
		pthread_join(philo[i].tid, NULL);
	i = -1;
	while (++i < instance->nbr_philo)
	{
		pthread_mutex_destroy(&(instance->mutex_fork[i]));
		pthread_mutex_destroy(&(instance->check_meal[i]));
	}
	pthread_mutex_destroy(&(instance->mutex_write));
	pthread_mutex_destroy(&(instance->mutex_all_ate));
	free(instance->mutex_fork);
	free(instance->check_meal);
	ft_free(philo, instance->fork, error);
	return (0);
}

static void	is_died(t_main *instance, t_philo *philo, int i)
{
	pthread_mutex_lock(&(instance->mutex_die));
	instance->dieded = 1;
	pthread_mutex_unlock(&(instance->mutex_die));
	pthread_mutex_unlock(&(instance->check_meal[i]));
	print_dead(instance, philo[i].id, "died");
}

static void	death_checker(t_main *instance, t_philo *philo, int i)
{
	pthread_mutex_lock(&(instance->mutex_all_ate));
	while ((instance->all_ate < instance->nbr_philo)
		|| instance->nbr_must_eat == -1)
	{
		pthread_mutex_unlock(&(instance->mutex_all_ate));
		i = -1;
		while (++i < instance->nbr_philo)
		{
			pthread_mutex_lock(&(instance->check_meal[i]));
			if (philo[i].last_meal != 0
				&& (time_diff(philo[i].last_meal, timenow()) > instance->ttdie))
			{
				is_died(instance, philo, i);
				return ;
			}
			pthread_mutex_unlock(&(instance->check_meal[i]));
		}
		pthread_mutex_lock(&(instance->mutex_all_ate));
	}
	pthread_mutex_unlock(&(instance->mutex_all_ate));
	pthread_mutex_lock(&(instance->mutex_write));
	printf("All philosophers have finished eating ");
	printf("%d times.\n", instance->nbr_must_eat);
	pthread_mutex_unlock(&(instance->mutex_write));
}

int	start(t_main *instance)
{
	int	i;

	i = 0;
	while (i < instance->nbr_philo)
	{
		if (pthread_create(&(instance->philo[i].tid), NULL, &routine,
				&instance->philo[i]))
			return (exit_start(instance, instance->philo, PTHREAD_ERROR));
		i++;
	}
	death_checker(instance, instance->philo, -1);
	exit_start(instance, instance->philo, 0);
	return (1);
}
