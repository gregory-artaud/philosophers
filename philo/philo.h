/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gartaud <gartaud@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/05 10:13:35 by gartaud           #+#    #+#             */
/*   Updated: 2021/07/03 20:51:32 by gartaud          ###   ########lyon.fr   */
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

# define INT32_MAX INT_MAX

typedef u_int64_t uint64_t;

enum e_actions
{
	EAT,
	DIE,
	TAKE_FORK,
	SLEEP,
	THINK,
	MAX_EAT
};

typedef struct s_philo
{
	int					id;
	int					is_eating;
	int					eat_count;
	int					lfork;
	int					rfork;
	pthread_t			th;
	uint64_t			last_eat;
	struct s_context	*context;
	pthread_mutex_t		mutex;
}						t_philo;

typedef struct s_context
{
	int				no_philo;
	int64_t			time_to_die;
	int64_t			time_to_eat;
	int64_t			time_to_sleep;
	int				max_eat;
	pthread_mutex_t	*forks;
	t_philo			*philos;
	uint64_t		start;
	pthread_mutex_t	write_m;
	pthread_mutex_t	somebody_died;
}					t_context;

/*
** lib
*/
int			ft_atoi(const char *s);
/*
** init
*/
int			init_context(t_context *c, int argc, char **argv);
void		free_context(t_context *c);
int			get_absolute_time(uint64_t *t);
int			get_relative_time(uint64_t *t, uint64_t reference);
uint64_t	get_simulation_time(uint64_t reference);
/*
** is_finished
*/
int			is_finished(t_context *c);
/*
** actions
*/
int			p_die(t_philo *p);
int			p_eat(t_philo *p);
int			p_sleep(t_philo *p);
/*
** put_log
*/
void		put_log(t_philo *p, int type);
#endif
