/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_thinking.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyowchoi <hyowchoi@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 12:50:54 by hyowchoi          #+#    #+#             */
/*   Updated: 2024/02/19 13:38:55 by hyowchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "philosopher.h"

int    do_thinking (t_info *info)
{
	// check someone is dead
	check_died(info);
	if (check_someone_died(info))
		return (1);

	// print thinking
	print_doing(info, THINKING, info->const_info->start_time, info->p_num);
	return (0);
}
