/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_philo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyowchoi <hyowchoi@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 15:27:15 by hyowchoi          #+#    #+#             */
/*   Updated: 2024/02/13 12:03:26 by hyowchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	*do_philo(void *cont)
{
	t_info	*info;
	int		p_cnt;

	info = (t_info *)cont;
	p_cnt = info->const_info->p_cnt;
	pthread_mutex_lock(info->const_info->ready);
	pthread_mutex_unlock(info->const_info->ready);
	info->chk_forks[0] = &(info->const_info->m_fork[info->p_num]);
	info->chk_forks[1] = &(info->const_info->m_fork[(info->p_num + 1) % p_cnt]);
	info->my_forks[0] = &(info->const_info->fork[info->p_num]);
	info->my_forks[1] = &(info->const_info->fork[(info->p_num + 1) % p_cnt]);
	// printf("\n---thread num %d: its forks: %d %d--\n", info->p_num, info->p_num, (info->p_num + 1) % p_cnt);
	do_eating(info);
	return (NULL);
}
