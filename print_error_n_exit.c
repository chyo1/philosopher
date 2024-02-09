/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error_n_exit.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyowchoi <hyowchoi@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 19:39:37 by hyowchoi          #+#    #+#             */
/*   Updated: 2024/02/09 12:48:28 by hyowchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	print_error_n_exit(int which)
{
	if (which == INVALID_ARG_NUM)
		printf("Invalid argc num\n");
	if (which == THREAD_CREATE_ERROR)
		printf("pthread create error\n");
	exit (1);
}
