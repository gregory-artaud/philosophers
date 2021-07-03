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
		c->philos[i].id = i;
		c->philos[i].eat_count = 0;
		c->philos[i].context = c;
		c->philos[i].last_eat = 0;
		c->philos[i].lfork = i;
		c->philos[i].rfork = (i + 1) % c->no_philo;
		pthread_mutex_init(&(c->philos[i].mutex), NULL);
		pthread_mutex_init(&(c->philos[i].eat_end), NULL);
	}
	return (EXIT_SUCCESS);
}

int	init_forks(t_context *c)
{
	int	i;

	c->forks = malloc(sizeof(pthread_mutex_t) * c->no_philo);
	if (!c->forks)
		return (EXIT_FAILURE);
	i = -1;
	while (++i < c->no_philo)
		pthread_mutex_init(c->forks + i, NULL);
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
	error = init_forks(c);
	if (error)
		free(c->philos);
	pthread_mutex_init(&(c->write_m), NULL);
	pthread_mutex_init(&(c->somebody_died), NULL);
	c->start = 0;
	return (error);
}

void	free_context(t_context *c)
{
	int	i;

	free(c->philos);
	i = -1;
	while (++i < c->no_philo)
	{
		pthread_mutex_destroy(c->forks + i);
		pthread_mutex_destroy(&(c->philos[i].mutex));
	}
	pthread_mutex_destroy(&(c->write_m));
	pthread_mutex_destroy(&(c->somebody_died));
	free(c->forks);
}
