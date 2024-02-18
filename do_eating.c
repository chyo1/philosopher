/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_eating.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyowchoi <hyowchoi@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 12:50:35 by hyowchoi          #+#    #+#             */
/*   Updated: 2024/02/16 16:53:36 by hyowchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

static int	check_left_fork(t_info *info)
{
	while (1)
	{
		// Is this thread dead?
		check_died(info);
		if (check_someone_died(info))
			return (TRUE);
		pthread_mutex_lock(info->chk_forks[0]);
		if (*info->my_forks[0] == EMPTY)
		{
			*info->my_forks[0] = FULL;
			pthread_mutex_unlock(info->chk_forks[0]);
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
		// Is this thread dead?
		check_died(info);
		if (check_someone_died(info))
			return (TRUE);
		pthread_mutex_lock(info->chk_forks[1]);
		if (*info->my_forks[1] == EMPTY)
		{
			*info->my_forks[1] = FULL;
			pthread_mutex_unlock(info->chk_forks[1]);
			print_doing(info, TAKE_FORK, info->const_info->start_time, info->p_num);
			return (FALSE);
		}
		pthread_mutex_unlock(info->chk_forks[1]);
	}
	return (TRUE);
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
	if (info->n_eat == 0)
		return (TRUE);

	// eating
	if (check_forks(info))
		return (TRUE);
	print_doing(info, EATING, info->const_info->start_time, info->p_num);
	if (check_died_while_waiting(info, info->const_info->t_eat))
			return (TRUE);
	if (info->n_eat > 0)
		info->n_eat--;
	free_forks(info);
	return (FALSE);
}
