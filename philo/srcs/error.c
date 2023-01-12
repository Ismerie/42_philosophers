/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igeorge <igeorge@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 18:40:31 by igeorge           #+#    #+#             */
/*   Updated: 2022/08/27 15:06:47 by igeorge          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_free(t_philo *philo, int *fork, int error)
{
	if (philo)
		free(philo);
	if (fork)
		free(fork);
	if (error != 0)
		error_msg(error);
	return (0);
}

static int	ft_strlen(const char *str)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
		i++;
	return (i);
}

static void	putstr_fd(char *s, int fd)
{
	if (s)
		write(fd, s, ft_strlen(s));
}

int	error_msg(int error)
{
	if (error == SYNTAX_ARGUMENT)
		putstr_fd("Error: syntax argument.\n", 2);
	if (error == WRONG_ARGUMENT)
		putstr_fd("Error: wrong argument.\n", 2);
	if (error == MALLOC_ERROR)
		putstr_fd("Error: malloc error.\n", 2);
	if (error == PTHREAD_ERROR)
		putstr_fd("Error: pthread error.\n", 2);
	return (0);
}
