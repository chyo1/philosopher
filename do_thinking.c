/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_thinking.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyowchoi <hyowchoi@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 12:50:54 by hyowchoi          #+#    #+#             */
/*   Updated: 2024/02/14 17:17:05 by hyowchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "philosopher.h"

int    do_thinking (t_info *info)
{
	if (check_died(info))
		return (TRUE);
	print_doing(info, THINKING, info->const_info->start_time, info->p_num);
	return (FALSE);
}
