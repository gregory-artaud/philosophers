/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gartaud <gartaud@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/05 10:13:35 by gartaud           #+#    #+#             */
/*   Updated: 2021/06/11 17:51:23 by gartaud          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <sys/time.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>

typedef struct s_philo
{
	int					id;
	int					is_alive;
	int					eat_count;
	pthread_t			th;
	uint64_t			last_eat_date;
	struct s_context	*context;
}						t_philo;

typedef struct s_context
{
	int				no_philo;
	int64_t			time_to_die;
	int64_t			time_to_eat;
	int64_t			time_to_sleep;
	int				max_eat;
	pthread_mutex_t	*mutexes;
	t_philo			*philos;
	uint64_t		start;
}					t_context;

/*
** lib
*/
int		ft_atoi(const char *s);
/*
** init
*/
int		init_context(t_context *c, int argc, char **argv);
void	free_context(t_context *c);
int		get_now_time(uint64_t *t);
#endif
