/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_eating.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyowchoi <hyowchoi@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 12:50:35 by hyowchoi          #+#    #+#             */
/*   Updated: 2024/02/19 13:38:22 by hyowchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

static int	check_left_fork(t_info *info)
{
	while (1)
	{
		// check someone is dead
		check_died(info);
		if (check_someone_died(info))
			return (1);
		
		// check left fork
		pthread_mutex_lock(info->chk_forks[0]);

		// if left fork is empty
		if (*info->my_forks[0] == EMPTY)
		{
			*info->my_forks[0] = FULL;
			pthread_mutex_unlock(info->chk_forks[0]);

			// print take fork
			print_doing(info, TAKE_FORK, info->const_info->start_time, info->p_num);
			break ;
		}
		pthread_mutex_unlock(info->chk_forks[0]); 
	}
	return (0);
}

static int	check_right_fork(t_info *info)
{
	while (1)
	{
		// check someone is dead
		check_died(info);
		if (check_someone_died(info))
			return (1);

		// check right fork
		pthread_mutex_lock(info->chk_forks[1]);

		// if right fork is empty
		if (*info->my_forks[1] == EMPTY)
		{
			*info->my_forks[1] = FULL;
			pthread_mutex_unlock(info->chk_forks[1]);

			// print take fork
			print_doing(info, TAKE_FORK, info->const_info->start_time, info->p_num);
			return (0);
		}
		pthread_mutex_unlock(info->chk_forks[1]);
	}
	return (1);
}

static int	check_forks(t_info *info)
{
	if (check_left_fork(info) || check_right_fork(info))
		return (1);
	return (0);
}

static void	free_forks(t_info *info)
{
	// free right fork
	pthread_mutex_lock(info->chk_forks[1]);
	*info->my_forks[1] = EMPTY;
	pthread_mutex_unlock(info->chk_forks[1]);

	// free left_fork
	pthread_mutex_lock(info->chk_forks[0]);
	*info->my_forks[0] = EMPTY;
	pthread_mutex_unlock(info->chk_forks[0]);
}

int	do_eating(t_info *info)
{
	// if the thread has met the number of times it is eaten, nothing to do
	if (info->n_eat == 0)
		return (1);

	// eating
	if (check_forks(info))
		return (1);

	// print eating
	print_doing(info, EATING, info->const_info->start_time, info->p_num);

	// eating time
	if (check_died_while_waiting(info, info->const_info->t_eat))
		return (1);

	// if the thread has the number of times, check eat count
	if (info->n_eat > 0)
		info->n_eat--;

	free_forks(info);
	return (0);
}
