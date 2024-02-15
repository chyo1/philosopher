#include "philosopher.h"

static int	is_space(char c)
{
	if ((9 <= c && c <= 13) || c == 32)
		return (1);
	return (0);
}

int	check_digit_n_exit(const char *str)
{
	long long	num;

	num = 0;
	while (*str != '\0' && is_space(*str))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			print_error(INVALID_DIGIT);
		str++;
	}
	while (*str)
	{
		if ('0' <= *str && *str <= '9')
			num = num * 10 + (*str - '0');
		else
			break ;
		str++;
	}
	while (*str != '\0' && is_space(*str))
		str++;
	if (*str != '\0' || num == 0)
		print_error(INVALID_DIGIT);
	return (num);
}

int	print_error(int which)
{
	if (which == INVALID_ARG_NUM)
		printf("Invalid argc num\n");
	if (which == INVALID_DIGIT)
		printf("Invalid argument\n");
	if (which == THREAD_CREATE_ERROR)
		printf("pthread create error\n");
	// exit (1);
	return (TRUE);
}

int	wait_threads(pthread_t *philo_tid, int p_cnt)
{
	int	idx;

	idx = 0;
	while (idx < p_cnt)
	{
		pthread_join(philo_tid[idx], NULL);
		idx++;
	}
	return (0);
}

int free_resources(t_const *const_info, pthread_t *philo_tid)
{
	free(const_info->fork);
	free(const_info->m_fork);
	free(const_info->check_dead_thread);
	free(const_info->is_thread_dead);
	free(const_info->ready);
	free(const_info->is_printable);
	free(const_info->printable);
	free(const_info);
	free(philo_tid);
	return (0);
}