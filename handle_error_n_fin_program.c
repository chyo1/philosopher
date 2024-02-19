/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_error_n_fin_program.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyowchoi <hyowchoi@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 13:01:38 by hyowchoi          #+#    #+#             */
/*   Updated: 2024/02/19 13:24:17 by hyowchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

static int	is_space(char c)
{
	if ((9 <= c && c <= 13) || c == 32)
		return (1);
	return (0);
}

int	check_digit(const char *str)
{
	long long	num;

	num = 0;
	while (*str != '\0' && is_space(*str))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			return (print_error(INVALID_DIGIT));
		str++;
	}
	while (*str)
	{
		if ('0' <= *str && *str <= '9')
			num = num * 10 + (*str - '0');
		else
			break ;
		str++;
	}
	while (*str != '\0' && is_space(*str))
		str++;
	if (*str != '\0' || num == 0)
		return (print_error(INVALID_DIGIT));
	return (num);
}

int	print_error(int which)
{
	if (which == INVALID_ARG_NUM)
		printf("Invalid argc num\n");
	if (which == INVALID_DIGIT)
		printf("Invalid argument\n");
	if (which == THREAD_CREATE_ERROR)
		printf("pthread create error\n");
	return (0);
}

int	wait_threads(pthread_t *philo_tid, int p_cnt)
{
	int	idx;

	idx = 0;
	while (idx < p_cnt)
	{
		if (pthread_join(philo_tid[idx], NULL))
			return (1);
		idx++;
	}
	return (0);
}

int free_resources(t_const *const_info, pthread_t *philo_tid, t_info *info)
{
	free(const_info->fork);
	free(const_info->m_fork);
	free(const_info);
	free(philo_tid);
	free(info);
	return (1);
}
