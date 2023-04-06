/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aigounad <aigounad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 06:56:56 by aigounad          #+#    #+#             */
/*   Updated: 2023/04/06 18:10:00 by aigounad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_error(char *error)
{
	printf("%s\n", error);
	return (1);
}

long int	actual_time(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) == -1)
		return (1);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	ft_usleep(long int time_to_sleep)
{
	long int	elapsed_time;
	long int	start_time;

	start_time = actual_time();
	elapsed_time = 0;
	while (elapsed_time < time_to_sleep)
	{
		usleep(time_to_sleep / 10);
		elapsed_time = actual_time() - start_time;
	}
}

void	generate_sem_name(char *src, char *dst, int j)
{
	int	i;

	i = 0;
	if (!src | !dst)
		return ;
	while (src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i++] = j + '0';
	dst[i] = 0;
}
