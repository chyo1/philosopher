/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_philo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyowchoi <hyowchoi@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 15:27:15 by hyowchoi          #+#    #+#             */
/*   Updated: 2024/02/16 19:13:48 by hyowchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

static void	init_philo_info(t_info *info)
{
	int	p_cnt;

	p_cnt = info->const_info->p_cnt;
	info->chk_forks[0] = &(info->const_info->m_fork[info->p_num]);
	info->chk_forks[1] = &(info->const_info->m_fork[(info->p_num + 1) % p_cnt]);
	info->my_forks[0] = &(info->const_info->fork[info->p_num]);
	info->my_forks[1] = &(info->const_info->fork[(info->p_num + 1) % p_cnt]);
	pthread_mutex_lock(info->const_info->ready);
	pthread_mutex_unlock(info->const_info->ready);

	// to check_dead_time first_eat_time = start_time
	info->t_last_eat = get_now_time();
}

void	*do_philo(void *cont)
{
	t_info	*info;

	info = (t_info *)cont;
	init_philo_info(info);
	if (info->p_num % 2)
	{
		// even num philo eat first
		if (check_died_while_waiting(info, info->const_info->t_eat))
			return (NULL);
	}
	while (1)
	{
		if (do_eating(info))
			return (NULL);
		if (do_sleeping(info))
			return (NULL);
		if (do_thinking(info))
			return (NULL);
	}
	return (NULL);
}
