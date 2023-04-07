/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aigounad <aigounad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 18:13:15 by aigounad          #+#    #+#             */
/*   Updated: 2023/04/06 18:13:40 by aigounad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_free(t_data *data)
{
	int		i;

	sem_close(data->a.sem_dead);
	sem_close(data->a.sem_forks);
	sem_close(data->a.sem_write);
	i = 0;
	while (i < data->a.total)
	{
		sem_close(data->ph[i].sem_finish);
		sem_close(data->ph[i].sem_last_eat);
		i++;
	}
	free(data->ph);
}
