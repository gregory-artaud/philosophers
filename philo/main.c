/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gartaud <gartaud@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/05 10:14:29 by gartaud           #+#    #+#             */
/*   Updated: 2021/09/30 09:26:21 by gartaud          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*monitor(void *arg)
{
	t_philo		*p;
	uint64_t	t;
	int			death;

	p = (t_philo *)arg;
	while (!is_somebody_dead(p->context))
	{
		pthread_mutex_lock(&p->mutex);
		t = get_absolute_time() - p->context->start;
		death = (!p->is_eating
				&& t - p->last_eat > (uint64_t)p->context->time_to_die);
		if (death)
		{
			put_log(p, DIE);
			set_death(p, 1);
			pthread_mutex_unlock(&p->mutex);
			return (NULL);
		}
		pthread_mutex_unlock(&p->mutex);
	}
	return (NULL);
}

void	*routine(void *arg)
{
	t_philo		*p;
	pthread_t	monitor_th;

	p = (t_philo *)arg;
	if (!(p->id % 2))
		ft_usleep(p->context->time_to_eat / 10);
	pthread_create(&monitor_th, NULL, monitor, arg);
	while (1)
	{
		if (p_eat(p))
			break ;
		p_sleep(p);
		put_log(p, THINK);
	}
	pthread_join(monitor_th, NULL);
	return (NULL);
}

void	*eat_monitor(void *context)
{
	t_context	*c;
	int			i;
	int			tmp;

	c = (t_context *)context;
	while (!is_somebody_dead(c))
	{
		i = -1;
		while (++i < c->no_philo)
		{
			tmp = get_eat(c->philos + i);
			if (tmp == c->max_eat)
			{
				put_log(c->philos + i, MAX_EAT);
				set_death(c->philos + i, 1);
				return (NULL);
			}
		}
	}
	return (NULL);
}

void	launch_threads(void *context)
{
	int			i;
	t_context	*c;
	pthread_t	eat_th;

	c = (t_context *)context;
	c->start = get_absolute_time();
	if (c->max_eat != -1)
		pthread_create(&eat_th, NULL, &eat_monitor, c);
	i = -1;
	while (++i < c->no_philo)
		pthread_create(&(c->philos[i].th), NULL, &routine, c->philos + i);
	i = -1;
	if (c->max_eat != -1)
		pthread_join(c->philos[i].th, NULL);
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
	launch_threads(&context);
	free_context(&context);
	return (EXIT_SUCCESS);
}
