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
static int	get_print_qualification(t_info *info, int which)
{
	while (1)
	{
		pthread_mutex_lock(&info->const_info->printable);
		if (info->const_info->is_printable == TRUE)
		{
			info->const_info->is_printable = FALSE;
			pthread_mutex_unlock(&info->const_info->printable);
			break ;
		}
		pthread_mutex_unlock(&info->const_info->printable);

		// check if someone died
		if (which != DEAD)
		{
			check_died(info);
			if (check_someone_died(info))
				return (1);
		}
	}
	return (0);
}

void	print_doing(t_info *info, int which, long long start_time, int p_num)
{
	if (get_print_qualification(info, which))
		return ;
	if (which == TAKE_FORK)
		printf("%lld %d has taken a fork\n", (get_now_time() - start_time) / MILLI, p_num + 1);
	else if (which == EATING)
	{
		printf("%lld %d is eating\n", (get_now_time() - start_time) / MILLI, p_num + 1);
		info->t_last_eat = get_now_time();
	}
	else if (which == SLEEPING)
		printf("%lld %d is sleeping\n", (get_now_time() - start_time) / MILLI, p_num + 1);
	else if (which == THINKING)
		printf("%lld %d is thinking\n", (get_now_time() - start_time) / MILLI, p_num + 1);
	else if (which == DEAD)
		printf("%lld %d died\n", (get_now_time() - start_time) / MILLI, p_num + 1);

	// make other thread can print
	if (which != DEAD)
	{
		pthread_mutex_lock(&info->const_info->printable);
		info->const_info->is_printable = TRUE;
		pthread_mutex_unlock(&info->const_info->printable);
	}
}
