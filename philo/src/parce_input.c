/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parce_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aigounad <aigounad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 10:12:43 by aigounad          #+#    #+#             */
/*   Updated: 2023/04/01 11:16:21 by aigounad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long int	ft_atoi(const char *str)
{
	long int	r;

	r = 0;
	while (*str && (*str >= '0' && *str <= '9'))
	{
		r = r * 10 + (*str - '0');
		str++;
	}
	return (r);
}

int	ft_isdigit(char *s)
{
	while (*s)
	{
		if (!(*s >= '0' && *s <= '9'))
			return (0);
		s++;
	}
	return (1);
}

int	ft_parse_input(int ac, char **av)
{
	int	i;

	i = 1;
	if (ac < 5 || ac > 6)
		return (1);
	while (av[i])
	{
		if (av[i][0] == '+')
			av[i]++;
		if (ft_isdigit(av[i]) && ft_atoi(av[i]) > 0)
			i++;
		else
			return (ft_error("ERROR :INVALID ARGS!"));
	}
	return (0);
}
