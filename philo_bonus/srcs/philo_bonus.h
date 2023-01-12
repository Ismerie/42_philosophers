/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igeorge <igeorge@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 20:02:47 by igeorge           #+#    #+#             */
/*   Updated: 2022/09/08 14:29:38 by igeorge          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H

# define PHILO_BONUS_H

# include <semaphore.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/stat.h>
# include <sys/time.h>
# include <sys/types.h>
# include <pthread.h>
# include <sys/wait.h>
# include <limits.h>
# include <signal.h>
# include <fcntl.h>

# define SYNTAX_ARGUMENT -1
# define WRONG_ARGUMENT -2
# define MALLOC_ERROR -3
# define PTHREAD_ERROR -4
# define FORK_ERROR -5
# define SEM_ERROR -6
# define WAITPID_ERROR -7
# define TIME_ERROR -9

typedef struct s_philo
{
	int				id;
	int				nbr_meal;
	int				died;
	long long		last_meal;
	struct s_main	*instance;
	pthread_t		tid;
	pid_t			pid;
}	t_philo;

typedef struct s_main
{
	int			tteat;
	int			ttdie;
	int			ttsleep;
	int			nbr_philo;
	int			nbr_must_eat;
	long long	time_stamp;
	t_philo		*philo;
	sem_t		*write;
	sem_t		*fork;
	sem_t		*check_meal;

}	t_main;

void		init(t_main *instance, int max_arg, char **argv);
void		init_philo(t_main *instance);
void		init_sem(t_main *instance);
void		destroy_sem(t_main *instance);
void		destroy_fork(t_main *instance, int nb_fork);
void		run_fork(t_philo *philo, t_main *instance);
void		*run_thread(void *arg);
void		run_philosophers(t_main *instance);
void		error_time(t_philo *philo, t_main *instance);
void		*print_death(t_philo *philo, t_main *instance);
void		exit_fork(t_philo *philo, int code);
void		new_sleep(long long time);
long long	time_diff(long long past, long long present);
long long	timestamp(void);
void		action_print(t_main *instance, t_philo *philo, char *str);
void		*print_death(t_philo *philo, t_main *instance);
void		error_msg(int error);
void		ft_free(t_philo *philo);

#endif