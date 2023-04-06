/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat_sleep_think.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aigounad <aigounad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 17:47:51 by aigounad          #+#    #+#             */
/*   Updated: 2023/04/06 17:48:03 by aigounad         ###   ########.fr       */
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
	usleep(ph->pa->t_to_eat * 1000);
	sem_post(ph->pa->sem_forks);
	sem_post(ph->pa->sem_forks);
	status("is sleeping", ph, 0);
	usleep(ph->pa->t_to_slp * 1000);
	status("is thinking", ph, 0);
	return (0);
}
