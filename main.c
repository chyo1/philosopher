/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyowchoi <hyowchoi@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 18:38:31 by hyowchoi          #+#    #+#             */
/*   Updated: 2024/02/15 21:07:51 by hyowchoi         ###   ########.fr       */
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

	const_info = init_const_info(argc, argv);
	if (!const_info)
		return (1);

	// If there's only one philosopher, kill at t_die
	if (const_info->p_cnt == 1)
	{
		usleep(const_info->t_die);
		printf("%d 1 died\n", const_info->t_die / MILLI);
		free_resources(const_info, NULL);
		return (1);
	}

	philo_tid = init_tid(const_info->p_cnt);
	if (!philo_tid)
		return (free_resources(const_info, philo_tid));

	// to make all thread start at once
	pthread_mutex_lock(const_info->ready);

	const_info->start_time = get_now_time();
	if (make_philo_thread(const_info, philo_tid))
		return (free_resources(const_info, philo_tid));

	pthread_mutex_unlock(const_info->ready);

	// wait for all threads to finish
	if (wait_threads(philo_tid, const_info->p_cnt))
		return (free_resources(const_info, philo_tid));

	// free all resources
	free_resources(const_info, philo_tid);
	return (0);
}
