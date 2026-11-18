
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define N 5

sem_t room;
sem_t fork[N];

void *philosopher(void *arg)
{
    int id = *(int *)arg;

    printf("Philosopher %d is thinking.\n", id);

    sem_wait(&room);

    sem_wait(&fork[id]);
    sem_wait(&fork[(id + 1) % N]);

    printf("Philosopher %d is eating.\n", id);
    sleep(1);

    printf("Philosopher %d finished eating.\n", id);

    sem_post(&fork[id]);
    sem_post(&fork[(id + 1) % N]);

    sem_post(&room);

    return NULL;
}

int main()
{
    pthread_t t[N];
    int id[N], i;

    sem_init(&room, 0, 4);

    for(i = 0; i < N; i++)
        sem_init(&fork[i], 0, 1);

    for(i = 0; i < N; i++)
    {
        id[i] = i;
        pthread_create(&t[i], NULL, philosopher, &id[i]);
    }

    for(i = 0; i < N; i++)
        pthread_join(t[i], NULL);

    for(i = 0; i < N; i++)
        sem_destroy(&fork[i]);

    sem_destroy(&room);

    return 0;
}


gcc dining.c -o dining -pthread
./dining