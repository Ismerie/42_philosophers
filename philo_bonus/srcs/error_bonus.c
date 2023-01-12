/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igeorge <igeorge@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 20:12:03 by igeorge           #+#    #+#             */
/*   Updated: 2022/09/08 14:28:03 by igeorge          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	ft_free(t_philo *philo)
{
	free(philo);
	error_msg(MALLOC_ERROR);
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

void	error_msg(int error)
{
	if (error == SYNTAX_ARGUMENT)
		putstr_fd("Error: syntax argument.\n", 2);
	if (error == WRONG_ARGUMENT)
		putstr_fd("Error: wrong argument.\n", 2);
	if (error == MALLOC_ERROR)
		putstr_fd("Error : malloc error.\n", 2);
	if (error == PTHREAD_ERROR)
		putstr_fd("Error : pthread error.\n", 2);
	if (error == SEM_ERROR)
		putstr_fd("Error : semaphore error.\n", 2);
	if (error == WAITPID_ERROR)
		putstr_fd("Error: waitpid error.\n", 2);
	if (error == FORK_ERROR)
		putstr_fd("Error: fork error.\n", 2);
	if (error == TIME_ERROR)
		putstr_fd("Error: time error.\n", 2);
	exit(EXIT_FAILURE);
}
