#include "philo.h"

void	put_log(t_philo *p, int type)
{
	uint64_t	t;

	t = get_simulation_time(p->context->start);
	pthread_mutex_lock(&(p->context->write_m));
	if (type == EAT)
		printf("%lu %d is eating\n", t, p->id + 1);
	else if (type == DIE)
		printf("%lu %d died\n", t, p->id + 1);
	else if (type == TAKE_FORK)
		printf("%lu %d has taken a fork\n", t, p->id + 1);
	else if (type == SLEEP)
		printf("%lu %d is sleeping\n", t, p->id + 1);
	else if (type == THINK)
		printf("%lu %d is thinking\n", t, p->id + 1);
	else if (type == MAX_EAT)
		printf("%lu everyone has eaten enough\n", t);
	pthread_mutex_unlock(&(p->context->write_m));
}
