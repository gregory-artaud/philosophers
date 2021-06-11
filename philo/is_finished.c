#include "philo.h"

int	is_anybody_dead(t_context *c)
{
	int	i;

	i = -1;
	while (++i < c->no_philo)
		if (!c->philos[i].is_alive)
			return (1);
	return (0);
}

int	has_anybody_ate_enough(t_context *c)
{
	int	i;

	i = -1;
	while (++i < c->no_philo)
		if (c->max_eat <= c->philos[i].eat_count)
			return (1);
	return (0);
}

int	is_finished(t_context *c)
{
	return (is_anybody_dead(c) || has_anybody_ate_enough(c));
}
