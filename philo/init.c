#include "philo.h"

int	init_philos(t_context *c)
{
	int	i;

	c->philos = malloc(sizeof(t_philo) * c->no_philo);
	if (!c->philos)
		return (EXIT_FAILURE);
	i = -1;
	while (++i < c->no_philo)
	{
		c->philos[i].id = i + 1;
		c->philos[i].eat_count = 0;
		c->philos[i].context = c;
		c->philos[i].last_eat_date = 0;
		c->philos[i].is_alive = 1;
	}
	return (EXIT_SUCCESS);
}

int	init_mutexes(t_context *c)
{
	int	i;

	c->mutexes = malloc(sizeof(pthread_mutex_t) * c->no_philo);
	if (!c->mutexes)
		return (EXIT_FAILURE);
	i = -1;
	while (++i < c->no_philo)
		pthread_mutex_init(c->mutexes + i, NULL);
	return (EXIT_SUCCESS);
}

int	process_argv(t_context *c, int argc, char **argv)
{
	if (argc != 5 && argc != 6)
		return (EXIT_FAILURE);
	c->no_philo = ft_atoi(argv[1]);
	if (c->no_philo < 1)
		return (EXIT_FAILURE);
	c->time_to_die = ft_atoi(argv[2]);
	c->time_to_eat = ft_atoi(argv[3]);
	c->time_to_sleep = ft_atoi(argv[4]);
	c->max_eat = -1;
	if (argc == 6)
		c->max_eat = ft_atoi(argv[5]);
	return (EXIT_SUCCESS);
}

int	init_context(t_context *c, int argc, char **argv)
{
	int	error;

	error = process_argv(c, argc, argv);
	if (error)
		return (error);
	error = init_philos(c);
	if (error)
		return (error);
	error = init_mutexes(c);
	if (error)
		free(c->philos);
	error = get_now_time(&(c->start));
	return (error);
}

void	free_context(t_context *c)
{
	int	i;

	free(c->philos);
	i = -1;
	while (++i < c->no_philo)
		pthread_mutex_destroy(c->mutexes + i);
	free(c->mutexes);
}
