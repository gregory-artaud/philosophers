#include "philo.h"

int	get_now_time(uint64_t *t)
{
	int				error;
	struct timeval	time;

	error = gettimeofday(&time, NULL);
	if (error)
		return (error);
	*t = time.tv_sec * 1000000 + time.tv_usec;
	return (EXIT_SUCCESS);
}
