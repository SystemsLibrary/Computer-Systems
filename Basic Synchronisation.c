#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include <semaphore.h>
#include <errno.h>

void *thread(void *vargp);

volatile long cnt = 0; /* Counter */
sem_t mutex; 

void *thread(void *vargp)
{
 	long i, niters = *((long *)vargp);

 	for (i = 0; i < niters; i++)
	{
		sem_wait(&mutex);
 		cnt++;
		sem_post(&mutex);
	}
} 

int main(int argc, char **argv)
{
	long niters;
 	
	pthread_t tid1, tid2, tid3, tid4, tid5;
 	niters = atoi(argv[1]);

 	sem_init(&mutex, 0, 1); 

	pthread_create(&tid1, NULL, thread, &niters);
 	pthread_create(&tid2, NULL, thread, &niters);
	pthread_create(&tid3, NULL, thread, &niters);
	pthread_create(&tid4, NULL, thread, &niters);
	pthread_create(&tid5, NULL, thread, &niters);
	pthread_join(tid1, NULL);
	pthread_join(tid2, NULL);
	pthread_join(tid3, NULL);
	pthread_join(tid4, NULL);
	pthread_join(tid5, NULL);

	printf("cnt=%ld\n", cnt);
}
