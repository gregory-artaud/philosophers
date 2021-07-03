/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gartaud <gartaud@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/05 10:14:29 by gartaud           #+#    #+#             */
/*   Updated: 2021/07/03 21:36:37 by gartaud          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*monitor(void *arg)
{
	t_philo		*p;
	uint64_t	t;
	int			death;

	p = (t_philo *)arg;
	while (1)
	{
		pthread_mutex_lock(&p->mutex);
		t = get_simulation_time(p->context->start);
		death = (!p->is_eating &&
			t - p->last_eat > (uint64_t)p->context->time_to_die);
		if (death)
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

void	*check_max_eat(void *context)
{
	t_context	*c;
	int			i;
	int			j;

	c = (t_context *)context;
	i = -1;
	while (++i <= c->max_eat)
	{
		j = -1;
		while (++j < c->no_philo)
			pthread_mutex_lock(&(c->philos[j].eat_end));
	}
	put_log(c->philos, MAX_EAT);
	pthread_mutex_unlock(&(c->somebody_died));
	return (NULL);
}

void	launch_threads(t_context *c)
{
	int			i;
	pthread_t	count_th;

	get_absolute_time(&(c->start));
	if (c->max_eat != -1)
	{
		pthread_create(&count_th, NULL, &check_max_eat, c);
		pthread_detach(count_th);
	}
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
	pthread_mutex_lock(&(context.somebody_died));
	free_context(&context);
	return (EXIT_SUCCESS);
}
