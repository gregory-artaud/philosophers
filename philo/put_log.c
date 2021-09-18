#include "philo.h"

void	put_log(t_philo *p, int type)
{
	uint64_t	t;

	t = get_absolute_time() - p->context->start;
	pthread_mutex_lock(&(p->context->write_m));
	if (is_somebody_dead(p->context))
	{
		pthread_mutex_unlock(&(p->context->write_m));
		return ;
	}
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
	else if (type == DROP)
		printf("%lu %d dropped a fork\n", t, p->id + 1);
	else if (type == MAX_EAT)
		printf("%lu everyone has eaten enough\n", t);
	pthread_mutex_unlock(&(p->context->write_m));
}
