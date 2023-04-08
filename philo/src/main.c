/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aigounad <aigounad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 22:26:47 by aigounad          #+#    #+#             */
/*   Updated: 2023/04/08 14:14:43 by aigounad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*check_finish(void *arg)
{
	t_data	*data;
	int		i;

	i = 0;
	data = (t_data *)arg;
	while (i < data->arg.total)
	{
		pthread_mutex_lock(&data->ph[i].finish);
		pthread_mutex_unlock(&data->ph[i].finish);
		i++;
	}
	pthread_mutex_unlock(&data->arg.dead);
	return (NULL);
}

void	*check_death(void *arg)
{
	t_philo	*ph;

	ph = (t_philo *)arg;
	while (1)
	{
		pthread_mutex_lock(&ph->lock);
		if (actual_time() > ph->t_lst_meal + ph->pa->t_to_die)
		{
			status("died", ph, 1);
			pthread_mutex_unlock(&ph->pa->dead);
			pthread_mutex_unlock(&ph->lock);
		}
		pthread_mutex_unlock(&ph->lock);
		usleep(5000);
	}
	return (arg);
}

void	*routine(void *arg)
{
	pthread_t	thr_id;
	t_philo		*ph;

	ph = (t_philo *)arg;
	ph->t_lst_meal = actual_time();
	if (pthread_create(&thr_id, NULL, &check_death, ph) != 0)
		return (NULL);
	pthread_detach(thr_id);
	while (1)
	{
		if (eat_sleep_think(ph))
			break ;
		if (ph->meals_count == ph->pa->each_must_eat)
		{
			pthread_mutex_unlock(&ph->finish);
		}
	}
	return (NULL);
}

void	ft_free(t_data *data)
{
	int	i;

	pthread_mutex_destroy(&data->arg.dead);
	pthread_mutex_destroy(&data->arg.write);
	i = 0;
	while (i < data->arg.total)
	{
		pthread_mutex_destroy(&data->ph[i].l_fork);
		pthread_mutex_destroy(&data->ph[i].lock);
		pthread_mutex_destroy(&data->ph[i].finish);
		i++;
	}
	free(data->ph);
}

int	main(int ac, char **av)
{
	t_data	data;

	if (ft_parse_input(ac, av))
		return (1);
	ft_init_args(ac, av, &data);
	data.ph = malloc(sizeof(t_philo) * data.arg.total);
	if (!data.ph)
	{
		printf("error malloc\n");
		return (1);
	}
	if (ft_init_philos(&data) || ft_create_threads(&data))
	{
		free(data.ph);
		return (1);
	}
	pthread_mutex_lock(&data.arg.dead);
	pthread_mutex_unlock(&data.arg.dead);
	ft_free(&data);
	return (0);
}
