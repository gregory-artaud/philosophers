#include "philo.h"

int		is_somebody_dead(t_context *c)
{
	int	i;

	i = -1;
	while (++i < c->no_philo)
		if (get_death(c->philos + i))
			return (1);
	return (0);
}
