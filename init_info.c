/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_info.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyowchoi <hyowchoi@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 13:01:26 by hyowchoi          #+#    #+#             */
/*   Updated: 2024/02/19 13:36:38 by hyowchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	*ft_calloc(size_t count, size_t size)
{
	char	*c;
	size_t	i;

	i = 0;
	c = (char *)malloc(count * size);
	if (c == NULL)
	{
		print_error(MALLOC_ERROR);
		return (0);
	}
	while (i < count * size)
	{
		c[i] = 0;
		i++;
	}
	return ((void *)c);
}

static int	init_const_info_contents_n_check_error(t_const *const_info)
{
	int	idx;

	if (!const_info->p_cnt || !const_info->t_eat || !const_info->t_die || !const_info->t_sleep
		|| !const_info->n_eat)
		return (1);
	idx = 0;
	const_info->is_thread_dead = FALSE;
	const_info->is_printable = TRUE;
	while (idx < const_info->p_cnt)
	{
		pthread_mutex_init(&(const_info->m_fork[idx]), NULL); // check error
		idx++;
	}
	pthread_mutex_init(&const_info->ready, NULL);
	pthread_mutex_init(&const_info->check_dead_thread, NULL);
	pthread_mutex_init(&const_info->printable, NULL);
	return (0);
}

t_const	*init_const_info(int argc, char **argv)
{
	t_const	*const_info;

	// check invalid argument count
	if (!(5 <= argc && argc <= 6))
	{
		print_error(INVALID_ARG_NUM);
		return (0);
	}
	const_info = (t_const *)ft_calloc(1, sizeof(t_const));
	if (const_info == 0)
		return (0);
	const_info->p_cnt = check_digit(argv[1]);
	const_info->t_die = check_digit(argv[2]) * MILLI;
	const_info->t_eat = check_digit(argv[3]) * MILLI;
	const_info->t_sleep = check_digit(argv[4]) * MILLI;
	if (argc == 6)
		const_info->n_eat = check_digit(argv[5]);
	else
		const_info->n_eat = -1;
	const_info->fork = (int *)ft_calloc(const_info->p_cnt, sizeof(int));
	const_info->m_fork = (pthread_mutex_t *)ft_calloc(const_info->p_cnt, sizeof(pthread_mutex_t));
	if (!const_info->fork || !const_info->m_fork)
	{
		free_resources(const_info, NULL, NULL);
		return (0);
	}
	if (init_const_info_contents_n_check_error(const_info))
		return (0);
	return (const_info);
}

pthread_t	*init_tid(int philo_num)
{
	pthread_t	*philo_tid;

	philo_tid = (pthread_t *)ft_calloc(philo_num, sizeof(pthread_t));
	if (!philo_tid)
		return (0);
	return (philo_tid);
}
