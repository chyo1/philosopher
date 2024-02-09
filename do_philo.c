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


void	do_eating(t_info *info)
{
	pthread_mutex_lock(info->wait);
	pthread_mutex_unlock(info->wait);

}

void	*do_philo(void *cont)
{
	t_info	*info;

	info = (t_info *)cont;
	printf("\n---------%d--------\n", info->p_num);
	pthread_mutex_lock(info->wait);
	pthread_mutex_unlock(info->wait);
	do_eating(info);
	return (NULL);
}
