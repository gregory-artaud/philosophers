#include "philo.h"

void	ft_usleep(long int time_in_ms)
{
	long int	start_time;

	start_time = get_absolute_time();
	while ((get_absolute_time() - start_time) < time_in_ms)
		usleep(time_in_ms / 10);
}
