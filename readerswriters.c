#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include <semaphore.h>
#include <errno.h>

#define SIZE 20

volatile int readcnt = 0; /* Initially = 0 */
sem_t mutex, w; /* Initially = 1 */

int buffer[SIZE];

void writer(int n)
{
	for (int i = 0; i < SIZE; i++) {
		sem_wait(&mutex);
		readcnt++;
		
		if (readcnt == 1) /* First in */
			sem_wait(&w);
		sem_post(&mutex);

		//printf("%d\n", buffer[1]);
		buffer[i] = n;
		//n += increment;

		sem_wait(&mutex);
		readcnt--;
		
		if (readcnt == 0) /* Last out */
			sem_post(&w);
		sem_post(&mutex);
	}
}

void reader(void)
{
	for (int i = 0; i < SIZE; i++) {
		sem_wait(&w);
		
		printf("%d\n", buffer[1]);
 
		sem_post(&w);
	}
}

void *thread(void *vargp)
{
 	long input = *((long *)vargp);
	
	writer(input);
	reader();
} 

int main(int argc, char **argv)
{
	long input;
 	
	pthread_t tid1, tid2, tid3, tid4, tid5;
 	input = atoi(argv[1]);

 	sem_init(&mutex, 0, 1); 
	sem_init(&w, 0, 1); 

	pthread_create(&tid1, NULL, thread, &input);
 	pthread_create(&tid2, NULL, thread, &input);
	pthread_create(&tid3, NULL, thread, &input);
	pthread_create(&tid4, NULL, thread, &input);
	pthread_create(&tid5, NULL, thread, &input);
	pthread_join(tid1, NULL);
	pthread_join(tid2, NULL);
	pthread_join(tid3, NULL);
	pthread_join(tid4, NULL);
	pthread_join(tid5, NULL);

	//printf("cnt=%ld\n", cnt);
}
