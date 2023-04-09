/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat_sleep_think.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aigounad <aigounad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 17:47:51 by aigounad          #+#    #+#             */
/*   Updated: 2023/04/09 12:37:21 by aigounad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	status(char *info, t_philo *ph, int i)
{
	static int	done;

	sem_wait(ph->pa->sem_write);
	if (done == 0)
	{
		printf("%ld %d %s\n", actual_time() - ph->start, ph->nbr, info);
		if (i == 1)
		{
			done = 1;
			return ;
		}
	}
	sem_post(ph->pa->sem_write);
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

int	eat_sleep_think(t_philo *ph)
{
	sem_wait(ph->pa->sem_forks);
	status("has taken a fork", ph, 0);
	sem_wait(ph->pa->sem_forks);
	status("has taken a fork", ph, 0);
	status("is eating", ph, 0);
	sem_wait(ph->sem_last_eat);
	ph->last_eat = actual_time();
	ph->eat_count++;
	sem_post(ph->sem_last_eat);
	ft_usleep(ph->pa->t_to_eat);
	sem_post(ph->pa->sem_forks);
	sem_post(ph->pa->sem_forks);
	status("is sleeping", ph, 0);
	ft_usleep(ph->pa->t_to_slp);
	status("is thinking", ph, 0);
	return (0);
}
