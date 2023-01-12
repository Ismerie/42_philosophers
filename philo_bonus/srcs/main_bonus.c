/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igeorge <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 20:11:05 by igeorge           #+#    #+#             */
/*   Updated: 2022/08/05 20:11:05 by igeorge          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	main(int argc, char **argv)
{
	t_main	instance;

	if (argc < 5 || argc > 6)
	{
		error_msg(SYNTAX_ARGUMENT);
		return (1);
	}
	init(&instance, argc - 1, argv);
	init_philo(&instance);
	init_sem(&instance);
	run_philosophers(&instance);
	return (0);
}
