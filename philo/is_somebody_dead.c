/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_somebody_dead.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gartaud <gartaud@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/05 10:14:29 by gartaud           #+#    #+#             */
/*   Updated: 2021/09/30 09:28:50 by gartaud          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_somebody_dead(t_context *c)
{
	int	i;

	i = -1;
	while (++i < c->no_philo)
		if (get_death(c->philos + i))
			return (1);
	return (0);
}
