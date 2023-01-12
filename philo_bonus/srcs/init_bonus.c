/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igeorge <igeorge@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 20:14:46 by igeorge           #+#    #+#             */
/*   Updated: 2022/09/08 15:05:45 by igeorge          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

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

void	init_sem(t_main *instance)
{
	sem_unlink("write");
	sem_unlink("fork");
	sem_unlink("check_meal");
	instance->write = sem_open("write", O_CREAT, S_IRWXU, 1);
	instance->fork = sem_open("fork", O_CREAT, S_IRWXU, instance->nbr_philo);
	instance->check_meal = sem_open("check_meal", O_CREAT, S_IRWXU, 1);
	if (instance->check_meal == SEM_FAILED || instance->write == SEM_FAILED
		|| instance->fork == SEM_FAILED)
	{
		destroy_sem(instance);
		error_msg(SEM_ERROR);
	}
}

void	init_philo(t_main *instance)
{
	int	i;

	instance->philo = malloc(sizeof(t_philo) * instance->nbr_philo);
	if (!instance->philo)
		ft_free(instance->philo);
	i = 0;
	while (i < instance->nbr_philo)
	{
		instance->philo[i].id = i + 1;
		instance->philo[i].nbr_meal = 0;
		instance->philo[i].died = 0;
		instance->philo[i].instance = instance;
		instance->philo[i].last_meal = timestamp();
		i++;
	}
}

void	init(t_main *instance, int max_arg, char **argv)
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
			error_msg(WRONG_ARGUMENT);
	}
	else
		instance->nbr_must_eat = -1;
	instance->time_stamp = timestamp();
}
