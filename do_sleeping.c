/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_sleeping.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyowchoi <hyowchoi@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 12:50:45 by hyowchoi          #+#    #+#             */
/*   Updated: 2024/02/13 19:51:23 by hyowchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "philosopher.h"

int    do_sleeping(t_info *info)
{
	print_doing(info, SLEEPING, info->const_info->start_time, info->p_num);
	if (check_died_while_sleeping(info->last_eat, info->const_info->t_die, info->const_info->t_sleep))
			return (TRUE);
    // usleep(info->const_info->t_sleep);
	return (FALSE);
}
