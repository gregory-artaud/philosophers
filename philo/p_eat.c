/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_eat.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gartaud <gartaud@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/05 10:14:29 by gartaud           #+#    #+#             */
/*   Updated: 2021/09/30 09:29:18 by gartaud          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	take_forks(t_philo *p)
{
	pthread_mutex_lock(p->context->forks + p->lfork);
	put_log(p, TAKE_FORK);
	if (p->context->no_philo == 1)
	{
		pthread_mutex_unlock(p->context->forks + p->lfork);
		return (1);
	}	
	pthread_mutex_lock(p->context->forks + p->rfork);
	put_log(p, TAKE_FORK);
	return (0);
}

void	drop_forks(t_philo *p)
{
	pthread_mutex_unlock(p->context->forks + p->rfork);
	put_log(p, DROP);
	pthread_mutex_unlock(p->context->forks + p->lfork);
	put_log(p, DROP);
}

int	p_eat(t_philo *p)
{
	if (is_somebody_dead(p->context) || take_forks(p))
		return (EXIT_FAILURE);
	pthread_mutex_lock(&p->mutex);
	p->is_eating = 1;
	p->last_eat = get_absolute_time() - p->context->start;
	put_log(p, EAT);
	ft_usleep(p->context->time_to_eat);
	add_eat(p);
	p->is_eating = 0;
	pthread_mutex_unlock(&p->mutex);
	drop_forks(p);
	return (EXIT_SUCCESS);
}
