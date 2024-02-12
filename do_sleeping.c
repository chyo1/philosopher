
#include "philosopher.h"

void    do_sleeping(t_info *info)
{
	struct timeval	now; // to get the now time
    
    gettimeofday(&now, NULL);
		printf("%ld %d is sleeping\n", 
			now.tv_sec - info->const_info->start_time, info->p_num);
    usleep(info->const_info->t_sleep);
	do_thinking(info);
}
