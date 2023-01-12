/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igeorge <igeorge@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 20:11:27 by igeorge           #+#    #+#             */
/*   Updated: 2022/09/08 14:29:05 by igeorge          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*print_death(t_philo *philo, t_main *instance)
{
	sem_wait(instance->write);
	printf("%lli ", timestamp() - instance->time_stamp);
	printf("%d died\n", philo->id);
	exit(EXIT_FAILURE);
}

void	action_print(t_main *instance, t_philo *philo, char *str)
{
	sem_wait(instance->write);
	printf("%lli ", timestamp() - instance->time_stamp);
	printf("%d %s\n", philo->id, str);
	sem_post(instance->write);
	return ;
}

long long	timestamp(void)
{
	static struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

long long	time_diff(long long past, long long present)
{
	return (present - past);
}

void	new_sleep(long long time)
{
	long long	new_time;

	new_time = timestamp();
	while (time_diff(new_time, timestamp()) < time)
		usleep(50);
}
