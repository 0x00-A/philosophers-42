/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aigounad <aigounad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 01:10:52 by aigounad          #+#    #+#             */
/*   Updated: 2023/04/08 13:59:00 by aigounad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_error(char *error)
{
	if (error)
		printf("%s\n", error);
	return (1);
}

long int	actual_time(void)
{
	long int		time;
	struct timeval	curr_time;

	if (gettimeofday(&curr_time, NULL) == -1)
		return (1);
	time = (curr_time.tv_sec * 1000) + (curr_time.tv_usec / 1000);
	return (time);
}
