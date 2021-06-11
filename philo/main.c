/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gartaud <gartaud@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/05 10:14:29 by gartaud           #+#    #+#             */
/*   Updated: 2021/06/11 12:27:48 by gartaud          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_philos(t_philo *philos, int n, t_context *c)
{
	int	i;

	i = -1;
	while (++i < n)
	{
		philos[i].id = i;
		philos[i].eat_count = 0;
		philos[i].context = c;
	}
	return (EXIT_SUCCESS);
}

int	init_context(t_context *c, int argc, char **argv)
{
	int	error;

	error = 0;
	if (argc != 5 && argc != 6)
		return (EXIT_FAILURE);
	c->no_philo = ft_atoi(argv[1]);
	c->time_to_die = ft_atoi(argv[2]);
	c->time_to_eat = ft_atoi(argv[3]);
	c->time_to_sleep = ft_atoi(argv[4]);
	c->max_eat = -1;
	if (argc == 6)
		c->max_eat = ft_atoi(argv[5]);
	c->philos = malloc(sizeof(t_philo) * c->no_philo);
	if (!c->philos)
		return (EXIT_FAILURE);
	error = init_philos(c->philos, c->no_philo, c);
	return (error);
}

void	print_context(t_context *c)
{
	printf("context:\n");
	printf("\tno_philo: %d\n", c->no_philo);
	printf("\ttime_to_die: %lld\n", c->time_to_die);
	printf("\ttime_to_eat: %lld\n", c->time_to_eat);
	printf("\ttime_to_sleep: %lld\n", c->time_to_sleep);
	printf("\tmax_eat: %d\n", c->max_eat);
}

void	*routine(void *arg)
{
	t_philo	*p;

	p = (t_philo *)arg;
	printf("Hello I'm philo %d !\n", p->id);
	return (NULL);
}

void	launch_philos(t_context *c)
{
	int	i;

	i = -1;
	while (++i < c->no_philo)
		pthread_create(&(c->philos[i].th), NULL, routine, &(c->philos[i]));
	i = -1;
	while (++i < c->no_philo)
		pthread_join(c->philos[i].th, NULL);
}

int	main(int argc, char **argv)
{
	t_context	context;
	int			error;

	error = init_context(&context, argc, argv);
	if (error)
		return (error);
	//print_context(&context);
	launch_philos(&context);
	return (EXIT_SUCCESS);
}
