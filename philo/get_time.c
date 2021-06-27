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
	int64_t		res;

	error = get_absolute_time(&now);
	if (error)
		return (error);
	res =  (int64_t)now - (int64_t)reference;
	if (res < 0)
		*t = 0;
	else
		*t = (uint64_t)res;
	return (EXIT_SUCCESS);
}

uint64_t	get_simulation_time(uint64_t reference)
{
	uint64_t	t;

	t = 0;
	get_relative_time(&t, reference);
	return (t);
}
