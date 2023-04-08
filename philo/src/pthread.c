/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pthread.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aigounad <aigounad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 10:27:04 by aigounad          #+#    #+#             */
/*   Updated: 2023/04/08 13:19:19 by aigounad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_create_threads(t_data *data)
{
	pthread_t	thr_id;
	int			i;

	i = 0;
	if (data->arg.each_must_eat > 0)
	{
		if (pthread_create(&thr_id, NULL, &check_finish, data) != 0)
			return (ft_error("pthread create error"));
		pthread_detach(thr_id);
	}
	while (i < data->arg.total)
	{
		if (pthread_create(&thr_id, NULL, &routine, &data->ph[i]) != 0)
			return (ft_error("pthread create error"));
		pthread_detach(thr_id);
		// usleep(100);
		i++;
	}
	return (0);
}
