/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igeorge <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 17:33:57 by igeorge           #+#    #+#             */
/*   Updated: 2022/07/27 17:33:57 by igeorge          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_main	instance;

	if (argc < 5 || argc > 6)
	{
		error_msg(SYNTAX_ARGUMENT);
		return (1);
	}
	if (!init(&instance, argc - 1, argv) || !init_philo(&instance)
		|| !init_mutex(&instance))
		return (1);
	start(&instance);
	return (0);
}
