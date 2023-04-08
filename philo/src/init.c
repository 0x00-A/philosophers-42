/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aigounad <aigounad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 10:13:30 by aigounad          #+#    #+#             */
/*   Updated: 2023/04/08 14:16:32 by aigounad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_init_args(int ac, char **av, t_data *data)
{
	data->arg.total = (int)ft_atoi(av[1]);
	data->arg.t_to_die = ft_atoi(av[2]);
	data->arg.t_to_eat = ft_atoi(av[3]);
	data->arg.t_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		data->arg.each_must_eat = (int)ft_atoi(av[5]);
	else
		data->arg.each_must_eat = -1;
	pthread_mutex_init(&data->arg.write, NULL);
	pthread_mutex_init(&data->arg.dead, NULL);
	pthread_mutex_lock(&data->arg.dead);
}

int	ft_init_philos(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->arg.total)
	{
		data->ph[i].pa = &data->arg;
		data->ph[i].philo_nb = i + 1;
		data->ph[i].meals_count = 0;
		data->ph[i].t_start = actual_time();
		pthread_mutex_init(&data->ph[i].lock, NULL);
		pthread_mutex_init(&data->ph[i].l_fork, NULL);
		pthread_mutex_init(&data->ph[i].finish, NULL);
		pthread_mutex_lock(&data->ph[i].finish);
		if (data->arg.total == 1)
			return (0);
		if (i == data->arg.total - 1)
			data->ph[i].r_fork = &data->ph[0].l_fork;
		else
			data->ph[i].r_fork = &data->ph[i + 1].l_fork;
		i++;
	}
	return (0);
}
