/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gartaud <gartaud@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/05 10:14:29 by gartaud           #+#    #+#             */
/*   Updated: 2021/09/30 09:28:45 by gartaud          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_isspace(char c)
{
	return (c == ' ' || c == '\n' || c == '\t' || c == '\r' || c == '\t'
		|| c == '\v' || c == '\f');
}

int	ft_isdigit(char c)
{
	return (c >= '0' && c <= '9');
}

int	ft_is_number(char *s)
{
	if (!s)
		return (0);
	while (*s)
		if (!ft_isdigit(*(s++)))
			return (0);
	return (1);
}

int	ft_atoi(const char *s)
{
	unsigned int	i;
	int				sgn;
	long long		res;

	i = 0;
	sgn = 1;
	res = 0;
	while (ft_isspace(s[i]))
		i++;
	if ((s[i] == '-') || (s[i] == '+'))
	{
		if (s[i] == '-')
			sgn = -1;
		i++;
	}
	while (s[i] && ft_isdigit(s[i]))
	{
		res = res * 10 + s[i++] - '0';
		if (res * sgn > INT_MAX)
			return (-1);
		else if (res * sgn < INT_MIN)
			return (0);
	}
	return (res * sgn);
}
