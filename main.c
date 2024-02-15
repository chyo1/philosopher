/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyowchoi <hyowchoi@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 18:38:31 by hyowchoi          #+#    #+#             */
/*   Updated: 2024/02/15 20:40:58 by hyowchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"


int	wait_threads(pthread_t *philo_tid, int p_cnt)
{
	int	idx;

	idx = 0;
	while (idx < p_cnt)
	{
		pthread_join(philo_tid[idx], NULL);
		idx++;
		
	}
	return (0);
}

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
	if (const_info->p_cnt == 1)
	{
		usleep(const_info->t_die);
		printf("%d 1 died\n", const_info->t_die / MILLI);
		return 0;
	}

	philo_tid = init_tid(const_info->p_cnt);

	pthread_mutex_lock(const_info->ready);

	const_info->start_time = get_now_time();
	make_philo_thread(const_info, philo_tid);

	pthread_mutex_unlock(const_info->ready);
	return (wait_threads(philo_tid, const_info->p_cnt));
}
