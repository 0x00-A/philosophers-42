/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sem.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aigounad <aigounad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 07:29:46 by aigounad          #+#    #+#             */
/*   Updated: 2023/04/03 09:35:23 by aigounad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <semaphore.h>

#define SEM_VALUE 1
#define SEM_NAME "/semaphore"
#define SEM_PERM 0660

void	fun()
{
	system("leaks a.out");
}

void	child_routine(sem_t *sem)
{
	printf("in child\n");
	sem_wait(sem);
	printf("in critical section\n");
	sem_post(sem);
	printf("out of critical section\n");
	exit(0);
}

int	main()
{
	// atexit(fun);
	pid_t	chl_pid;
	sem_t 	*sem;

	sem = sem_open(SEM_NAME, O_CREAT, SEM_PERM, SEM_VALUE);
	if (sem == SEM_FAILED)
	{
		printf("sem_open() failed\n");
		exit(1);
	}

	chl_pid = fork();
	if (chl_pid == -1)
	{
		printf("fork() returned -1\n");
		exit(1);
	}
	else if (chl_pid == 0)
	{
		child_routine(sem);
	}

		wait(NULL);
		sem_close(sem);
		sem_unlink(SEM_NAME);
	return (0);
}
