#include "philo.h"

int	p_die(t_philo *p)
{
	uint64_t	t;

	get_relative_time(&t, p->context->start);
	printf("%llu %d died\n", t, p->id);
	p->is_alive = 0;
	return (EXIT_SUCCESS);
}
