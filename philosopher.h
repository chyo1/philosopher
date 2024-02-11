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

typedef struct s_const
{
	pthread_mutex_t	*ready;
	int				p_cnt;
	int				t_die;
	int				t_eat;
	int				t_sleep;
	int				*fork;
	int				n_eat;
}	t_const;

typedef struct s_info
{
	pthread_mutex_t	*wait;
	int				p_num;
	int				*my_forks[2];
	int				n_eat;
	t_const			*const_info;
}	t_info;

# define TRUE 1
# define FALSE 0

# define FULL 1
# define EMPTY 0


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

// printf_error_n_exit.c
void		print_error_n_exit(int which);

#endif