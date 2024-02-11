/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_philo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyowchoi <hyowchoi@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 15:27:15 by hyowchoi          #+#    #+#             */
/*   Updated: 2024/02/09 17:29:04 by hyowchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	check_forks(t_info *info)
{
	// check left_fork
	pthread_mutex_lock(info->wait);
	if (info->my_forks[0] == EMPTY)
		info->my_forks[0] = FULL;
	else
		return (FALSE);
	pthread_mutex_unlock(info->wait);

	// check right fork
	pthread_mutex_lock(info->wait);
	if (info->my_forks[1] == EMPTY)
		info->my_forks[1] = FULL;
	else
		return (FALSE);
	pthread_mutex_unlock(info->wait);
	return (TRUE);
}

void	do_eating(t_info *info)
{
	// even num philo eat first
	if (info->p_num % 2)
		usleep();

	// eating
	if (check_forks(info));
		usleep(info->const_info->t_eat);

}

void	*do_philo(void *cont)
{
	t_info	*info;

	info = (t_info *)cont;
	printf("\n---thread info->p_num :%d--\n", info->p_num);
	pthread_mutex_lock(info->wait);
	pthread_mutex_unlock(info->wait);
	info->my_forks[0] = info->const_info->fork[info->p_num];
	info->my_forks[1] = info->const_info->fork[(info->p_num + 1) % info->const_info->p_cnt];
	do_eating(info);
	return (NULL);
}
