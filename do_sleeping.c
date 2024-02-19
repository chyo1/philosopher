/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_sleeping.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyowchoi <hyowchoi@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 12:50:45 by hyowchoi          #+#    #+#             */
/*   Updated: 2024/02/19 13:39:04 by hyowchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "philosopher.h"

int    do_sleeping(t_info *info)
{
	// check someone is dead
	check_died(info);
	if (check_someone_died(info))
		return (1);
	
	// print sleeping
	print_doing(info, SLEEPING, info->const_info->start_time, info->p_num);
	
	// sleeping time
	if (check_died_while_waiting(info, info->const_info->t_sleep))
		return (1);
	return (0);
}
