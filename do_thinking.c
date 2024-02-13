
#include "philosopher.h"

void    do_thinking (t_info *info)
{
	struct timeval	now; // to get the now time

    gettimeofday(&now, NULL);
		printf("%ld %d is thinking\n", 
			(now.tv_usec - info->const_info->start_time) / MILLI, info->p_num);
	
		usleep(info->const_info->t_eat);
}