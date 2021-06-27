#include "philo.h"

int	p_sleep(t_philo *p)
{
	put_log(p, SLEEP);
	usleep(p->context->time_to_sleep * 1000);
	return (EXIT_SUCCESS);
}
