/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyowchoi <hyowchoi@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 19:39:37 by hyowchoi          #+#    #+#             */
/*   Updated: 2024/02/15 20:19:18 by hyowchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	print_doing(t_info *info, int which, long long start_time, int p_num)
{
	// if (which == DEAD)
	// {
	// 	pthread_mutex_lock(info->const_info->printable);
	// 	printf("%lld %d died\n", (get_now_time() - start_time) / MILLI, p_num + 1);
	// 	pthread_mutex_unlock(info->const_info->printable);
	// 	return ;
	// }

	pthread_mutex_lock(info->const_info->printable);
	if (which != DEAD)
	{
		if (check_died(info))
			printf("%lld %d died\n", (get_now_time() - start_time) / MILLI, p_num + 1);
		if (check_someone_died(info))
		{
			pthread_mutex_unlock(info->const_info->printable);
			return ;
		}
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
