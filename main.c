/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyowchoi <hyowchoi@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 18:38:31 by hyowchoi          #+#    #+#             */
/*   Updated: 2024/02/09 17:55:39 by hyowchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

// number_of_philosophers, time_to_die, time_to_eat, time_to_sleep, [number_of_times_each_philosopher_must_eat]
int	main(int argc, char **argv)
{
	pthread_t 		*philo_tid;
	t_const			*const_info;

	const_info = init_const_info(argc, argv);
	philo_tid = init_tid(const_info->p_cnt);
	
	pthread_mutex_init(const_info->ready, NULL);
	pthread_mutex_lock(const_info->ready);

	// make philo thread
	make_philo_thread(const_info, philo_tid);
	pthread_mutex_unlock(const_info->ready);
}
