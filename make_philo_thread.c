/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_philo_thread.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyowchoi <hyowchoi@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 18:52:37 by hyowchoi          #+#    #+#             */
/*   Updated: 2024/02/16 16:14:04 by hyowchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

static t_info	*init_info(t_const *const_info)
{
	t_info	*info;
	int		idx;

	idx = 0;
	info = (t_info *)ft_calloc(const_info->p_cnt, sizeof(t_info));
	if (!info)
		return (0);
	while (idx < const_info->p_cnt)
	{
		info[idx].const_info = const_info;
		info[idx].n_eat = const_info->n_eat;
		idx++;
	}
	return (info);
}

t_info	*make_philo_thread(t_const *const_info, pthread_t *philo_tid)
{
	int		idx;
	t_info	*info;

	idx = 0;	
	info = init_info(const_info);
	if (!info)
		return (0);
	while (idx < const_info->p_cnt)
	{
		info[idx].p_num = idx;
		if (pthread_create(&philo_tid[idx], NULL, do_philo, (void *)&info[idx]) != 0)
		{
			print_error(THREAD_CREATE_ERROR);
			return (0);
		}
		idx++;
	}
	return (info);
}
