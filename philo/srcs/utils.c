/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igeorge <igeorge@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 18:37:14 by igeorge           #+#    #+#             */
/*   Updated: 2022/09/08 14:23:35 by igeorge          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_dead(t_main *instance, int id, char *str)
{
	pthread_mutex_lock(&(instance->mutex_write));
	printf("%lli ", timenow() - instance->time_stamp);
	printf("%d %s\n", id, str);
	pthread_mutex_unlock(&(instance->mutex_write));
}

void	action_print(t_main *instance, int id, char *str)
{
	pthread_mutex_lock(&(instance->mutex_write));
	pthread_mutex_lock(&(instance->mutex_die));
	if (instance->dieded == 0)
	{
		pthread_mutex_unlock(&(instance->mutex_die));
		printf("%lli ", timenow() - instance->time_stamp);
		printf("%d %s\n", id, str);
		pthread_mutex_unlock(&(instance->mutex_write));
		return ;
	}
	pthread_mutex_unlock(&(instance->mutex_write));
	pthread_mutex_unlock(&(instance->mutex_die));
	return ;
}

long long	timenow(void)
{
	static struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

long long	time_diff(long long past, long long present)
{
	return (present - past);
}

void	new_sleep(long long time, t_main *instance)
{
	long long	new_time;

	pthread_mutex_lock(&(instance->mutex_die));
	if (instance->dieded == 1)
	{
		pthread_mutex_unlock(&(instance->mutex_die));
		return ;
	}
	pthread_mutex_unlock(&(instance->mutex_die));
	new_time = timenow();
	while (time_diff(new_time, timenow()) < time)
		usleep(50);
}
