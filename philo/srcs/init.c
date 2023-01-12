/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igeorge <igeorge@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 13:14:03 by igeorge           #+#    #+#             */
/*   Updated: 2022/09/08 14:23:11 by igeorge          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_is_space(char c)
{
	if (c == '\t' || c == '\n' || c == '\v'
		|| c == '\f' || c == '\r' || c == ' ')
		return (1);
	else
		return (0);
}

static long	ft_atol(char *str, int *dest)
{
	int					i;
	long				nbr;

	i = 0;
	nbr = 0;
	if (str[i] == '\0')
		return (0);
	while (str[i] && ft_is_space(str[i]))
		i++;
	if (!(str[i] >= '0' && str[i] <= '9') && str[i] != '+')
		return (0);
	if (str[i] == '+')
		i++;
	while (str[i] && (str[i] >= '0' && str[i] <= '9'))
		nbr = nbr * 10 + (str[i++] - '0');
	if (str[i] != '\0')
		return (0);
	if (nbr > INT_MAX)
		return (0);
	*dest = (int)nbr;
	return (nbr);
}

int	init_mutex(t_main *instance)
{
	int	i;
	int	nbr_philo;

	nbr_philo = instance->nbr_philo;
	instance->mutex_fork = malloc(sizeof(pthread_mutex_t) * nbr_philo);
	if (!instance->mutex_fork)
		return (ft_free(instance->philo, instance->fork, MALLOC_ERROR));
	instance->check_meal = malloc(sizeof(pthread_mutex_t) * nbr_philo);
	if (!instance->check_meal)
	{
		free(instance->mutex_fork);
		return (ft_free(instance->philo, instance->fork, MALLOC_ERROR));
	}
	i = -1;
	while (++i < instance->nbr_philo)
	{
		pthread_mutex_init(&(instance->check_meal[i]), NULL);
		pthread_mutex_init(&(instance->mutex_fork[i]), NULL);
	}
	pthread_mutex_init(&(instance->mutex_write), NULL);
	pthread_mutex_init(&(instance->mutex_all_ate), NULL);
	pthread_mutex_init(&(instance->mutex_die), NULL);
	return (1);
}

int	init_philo(t_main *instance)
{
	int	i;

	instance->philo = malloc(sizeof(t_philo) * instance->nbr_philo);
	instance->fork = malloc(sizeof(int) * instance->nbr_philo);
	if (!instance->fork || !instance->philo)
		return (ft_free(instance->philo, instance->fork, MALLOC_ERROR));
	i = 0;
	while (i < instance->nbr_philo)
	{
		instance->fork[i] = 1;
		instance->philo[i].id = i + 1;
		instance->philo[i].nbr_meal = 0;
		instance->philo[i].last_meal = timenow();
		instance->philo[i].instance = instance;
		instance->philo[i].r_fork = i;
		if (i == (instance->nbr_philo - 1))
			instance->philo[i].l_fork = 0;
		else
			instance->philo[i].l_fork = i + 1;
		i++;
	}
	return (1);
}

int	init(t_main *instance, int max_arg, char **argv)
{
	if (!ft_atol(argv[1], &instance->nbr_philo) || instance->nbr_philo == 0
		|| !ft_atol(argv[2], &instance->ttdie) || instance->ttdie == 0
		|| !ft_atol(argv[3], &instance->tteat) || instance->tteat == 0
		|| !ft_atol(argv[4], &instance->ttsleep) || instance->ttsleep == 0)
		return (error_msg(WRONG_ARGUMENT));
	if (max_arg == 5)
	{
		if (!ft_atol(argv[5], &instance->nbr_must_eat)
			|| instance->nbr_must_eat == 0)
			return (error_msg(WRONG_ARGUMENT));
	}
	else
		instance->nbr_must_eat = -1;
	instance->all_ate = 0;
	instance->dieded = 0;
	instance->time_stamp = timenow();
	return (1);
}
