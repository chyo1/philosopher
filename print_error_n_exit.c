/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error_n_exit.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyowchoi <hyowchoi@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 19:39:37 by hyowchoi          #+#    #+#             */
/*   Updated: 2024/02/14 20:43:38 by hyowchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	print_error_n_exit(int which)
{
	if (which == INVALID_ARG_NUM)
		printf("Invalid argc num\n");
	if (which == THREAD_CREATE_ERROR)
		printf("pthread create error\n");
	exit (1);
}

void	print_doing(t_info *info, int which, long long start_time, int p_num)
{
	struct timeval	now; // to get the now time
	long long now_time;
	
	pthread_mutex_lock(info->const_info->check_dead_thread);
	if (*info->const_info->is_thread_dead == TRUE)
	{
		which = DEAD;
	}
	pthread_mutex_unlock(info->const_info->check_dead_thread);

	gettimeofday(&now, NULL);
	now_time = now.tv_sec * MICRO + now.tv_usec;
	if (which == TAKE_FORK)
		printf("%lld %d has taken a fork\n", (now_time - start_time) / MILLI, p_num);
	else if (which == EATING)
	{
		info->t_last_eat = now_time;
		printf("%lld %d is eating\n", (now_time - start_time) / MILLI, p_num);
	}
	else if (which == SLEEPING)
		printf("%lld %d is sleeping\n", (now_time - start_time) / MILLI, p_num);
	else if (which == THINKING)
		printf("%lld %d is thinking\n", (now_time - start_time) / MILLI, p_num);
	else if (which == DEAD)
		printf("%lld %d died\n", (now_time - start_time) / MILLI, p_num);
}