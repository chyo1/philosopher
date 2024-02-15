/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error_n_exit.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyowchoi <hyowchoi@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 19:39:37 by hyowchoi          #+#    #+#             */
/*   Updated: 2024/02/15 19:24:24 by hyowchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	print_error_n_exit(int which)
{
	if (which == INVALID_ARG_NUM)
		printf("Invalid argc num\n");
	if (which == INVALID_DIGIT)
		printf("Invalid argument\n");
	if (which == THREAD_CREATE_ERROR)
		printf("pthread create error\n");
	exit (1);
	return (TRUE);
}

void	print_doing(t_info *info, int which, long long start_time, int p_num)
{
	pthread_mutex_lock(info->const_info->printable);
	if (which != DEAD)
	{
		check_died(info);
		if (check_someone_died(info))
			return ;
	}
	if (which == TAKE_FORK)
		printf("%lld %d has taken a fork\n", (get_now_time() - start_time) / MILLI, p_num + 1);
	else if (which == EATING)
	{
		info->t_last_eat = get_now_time();
		printf("%lld %d is eating\n", (get_now_time() - start_time) / MILLI, p_num + 1);
	}
	else if (which == SLEEPING)
		printf("%lld %d is sleeping\n", (get_now_time() - start_time) / MILLI, p_num + 1);
	else if (which == THINKING)
		printf("%lld %d is thinking\n", (get_now_time() - start_time) / MILLI, p_num + 1);
	else if (which == DEAD)
		printf("%lld %d died\n", (get_now_time() - start_time) / MILLI, p_num + 1);
	pthread_mutex_unlock(info->const_info->printable);
}
