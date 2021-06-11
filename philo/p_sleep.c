#include "philo.h"

int	p_sleep(t_philo *p)
{
	if (is_finished(p->context))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
