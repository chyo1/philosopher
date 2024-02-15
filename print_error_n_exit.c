/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error_n_exit.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyowchoi <hyowchoi@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 19:39:37 by hyowchoi          #+#    #+#             */
/*   Updated: 2024/02/15 15:47:08 by hyowchoi         ###   ########.fr       */
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
	const long long	now_time = get_now_time();
	if (which != DEAD)
	{
		check_died(info);
		if (check_someone_died(info))
			return ;
	}
	// pthread_mutex_lock(info->const_info->printable);
	// if (*info->const_info->is_printable == TRUE)
	// {
		// *info->const_info->is_printable = FALSE;
		// pthread_mutex_unlock(info->const_info->printable);
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
	// }
	// else
	// 	pthread_mutex_unlock(info->const_info->printable);

	// pthread_mutex_lock(info->const_info->printable);
	// *info->const_info->is_printable = TRUE;
	// pthread_mutex_unlock(info->const_info->printable);
}
