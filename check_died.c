/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_died.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyowchoi <hyowchoi@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 16:00:53 by hyowchoi          #+#    #+#             */
/*   Updated: 2024/02/14 21:12:34 by hyowchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	check_died(t_info *info)
{
	long long	dead_time;
	long long	now_time;

	pthread_mutex_lock(info->const_info->check_dead_thread);
	if (*info->const_info->is_thread_dead == TRUE)
	{
		pthread_mutex_unlock(info->const_info->check_dead_thread);
		return (TRUE);
	}
	pthread_mutex_unlock(info->const_info->check_dead_thread);

	dead_time = info->const_info->t_die;
	now_time = get_now_time();
	if (now_time - info->t_last_eat >= dead_time)
	{
		pthread_mutex_lock(info->const_info->check_dead_thread);
		*info->const_info->is_thread_dead = TRUE;
		pthread_mutex_unlock(info->const_info->check_dead_thread);
		print_doing(info, DEAD, info->const_info->start_time, info->p_num);
		return (TRUE);
	}
	return (FALSE);
}

int check_died_while_waiting(t_info *info, long long total_sleep_time)
{
	long long	end_time;
	long long	now_time;
	long long	dead_time;

	dead_time = info->const_info->t_die;
	end_time = get_now_time() + total_sleep_time;
	while (!check_died(info))
	{
		pthread_mutex_lock(info->const_info->check_dead_thread);
		if (*info->const_info->is_thread_dead == TRUE)
		{
			pthread_mutex_unlock(info->const_info->check_dead_thread);
			return (TRUE);
		}
		else
			pthread_mutex_unlock(info->const_info->check_dead_thread);

		now_time = get_now_time();

		// wakeup
		if (end_time <= now_time)
			return (FALSE) ;

		// thread is died
		if (info->t_last_eat + dead_time < now_time)
		{
			pthread_mutex_lock(info->const_info->check_dead_thread);
			*info->const_info->is_thread_dead = TRUE;
			pthread_mutex_unlock(info->const_info->check_dead_thread);
			print_doing(info, DEAD, info->const_info->start_time, info->p_num);
			return (TRUE);
		}
		usleep(SLEEP_TIME);
	}
	return (TRUE);
}
