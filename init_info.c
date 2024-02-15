
#include "philosopher.h"

static int	is_space(char c)
{
	if ((9 <= c && c <= 13) || c == 32)
		return (1);
	return (0);
}

void	*ft_calloc(size_t count, size_t size)
{
	char	*c;
	size_t	i;

	i = 0;
	if (size && count > (size_t)(-1) / size)
		print_error_n_exit(MALLOC_ERROR);
	c = (char *)malloc(count * size);
	if (c == NULL)
		print_error_n_exit(MALLOC_ERROR);
	while (i < count * size)
	{
		c[i] = 0;
		i++;
	}
	return ((void *)c);
}

static int	check_digit_n_exit(const char *str)
{
	long long	num;

	num = 0;
	while (*str != '\0' && is_space(*str))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			print_error_n_exit(INVALID_DIGIT);
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
		print_error_n_exit(INVALID_DIGIT);
	return (num);
}

void	init_const_info_mutexs(t_const *const_info)
{
	int	idx;

	idx = 0;
	while (idx < const_info->p_cnt)
	{
		pthread_mutex_init(&(const_info->m_fork[idx]), NULL); // check error
		idx++;
	}
	pthread_mutex_init(const_info->ready, NULL);
	pthread_mutex_init(const_info->check_dead_thread, NULL);
	pthread_mutex_init(const_info->printable, NULL);
}

t_const	*init_const_info(int argc, char **argv)
{
	t_const	*const_info;

	// check invalid argument count
	if (!(5 <= argc && argc <= 6))
		print_error_n_exit (INVALID_ARG_NUM);
	
	const_info = (t_const *)ft_calloc(1, sizeof(t_const));
	const_info->p_cnt = check_digit_n_exit(argv[1]);
	const_info->t_die = check_digit_n_exit(argv[2]) * MILLI;
	const_info->t_eat = check_digit_n_exit(argv[3]) * MILLI;
	const_info->t_sleep = check_digit_n_exit(argv[4]) * MILLI;
	if (argc == 6)
		const_info->n_eat = check_digit_n_exit(argv[5]);
	else
		const_info->n_eat = -1;
	const_info->fork = (int *)ft_calloc(const_info->p_cnt, sizeof(int));
	const_info->m_fork = (pthread_mutex_t *)ft_calloc(const_info->p_cnt, sizeof(pthread_mutex_t));
	const_info->ready = (pthread_mutex_t *)ft_calloc(1, sizeof(pthread_mutex_t));
	const_info->check_dead_thread = (pthread_mutex_t *)ft_calloc(1, sizeof(pthread_mutex_t));
	const_info->is_thread_dead = (int *)ft_calloc(1, sizeof(int));
	const_info->printable = (pthread_mutex_t *)ft_calloc(1, sizeof(pthread_mutex_t));
	const_info->is_printable = (int *)ft_calloc(1, sizeof(int));
	*const_info->is_printable = TRUE;
	init_const_info_mutexs(const_info);
	return (const_info);
}

pthread_t	*init_tid(int philo_num)
{
	pthread_t	*philo_tid;

	philo_tid = (pthread_t *)ft_calloc(philo_num, sizeof(pthread_t));
	return (philo_tid);
}
