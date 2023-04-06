/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aigounad <aigounad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 05:51:25 by aigounad          #+#    #+#             */
/*   Updated: 2023/04/06 18:12:43 by aigounad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_init_semaphores(t_data *data)
{
	sem_unlink(SEM_WRITE);
	data->a.sem_write = sem_open(SEM_WRITE, O_CREAT | O_EXCL, SEM_PERMS, 1);
	if (data->a.sem_write == SEM_FAILED)
		return (ft_error("sem_open failed1"));
	sem_unlink(SEM_DEAD);
	data->a.sem_dead = sem_open(SEM_DEAD, O_CREAT | O_EXCL, SEM_PERMS, 1);
	if (data->a.sem_dead == SEM_FAILED)
		return (ft_error("sem_open failed2"));
	sem_unlink(SEM_FORK);
	data->a.sem_forks = sem_open(SEM_FORK, O_CREAT | O_EXCL, SEM_PERMS,
			data->a.total);
	if (data->a.sem_forks == SEM_FAILED)
		return (ft_error("sem_open failed3"));
	return (0);
}

int	ft_init_philos(t_data *data)
{
	int		i;
	char	sem_name[64];

	i = 0;
	while (i < data->a.total)
	{
		data->ph[i].nbr = i + 1;
		data->ph[i].pa = &data->a;
		data->ph[i].eat_count = 0;
		generate_sem_name(SEM_LAST_EAT, sem_name, i);
		sem_unlink(sem_name);
		data->ph[i].sem_last_eat = sem_open(sem_name, O_CREAT | O_EXCL,
				SEM_PERMS, 1);
		if (data->ph[i].sem_last_eat == SEM_FAILED)
			return (ft_error("sem_open failed5"));
		generate_sem_name(SEM_FINISH, sem_name, i);
		sem_unlink(sem_name);
		data->ph[i].sem_finish = sem_open(sem_name, O_CREAT | O_EXCL,
				SEM_PERMS, 1);
		if (data->ph[i].sem_finish == SEM_FAILED)
			return (ft_error("sem_open failed"));
		sem_wait(data->ph[i].sem_finish);
		i++;
	}
	return (0);
}

int	ft_init(t_data *data, int ac, char **av)
{
	data->a.total = (int)ft_atoi(av[1]);
	data->a.t_to_die = ft_atoi(av[2]);
	data->a.t_to_eat = ft_atoi(av[3]);
	data->a.t_to_slp = ft_atoi(av[4]);
	if (ac == 6)
		data->a.must_eat = (int)ft_atoi(av[5]);
	else
		data->a.must_eat = -1;
	if (ft_init_semaphores(data))
		return (1);
	sem_wait(data->a.sem_dead);
	return (0);
}
