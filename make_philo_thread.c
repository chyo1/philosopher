/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_info.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyowchoi <hyowchoi@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 18:52:37 by hyowchoi          #+#    #+#             */
/*   Updated: 2024/02/09 17:53:22 by hyowchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	make_philo_thread(t_const *const_info, pthread_t *philo_tid)
{
	int		idx;
	t_info	*info;

	idx = 0;
	while (idx < const_info->p_cnt)
	{
		info = init_info(const_info);
		info->p_num = idx;
		// printf("\n~~idx : %d info->p_num = %d~~ \n", idx, info->p_num);
		if (pthread_create(&(philo_tid[idx]), NULL, do_philo, (void *)info) == -1)
			print_error_n_exit(THREAD_CREATE_ERROR);
		idx++;
	}
}

t_info	*init_info(t_const *const_info)
{
	t_info	*info;

	info = (t_info *)ft_calloc(1, sizeof(t_info));
	info->const_info = const_info;
	info->n_eat = const_info->n_eat;

	// info->wait = (pthread_mutex_t *)ft_calloc(1, sizeof(pthread_mutex_t));

	return (info);
}
