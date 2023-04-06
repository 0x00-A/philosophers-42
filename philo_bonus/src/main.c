/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aigounad <aigounad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 01:41:35 by aigounad          #+#    #+#             */
/*   Updated: 2023/04/06 18:16:14 by aigounad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*death_monitor(void *arg)
{
	t_philo	*ph;

	ph = (t_philo *)arg;
	while (1)
	{
		sem_wait(ph->sem_last_eat);
		if (actual_time() > ph->last_eat + ph->pa->t_to_die)
		{
			status("died", ph, 1);
			sem_post(ph->sem_last_eat);
			sem_post(ph->pa->sem_dead);
			return (NULL);
		}
		sem_post(ph->sem_last_eat);
		usleep(1000);
	}
	return (NULL);
}

void	*monitor_finish(void *arg)
{
	t_data	*data;
	int		i;

	i = 0;
	data = (t_data *)arg;
	while (i < data->a.total)
	{
		sem_wait(data->ph[i].sem_finish);
		sem_post(data->ph[i].sem_finish);
		i++;
	}
	sem_post(data->a.sem_dead);
	return (NULL);
}

void	routine(t_philo *ph)
{
	pthread_t	tid;

	ph->last_eat = actual_time();
	ph->start = actual_time();
	if (pthread_create(&tid, NULL, &death_monitor, ph) != 0)
		exit(1);
	pthread_detach(tid);
	while (1)
	{
		eat_sleep_think(ph);
		sem_wait(ph->sem_last_eat);
		if (ph->eat_count == ph->pa->must_eat)
		{
			sem_post(ph->sem_finish);
			return ;
		}
		sem_post(ph->sem_last_eat);
	}
}

int	ft_init_process(t_data *data)
{
	pthread_t	tid;
	int			i;

	if (data->a.must_eat > 0)
	{
		if (pthread_create(&tid, NULL, &monitor_finish, data) != 0)
			return (ft_error("pthread_creat error"));
		pthread_detach(tid);
	}
	i = 0;
	while (i < data->a.total)
	{
		data->ph[i].pid = fork();
		if (data->ph[i].pid == -1)
			return (ft_error("fork error"));
		else if (data->ph[i].pid == 0)
		{
			routine(&data->ph[i]);
			exit(0);
		}
		// usleep(100);
		i++;
	}
	return (0);
}

int	main(int ac, char **av)
{
	t_data		data;
	int			i;

	if (ft_parse_input(ac, av))
		return (1);
	if (ft_init(&data, ac, av))
		return (1);
	data.ph = malloc(sizeof(t_philo) * data.a.total);
	if (!data.ph)
		return (ft_error("malloc error"));
	if (ft_init_philos(&data) || ft_init_process(&data))
	{
		free(data.ph);
		return (1);
	}
	sem_wait(data.a.sem_dead);
	sem_post(data.a.sem_dead);
	i = 0;
	while (i < data.a.total)
	{
		kill(data.ph[i].pid, SIGKILL);
		i++;
	}
	ft_free(&data);
	return (0);
}
