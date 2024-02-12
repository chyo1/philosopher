/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyowchoi <hyowchoi@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 18:41:17 by hyowchoi          #+#    #+#             */
/*   Updated: 2024/02/09 17:55:32 by hyowchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER
# define PHILOSOPHER

# include <unistd.h>
# include <stdio.h>
# include <pthread.h>
# include <stdlib.h> // NULL?
# include <sys/time.h> // gettimeofday

typedef struct s_const
{
	int				p_cnt; // cnt of philos
	int				t_die; // time to die
	int				t_eat; // time to eat
	int				t_sleep; // time to sleep
	int				*fork; // all forks
	int				n_eat; // cnt of eating
	time_t			start_time;
	// make all thread start at once
	pthread_mutex_t	*ready;
	pthread_mutex_t	*m_fork; // fork mutex
}	t_const;

typedef struct s_info
{
	int				p_num; // philo number
	int				my_forks[2];
	pthread_mutex_t	*chk_forks[2];
	int				n_eat; // 
	t_const			*const_info;
	// pthread_mutex_t	wait;
}	t_info;

# define TRUE 1
# define FALSE 0

# define FULL 1
# define EMPTY 0

# define MILLI 1000

// philo do
# define EATING 1
# define SLEEPING 2
# define THINKING 3

// error type
# define INVALID_ARG_NUM 0
# define INVALID_DIGIT 1
# define MALLOC_ERROR 2
# define THREAD_CREATE_ERROR 3

// main.c
int			main(int argc, char **argv);

// init_info.c
void		*ft_calloc(size_t count, size_t size);
t_const		*init_const_info(int argc, char **argv);
pthread_t	*init_tid(int philo_num);

// make_philo_thread.c
void		make_philo_thread(t_const *const_info, pthread_t *philo_tid);
t_info		*init_info(t_const *const_info);

// do_philo.c
void		*do_philo(void *cont);

// do_eating.c
void	do_eating(t_info *info);

// do_sleeping.c
void    do_sleeping(t_info *info);

// do_thinking.c
void    do_thinking (t_info *info);

// printf_error_n_exit.c
void		print_error_n_exit(int which);

#endif