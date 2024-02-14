/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_sleeping.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyowchoi <hyowchoi@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 12:50:45 by hyowchoi          #+#    #+#             */
/*   Updated: 2024/02/14 20:26:57 by hyowchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "philosopher.h"

int    do_sleeping(t_info *info)
{
	if (check_died(info))
		return (TRUE);
	print_doing(info, SLEEPING, info->const_info->start_time, info->p_num);
	if (check_died_while_waiting(info, info->const_info->t_sleep))
			return (TRUE);
    // usleep(info->const_info->t_sleep);
	return (FALSE);
}
