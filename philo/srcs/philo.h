/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igeorge <igeorge@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 17:25:49 by igeorge           #+#    #+#             */
/*   Updated: 2022/09/08 14:25:42 by igeorge          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H

# define PHILO_H

# include <string.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <limits.h>

# define SYNTAX_ARGUMENT -1
# define WRONG_ARGUMENT -2
# define MALLOC_ERROR -3
# define PTHREAD_ERROR -4

typedef struct s_philo
{
	int				id;
	int				l_fork;
	int				r_fork;
	int				nbr_meal;
	long long		last_meal;
	struct s_main	*instance;
	pthread_t		tid;
}	t_philo;

typedef struct s_main
{
	int				tteat;
	int				ttdie;
	int				ttsleep;
	int				nbr_philo;
	int				nbr_must_eat;
	int				all_ate;
	int				dieded;
	long long		time_stamp;
	int				*fork;
	t_philo			*philo;
	pthread_mutex_t	*check_meal;
	pthread_mutex_t	*mutex_fork;
	pthread_mutex_t	mutex_write;
	pthread_mutex_t	mutex_all_ate;
	pthread_mutex_t	mutex_die;

}	t_main;

int			error_msg(int error);
int			ft_free(t_philo *philo, int *fork, int error);
long long	timenow(void);
long long	time_diff(long long past, long long present);
int			init(t_main *instance, int max_arg, char **argv);
int			init_philo(t_main *instance);
int			init_mutex(t_main *instance);
void		action_print(t_main *instance, int id, char *str);
void		print_dead(t_main *instance, int id, char *str);
int			start(t_main *instance);
void		*routine(void *philo);
void		new_sleep(long long time, t_main *instance);

#endif
