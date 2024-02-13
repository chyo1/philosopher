
#include "philosopher.h"

static int	check_forks(t_info *info)
{
	int	first;
	int	second;
	struct timeval	now; // to get the now time

	first = (info->p_num) % 2;
	second = (info->p_num + 1) % 2;

	// check left_fork
	pthread_mutex_lock(info->chk_forks[first]);
	if (*info->my_forks[first] == FULL)
    {
		pthread_mutex_unlock(info->chk_forks[first]); 
        return (FALSE);
    }
    *info->my_forks[first] = FULL;
    gettimeofday(&now, NULL);
    printf("%ld %d has taken a fork\n", 
        (now.tv_usec - info->const_info->start_time) / MILLI, info->p_num);
	pthread_mutex_unlock(info->chk_forks[first]);

	// check right fork
	pthread_mutex_lock(info->chk_forks[second]);
    if (*info->my_forks[second] == FULL)
    {
		pthread_mutex_unlock(info->chk_forks[second]); 
        return (FALSE);
    }
    *info->my_forks[second] = FULL;
    gettimeofday(&now, NULL);
    printf("%ld %d has taken a fork\n", 
    	(now.tv_usec - info->const_info->start_time) / MILLI, info->p_num);
	pthread_mutex_unlock(info->chk_forks[second]);
	return (TRUE);
}

static void	free_forks(t_info *info)
{
	int	first;
	int	second;

	first = (info->p_num) % 2;
	second = (info->p_num + 1) % 2;

	// free left_fork
	pthread_mutex_lock(info->chk_forks[first]);
	info->my_forks[first] = EMPTY;
	pthread_mutex_unlock(info->chk_forks[first]);

	// free right fork
	pthread_mutex_lock(info->chk_forks[second]);
	info->my_forks[second] = EMPTY;
	pthread_mutex_unlock(info->chk_forks[second]);

}

void	do_eating(t_info *info)
{
	struct timeval	now; // to get the now time
	if (info->p_num % 2)
	{
		// even num philo eat first
		usleep((info->const_info->t_eat) / 2);
	}

	// eating
	if (check_forks(info))
	{
		gettimeofday(&now, NULL);
		printf("%ld %d is eating\n", 
			(now.tv_usec - info->const_info->start_time) / MILLI, info->p_num);
	
		usleep(info->const_info->t_eat);
		do_sleeping(info);
	}
	free_forks(info);
}
