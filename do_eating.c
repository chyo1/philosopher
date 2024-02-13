/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_eating.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyowchoi <hyowchoi@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 12:50:35 by hyowchoi          #+#    #+#             */
/*   Updated: 2024/02/13 19:57:21 by hyowchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

static int	check_forks(t_info *info)
{
	int	first;
	int	second;
	
	first = (info->p_num) % 2;
	second = (info->p_num + 1) % 2;
	while (!check_died(info))
	{
		// check left_fork
		pthread_mutex_lock(info->chk_forks[first]);
		if (*info->my_forks[first] == FULL)
		{
			pthread_mutex_unlock(info->chk_forks[first]); 
			continue ;
		}
		*info->my_forks[first] = FULL;
		print_doing(info, TAKE_FORK, info->const_info->start_time, info->p_num);
		pthread_mutex_unlock(info->chk_forks[first]);

		// check right fork
		pthread_mutex_lock(info->chk_forks[second]);
		if (*info->my_forks[second] == FULL)
		{
			pthread_mutex_unlock(info->chk_forks[second]);
			*info->my_forks[first] = EMPTY;
			continue ;
		}
		*info->my_forks[second] = FULL;
		print_doing(info, TAKE_FORK, info->const_info->start_time, info->p_num);
		pthread_mutex_unlock(info->chk_forks[second]);
		return (FALSE);
	}
	return (TRUE);
}

static void	free_forks(t_info *info)
{
	int	first;
	int	second;

	first = (info->p_num) % 2;
	second = (info->p_num + 1) % 2;

	// free left_fork
	pthread_mutex_lock(info->chk_forks[first]);
	*info->my_forks[first] = EMPTY;
	pthread_mutex_unlock(info->chk_forks[first]);

	// free right fork
	pthread_mutex_lock(info->chk_forks[second]);
	*info->my_forks[second] = EMPTY;
	pthread_mutex_unlock(info->chk_forks[second]);
}

int	do_eating(t_info *info)
{
	// eating
	if (check_forks(info))
		return (TRUE);
	print_doing(info, EATING, info->const_info->start_time, info->p_num);
	if (check_died_while_sleeping(info->last_eat, info->const_info->t_die, info->const_info->t_eat))
			return (TRUE);
	// usleep(info->const_info->t_eat);
	if (info->n_eat > 0)
		info->n_eat--;
	if (info->n_eat == 0)
	{
		free_forks(info);
		return (0);
	}
	free_forks(info);
	return (FALSE);
}
