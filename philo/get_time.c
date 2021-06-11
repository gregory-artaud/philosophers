#include "philo.h"

int	get_absolute_time(uint64_t *t)
{
	int				error;
	struct timeval	time;

	error = gettimeofday(&time, NULL);
	if (error)
		return (error);
	*t = time.tv_sec * 1000 + time.tv_usec / 1000;
	return (EXIT_SUCCESS);
}

int		get_relative_time(uint64_t *t, uint64_t reference)
{
	int			error;
	uint64_t	now;

	error = get_absolute_time(&now);
	if (error)
		return (error);
	*t =  now - reference;
	return (EXIT_SUCCESS);
}
