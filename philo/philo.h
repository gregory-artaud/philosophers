/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gartaud <gartaud@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/05 10:13:35 by gartaud           #+#    #+#             */
/*   Updated: 2021/09/16 13:41:35 by gartaud          ###   ########lyon.fr   */
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

typedef u_int64_t	uint64_t;

enum e_actions
{
	EAT,
	DIE,
	TAKE_FORK,
	SLEEP,
	THINK,
	DROP,
	MAX_EAT
};

typedef struct s_philo
{
	int					id;
	int					is_eating;
	int					eat_count;
	int					lfork;
	int					rfork;
	int					is_dead;
	pthread_t			th;
	uint64_t			last_eat;
	struct s_context	*context;
	pthread_mutex_t		mutex;
	pthread_mutex_t		death_m;
	pthread_mutex_t		eat_m;
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
}					t_context;

/*
** lib
*/
int			ft_atoi(const char *s);
int			ft_is_number(char *s);
/*
** init
*/
int			init_context(t_context *c, int argc, char **argv);
void		free_context(t_context *c);
long int	get_absolute_time(void);
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
/*
** ft_usleep
*/
void		ft_usleep(long int time_in_ms);
/*
** is_somebody_dead
*/
int			is_somebody_dead(t_context *c);
/*
** accessors
*/
void		set_death(t_philo *p, int value);
int			get_death(t_philo *p);
void		add_eat(t_philo *p);
int			get_eat(t_philo *p);
#endif
