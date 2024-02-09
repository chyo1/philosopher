/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_info.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyowchoi <hyowchoi@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 18:52:37 by hyowchoi          #+#    #+#             */
/*   Updated: 2024/02/09 17:53:22 by hyowchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

static int	is_space(char c)
{
	if ((9 <= c && c <= 13) || c == 32)
		return (1);
	return (0);
}

static void	*ft_calloc(size_t count, size_t size)
{
	char	*c;
	size_t	i;

	i = 0;
	if (size && count > (size_t)(-1) / size)
		print_error_n_exit(MALLOC_ERROR);
	c = (char *)malloc(count * size);
	if (c == NULL)
		print_error_n_exit(MALLOC_ERROR);
	while (i < count * size)
	{
		c[i] = 0;
		i++;
	}
	return ((void *)c);
}

static int	check_digit_n_exit(const char *str)
{
	long long	num;

	num = 0;
	while (*str != '\0' && is_space(*str))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			print_error_n_exit(INVALID_DIGIT);
		str++;
	}
	while (*str)
	{
		if ('0' <= *str && *str <= '9')
			num = num * 10 + (*str - '0');
		else
			return (num);
		str++;
	}
	while (*str != '\0' && is_space(*str))
		str++;
	if (*str)
		print_error_n_exit(INVALID_DIGIT);
	return (num);
}

void	make_philo_thread(t_const *const_info, pthread_t *philo_tid)
{
	int		idx;
	t_info	*info;

	idx = 1;
	while (idx <= const_info->p_num)
	{
		info = init_info(const_info);
		info->p_num = idx;
		if (pthread_create(&(philo_tid[idx]), NULL, do_philo, (void *)info) == -1)
			print_error_n_exit(THREAD_CREATE_ERROR);
		idx++;
	}
}

t_const	*init_const_info(int argc, char **argv)
{
	t_const	*const_info;

	// invalid argument count
	if (!(5 <= argc && argc <= 6))
		print_error_n_exit (INVALID_ARG_NUM);
	
	const_info = (t_const *)ft_calloc(1, sizeof(t_const));
	const_info->p_num = check_digit_n_exit(argv[1]);
	const_info->t_die = check_digit_n_exit(argv[2]);
	const_info->t_eat = check_digit_n_exit(argv[3]);
	const_info->t_sleep = check_digit_n_exit(argv[4]);
	if (argc == 6)
		const_info->n_eat = check_digit_n_exit(argv[5]);
	const_info->fork = (int *)ft_calloc(const_info->p_num, sizeof(int));
	const_info->ready = (pthread_mutex_t *)ft_calloc(1, sizeof(pthread_mutex_t));
	return (const_info);
}

pthread_t	*init_tid(int philo_num)
{
	pthread_t 		*philo_tid;

	philo_tid = (pthread_t *)ft_calloc(philo_num, sizeof(pthread_t));
	return (philo_tid);
}

t_info	*init_info(t_const *const_info)
{
	t_info	*info;

	info = (t_info *)ft_calloc(1, sizeof(t_info));
	info->const_info = const_info;
	info->n_eat = const_info->n_eat;

	info->wait = (pthread_mutex_t *)ft_calloc(1, sizeof(pthread_mutex_t));

	return (info);
}
