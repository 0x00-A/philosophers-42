#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <semaphore.h>
#include <fcntl.h>

#define SEM_NAME "/mysemaphore"
#define SEM_PERMS (S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP)
#define SEM_INIT_VALUE 1

void child_process(sem_t *sem)
{
    printf("Child process: waiting for semaphore...\n");
    sem_wait(sem); // wait for semaphore

    printf("Child process: acquired semaphore!\n");
    // access shared resource here

    sem_post(sem); // release semaphore
    printf("Child process: released semaphore.\n");

    exit(0);
}

int main()
{
    sem_t *sem;
    pid_t pid;

    // create a named semaphore
    sem = sem_open(SEM_NAME, O_CREAT | O_EXCL, SEM_PERMS, SEM_INIT_VALUE);
    if (sem == SEM_FAILED) {
        perror("sem_open() failed");
        exit(1);
    }

    // fork a child process
    // pid = fork();
    // if (pid == -1) {
    //     perror("fork() failed");
    //     exit(1);
    // } else if (pid == 0) {
    //     // child process
    //     child_process(sem);
    // }

    // parent process
    printf("Parent process: waiting for semaphore...\n");
    sem_wait(sem); // wait for semaphore

    printf("Parent process: acquired semaphore!\n");
    sem_wait(sem); // wait for semaphore

    printf("Parent process: acquired semaphore 2!\n");
    // access shared resource here

    sem_post(sem); // release semaphore
    printf("Parent process: released semaphore.\n");

    // wait for child process to finish
    wait(NULL);

    // close and unlink the semaphore
    sem_close(sem);
    sem_unlink(SEM_NAME);

    return 0;
}
