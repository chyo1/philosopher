/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyowchoi <hyowchoi@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 18:38:31 by hyowchoi          #+#    #+#             */
/*   Updated: 2024/02/13 11:56:33 by hyowchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

/* 	number_of_philosophers, 
	time_to_die, 
	time_to_eat, 
	time_to_sleep, 
	[number_of_times_each_philosopher_must_eat] */
int	main(int argc, char **argv)
{
	pthread_t 		*philo_tid;
	t_const			*const_info;
	struct timeval	time; // to get the start time

	const_info = init_const_info(argc, argv);
	philo_tid = init_tid(const_info->p_cnt);
	
	pthread_mutex_init(const_info->ready, NULL);
	pthread_mutex_lock(const_info->ready);

	gettimeofday(&time, NULL);
	const_info->start_time = time.tv_usec;
	// make philo thread
	make_philo_thread(const_info, philo_tid);
	pthread_mutex_unlock(const_info->ready);

		int		idx;

	idx = 0;
	while (idx < const_info->p_cnt)
	{
		pthread_join(philo_tid[idx], NULL);
			// print_error_n_exit(THREAD_CREATE_ERROR);
		idx++;
	}
}
