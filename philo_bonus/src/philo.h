/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aigounad <aigounad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 18:18:22 by aigounad          #+#    #+#             */
/*   Updated: 2023/04/06 18:18:54 by aigounad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

//includes
# include <pthread.h>
# include <semaphore.h>
# include <stdio.h>
# include <signal.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>

# include <fcntl.h>           /* For O_* constants */
# include <sys/stat.h>

# define SEM_WRITE "/sem_write"
# define SEM_FINISH "/sem_finish"
# define SEM_DEAD "/sem_dead"
# define SEM_FORK "/sem_fork"
# define SEM_LAST_EAT "/sem_last_eat"
# define SEM_LOCK "/sem_lock"

# define SEM_PERMS 0664

//structs
typedef struct s_args{
	int			total;
	long int	t_to_die;
	long int	t_to_slp;
	long int	t_to_eat;
	int			must_eat;
	sem_t		*sem_write;
	sem_t		*sem_dead;
	sem_t		*sem_forks;
}	t_args;

typedef struct s_philo{
	pid_t		pid;
	t_args		*pa;
	int			nbr;
	int			eat_count;
	long int	last_eat;
	long int	start;
	sem_t		*sem_last_eat;
	sem_t		*sem_finish;
	int			done;
}	t_philo;

typedef struct s_data{
	t_philo		*ph;
	t_args		a;
}	t_data;

//prototypes
long int		ft_atoi(const char *str);
long int		actual_time(void);
int				ft_error(char *error);
int				ft_parse_input(int ac, char **av);
int				ft_init(t_data *data, int ac, char **av);
int				ft_init_philos(t_data *data);
void			generate_sem_name(char *src, char *dst, int j);
void			ft_usleep(long int time_to_sleep);
int				eat_sleep_think(t_philo *ph);
void			status(char *info, t_philo *ph, int i);
void			ft_free(t_data *data);

#endif
