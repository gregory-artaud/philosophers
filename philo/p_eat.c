#include "philo.h"

void	take_forks(t_philo *p)
{
	pthread_mutex_lock(p->context->forks + p->lfork);
	put_log(p, TAKE_FORK);
	pthread_mutex_lock(p->context->forks + p->rfork);
	put_log(p, TAKE_FORK);
}

void	drop_forks(t_philo *p)
{
	pthread_mutex_unlock(p->context->forks + p->lfork);
	pthread_mutex_unlock(p->context->forks + p->rfork);
}

int	p_eat(t_philo *p)
{
	take_forks(p);
	pthread_mutex_lock(&p->mutex);
	p->is_eating = 1;
	p->last_eat = get_simulation_time(p->context->start);
	put_log(p, EAT);
	usleep(p->context->time_to_eat * 1000);
	(p->eat_count)++;
	p->is_eating = 0;
	pthread_mutex_unlock(&p->mutex);
	pthread_mutex_unlock(&p->eat_end);
	drop_forks(p);
	return (EXIT_SUCCESS);
}
