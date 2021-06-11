/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gartaud <gartaud@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/05 10:14:29 by gartaud           #+#    #+#             */
/*   Updated: 2021/06/11 18:56:22 by gartaud          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
	t_philo		*p;
	uint64_t	t;
	int			error;

	p = (t_philo *)arg;
	if (is_finished(p->context))
		return (NULL);
	get_relative_time(&t, p->context->start);
	printf("%llu %d is born !\n", t, p->id);
	while (1)
	{
		if (p->id == 53)
		{
			p_die(p);
			return (NULL);
		}
		error = p_eat(p);
		if (error)
			return (NULL);
		error = p_sleep(p);
		if (error)
			return (NULL);
		error = p_think(p);
		if (error)
			return (NULL);
	}
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
	launch_philos(&context);
	free_context(&context);
	return (EXIT_SUCCESS);
}
