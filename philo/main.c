/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gartaud <gartaud@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/05 10:14:29 by gartaud           #+#    #+#             */
/*   Updated: 2021/06/27 19:23:31 by gartaud          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_context(t_context *c)
{
	printf("context:\n");
	printf("\tno_philo: %d\n", c->no_philo);
	printf("\ttime_to_die: %ld\n", c->time_to_die);
	printf("\ttime_to_eat: %ld\n", c->time_to_eat);
	printf("\ttime_to_sleep: %ld\n", c->time_to_sleep);
	printf("\tmax_eat: %d\n", c->max_eat);
}

void	*monitor(void *arg)
{
	t_philo		*p;
	uint64_t	t;
	int			cond;

	p = (t_philo *)arg;
	while (1)
	{
		pthread_mutex_lock(&p->mutex);
		t = get_simulation_time(p->context->start);
		cond = (!p->is_eating &&
			t - p->last_eat > (uint64_t)p->context->time_to_die);
		if (cond)
		{
			put_log(p, DIE);
			pthread_mutex_unlock(&p->mutex);
			pthread_mutex_unlock(&p->context->somebody_died);
			return (NULL);
		}
		pthread_mutex_unlock(&p->mutex);
		usleep(1000);
	}
	return (NULL);
}

void	*routine(void *arg)
{
	t_philo		*p;
	pthread_t	monitor_th;

	p = (t_philo *)arg;
	pthread_create(&monitor_th, NULL, monitor, arg);
	pthread_detach(monitor_th);
	while (1)
	{
		p_eat(p);
		p_sleep(p);
		put_log(p, THINK);
	}
	return (NULL);
}


void	launch_threads(t_context *c)
{
	int			i;

	get_absolute_time(&(c->start));
	i = -1;
	while (++i < c->no_philo)
	{
		pthread_create(&(c->philos[i].th), NULL, &routine, c->philos + i);
		pthread_detach(c->philos[i].th);
		usleep(100);
	}
}

int	main(int argc, char **argv)
{
	t_context	context;
	int			error;

	error = init_context(&context, argc, argv);
	if (error)
		return (error);
	launch_threads(&context);
	pthread_mutex_lock(&(context.somebody_died));
	pthread_mutex_unlock(&(context.somebody_died));
	free_context(&context);
	return (EXIT_SUCCESS);
}
