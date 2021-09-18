#include "philo.h"

void	set_death(t_philo *p, int value)
{
	pthread_mutex_lock(&p->death_m);
	p->is_dead = value;
	pthread_mutex_unlock(&p->death_m);
}

int		get_death(t_philo *p)
{
	int	res;

	pthread_mutex_lock(&p->death_m);
	res = p->is_dead;
	pthread_mutex_unlock(&p->death_m);
	return (res);
}

void	add_eat(t_philo *p)
{
	pthread_mutex_lock(&p->eat_m);
	(p->eat_count)++;
	pthread_mutex_unlock(&p->eat_m);
}

int		get_eat(t_philo *p)
{
	int	res;

	pthread_mutex_lock(&p->eat_m);
	res = p->eat_count;
	pthread_mutex_unlock(&p->eat_m);
	return (res);
}
