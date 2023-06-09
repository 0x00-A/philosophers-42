/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aigounad <aigounad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 12:12:23 by aigounad          #+#    #+#             */
/*   Updated: 2023/04/08 13:59:44 by aigounad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	status(char *s, t_philo *ph, int i);

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
	pthread_mutex_lock(&ph->l_fork);
	status("has taken a fork", ph, 0);
	if (ph->pa->total == 1)
	{
		pthread_mutex_unlock(&ph->l_fork);
		usleep(ph->pa->t_to_die * 1000);
		return (1);
	}
	pthread_mutex_lock(ph->r_fork);
	status("has taken a fork", ph, 0);
	status("is eating", ph, 0);
	ph->meals_count++;
	pthread_mutex_lock(&ph->lock);
	ph->t_lst_meal = actual_time();
	pthread_mutex_unlock(&ph->lock);
	ft_usleep(ph->pa->t_to_eat);
	pthread_mutex_unlock(&ph->l_fork);
	pthread_mutex_unlock(ph->r_fork);
	status("is sleeping", ph, 0);
	ft_usleep(ph->pa->t_to_sleep);
	status("is thinking", ph, 0);
	return (0);
}

void	status(char *s, t_philo *ph, int i)
{
	static int	stop;

	pthread_mutex_lock(&ph->pa->write);
	if (stop == 0)
	{
		printf("%ld %d %s\n", actual_time() - ph->t_start, ph->philo_nb, s);
		if (i == 1)
		{
			stop = 1;
		}
	}
	pthread_mutex_unlock(&ph->pa->write);
}
