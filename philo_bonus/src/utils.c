/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aigounad <aigounad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 06:56:56 by aigounad          #+#    #+#             */
/*   Updated: 2023/04/06 16:12:08 by aigounad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_error(char *error)
{
	printf("%s\n", error);
	return (1);
}

long int actual_time(void)
{
	struct timeval tv;

	if (gettimeofday(&tv, NULL) == -1)
		return (1);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
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


// int	ft_strlen(char *str)
// {
// 	int	i;

// 	i = 0;
// 	while (str[i])
// 		i++;
// 	return (i);
// }

void	generate_sem_name(char *src, char *dst, int j)
{
	int	i;

	i = 0;
	if (!src | !dst)
		return ;
	while (src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i++] = j + '0';
	dst[i] = 0;
}

// int	main()
// {
// 	char	sem_name[64];
// 	int i = 1;

// 	generate_sem_name(SEM_LAST_EAT, sem_name, i);
// 	printf("%s\n", sem_name);
// }

// void	child_process(t_data *data)
// {
// 	sleep(2);
// 	sem_post(data->a.sem_write);
// 		printf("HEloo from child\n");
// }

// int	main()
// {
// 	t_data	data;
// 	pid_t	pid;
// 	sem_t	*sem;

// 	sem_unlink(SEM_WRITE);
// 	data.a.sem_write = sem_open(SEM_WRITE, O_CREAT | O_EXCL, SEM_PERMS, 1);
// 	if (data.a.sem_write == SEM_FAILED)
// 		return (ft_error("sem_open failed1"));
	
// 	sem_unlink(SEM_FINISH);
// 	data.a.sem_finish = sem_open(SEM_FINISH, O_CREAT | O_EXCL, SEM_PERMS, 1);
// 	if (data.a.sem_finish == SEM_FAILED)
// 		return (ft_error("sem_open failed2"));

// 	sem_wait(data.a.sem_write);
// 	pid = fork();
// 	if (pid == -1)
// 		return (ft_error("ford error"));
// 	else if (pid == 0)
// 	{
// 		child_process(&data);
// 		exit(0);
// 	}
// 	// wait(NULL);

// 	sem_wait(data.a.sem_write);
// 	printf("Hello\n");
// 	sem_post(data.a.sem_write);
// 	// sem_post(data.a.sem_write);
// 	// sem_wait(data.a.sem_finish);
// 	// printf("Hello2\n");
// 	// sem_post(data.a.sem_finish);
	
// 	// sem_unlink(SEM_WRITE);
// 	// sem_close(data.a.sem_write);
// 	sem_wait(data.a.sem_write);
// 	printf("Hello2\n");
// 	sem_post(data.a.sem_write);

// 	// generate_sem_name(sem_name, SEM_FINISH);
// 	// sem_unlink(sem_name);
	
// }