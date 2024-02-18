/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_died.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyowchoi <hyowchoi@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 16:00:53 by hyowchoi          #+#    #+#             */
/*   Updated: 2024/02/16 21:25:29 by hyowchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	check_someone_died(t_info *info)
{
	pthread_mutex_lock(&info->const_info->check_dead_thread);
	if (info->const_info->is_thread_dead == TRUE)
	{
		pthread_mutex_unlock(&info->const_info->check_dead_thread);
		return (TRUE);
	}
	pthread_mutex_unlock(&info->const_info->check_dead_thread);
	return (FALSE);
}

void	check_died(t_info *info)
{
	long long	dead_time;

	dead_time = info->const_info->t_die;
	if (get_now_time() - info->t_last_eat >= dead_time)
	{
		pthread_mutex_lock(&info->const_info->check_dead_thread);
		if (info->const_info->is_thread_dead == FALSE)
		{
			print_doing(info, DEAD, info->const_info->start_time, info->p_num);
			info->const_info->is_thread_dead = TRUE;
		}
		pthread_mutex_unlock(&info->const_info->check_dead_thread);
	}
}

int check_died_while_waiting(t_info *info, long long total_sleep_time)
{
	long long	end_time;
	long long	dead_time;

	dead_time = info->const_info->t_die;
	end_time = get_now_time() + total_sleep_time;

	if (total_sleep_time * 0.8 + get_now_time() - info->t_last_eat < dead_time)
		usleep(total_sleep_time * 0.8);

	while (get_now_time() <= end_time)
	{
		// Is this thread dead?
		check_died(info);
		if (check_someone_died(info))
			return (TRUE);
		usleep(SLEEP_TIME);
	}
	return (FALSE);
}
