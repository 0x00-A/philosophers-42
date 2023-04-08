/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aigounad <aigounad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 11:34:59 by aigounad          #+#    #+#             */
/*   Updated: 2023/04/08 13:40:48 by aigounad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <pthread.h>
# include <time.h>
# include <sys/time.h>

typedef struct s_args{
	int				total;
	long int		t_to_die;
	long int		t_to_eat;
	long int		t_to_sleep;
	long int		each_must_eat;
	pthread_mutex_t	dead;
	pthread_mutex_t	write;
}	t_args;

typedef struct s_philo{
	int				philo_nb;
	t_args			*pa;
	pthread_mutex_t	l_fork;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	finish;
	int				meals_count;
	pthread_mutex_t	lock;
	long int		t_lst_meal;
	long int		t_start;
}	t_philo;

typedef struct s_data{
	t_philo		*ph;
	t_args		arg;
}	t_data;

int				ft_parse_input(int ac, char **av);
long int		ft_atoi(const char *str);
int				ft_error(char *error);
int				eat_sleep_think(t_philo *ph);
long int		actual_time(void);
void			ft_init_args(int ac, char **av, t_data *data);
int				ft_init_philos(t_data *data);
int				ft_create_threads(t_data *data);
void			*routine(void *arg);
void			*check_finish(void *arg);

void			status(char *s, t_philo *ph, int i);

#endif
