/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyowchoi <hyowchoi@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 18:41:17 by hyowchoi          #+#    #+#             */
/*   Updated: 2024/02/15 19:41:16 by hyowchoi         ###   ########.fr       */
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
	long long		start_time;
	
	// fork
	pthread_mutex_t	*m_fork;
	int				*fork; // all forks
	int				n_eat; // cnt of eating
	
	// make all thread start at once
	pthread_mutex_t	*ready;
	pthread_mutex_t	*check_dead_thread;
	int				*is_thread_dead;
	pthread_mutex_t	*printable;
	int				*is_printable;
}	t_const;

typedef struct s_info
{
	int				p_num; // philo number
	int				*my_forks[2];
	pthread_mutex_t	*chk_forks[2];
	long long		t_last_eat;
	int				n_eat; // 
	t_const			*const_info;
}	t_info;

# define TRUE 1
# define FALSE 0

# define FULL 1
# define EMPTY 0

# define MICRO 1000000
# define MILLI 1000
# define SLEEP_TIME 100

// philo do
# define TAKE_FORK 0
# define EATING 1
# define SLEEPING 2
# define THINKING 3
# define DEAD 4

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
int		make_philo_thread(t_const *const_info, pthread_t *philo_tid);

// do_philo.c
void		*do_philo(void *cont);

// do_eating.c
int	do_eating(t_info *info);

// do_sleeping.c
int    do_sleeping(t_info *info);

// do_thinking.c
int    do_thinking (t_info *info);

// check_died.c
void	check_died(t_info *info);
int	check_someone_died(t_info *info);
int 	check_died_while_waiting(t_info *info, long long total_sleep_time);

// get_time.c
long long	get_now_time(void);

// handle_error_n_fin_program.c
int	check_digit_n_exit(const char *str);
int		print_error(int which);
int	wait_threads(pthread_t *philo_tid, int p_cnt);
int free_resources(t_const *const_info, pthread_t *philo_tid);

// printf_error_n_exit.c
void	print_doing(t_info *info, int which, long long start_time, int p_num);

#endif