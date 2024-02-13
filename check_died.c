/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_died.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyowchoi <hyowchoi@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 16:00:53 by hyowchoi          #+#    #+#             */
/*   Updated: 2024/02/13 20:50:40 by hyowchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	check_died(t_info *info)
{
	long long	dead_time;
	long long	now_time;
	struct timeval	now; // to get the now time

	pthread_mutex_lock(info->const_info->check_dead_thread);
	if (*info->const_info->is_thread_dead == TRUE)
	{
		pthread_mutex_unlock(info->const_info->check_dead_thread);
		return (TRUE);
	}
	dead_time = info->const_info->t_die;
	now_time = now.tv_sec * MICRO + now.tv_usec;
	gettimeofday(&now, NULL);
	if (now_time - info->last_eat > dead_time)
	{
		pthread_mutex_lock(info->const_info->check_dead_thread);
		*info->const_info->is_thread_dead = TRUE;
		pthread_mutex_unlock(info->const_info->check_dead_thread);
		print_doing(info, DEAD, info->const_info->start_time, info->p_num);
		return (TRUE);
	}
	return (FALSE);
}

int check_died_while_sleeping(t_info *info, long long total_sleep_time)
{
	long long	end_time;
	long long	now_time;
	long long	dead_time;
	long long	last_eat;
	struct timeval	now; // to get the now time

	dead_time = info->const_info->t_die;
	last_eat = info->last_eat;
	gettimeofday(&now, NULL);
	end_time = now.tv_sec * MICRO + now.tv_usec + total_sleep_time;
	while (1)
	{
		pthread_mutex_lock(info->const_info->check_dead_thread);
		if (*info->const_info->is_thread_dead == TRUE)
		{
			pthread_mutex_unlock(info->const_info->check_dead_thread);
			return (TRUE);
		}
		gettimeofday(&now, NULL);
		now_time = now.tv_sec * MICRO + now.tv_usec;
		
		// wakeup
		if (end_time < now_time)
			break;

		// thread is died
		if (last_eat + dead_time < now_time)
		{
			pthread_mutex_lock(info->const_info->check_dead_thread);
			*info->const_info->is_thread_dead = TRUE;
			pthread_mutex_unlock(info->const_info->check_dead_thread);
			print_doing(info, DEAD, info->const_info->start_time, info->p_num);
			return (TRUE);
		}
		usleep(SLEEP_TIME);
	}
	return (FALSE);
}
