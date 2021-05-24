#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include <semaphore.h>
#include <errno.h>

#define SIZE 21
#define SECTION_SIZE 5

volatile int cnt = 1;

typedef struct {
 	int *buf; /* Buffer array */
 	int n; /* Maximum number of slots */
 	int front; /* buf[(front+1)%n] is first item */
 	int rear; /* buf[rear%n] is last item */
 	sem_t mutex; /* Protects accesses to buf */
 	sem_t slots; /* Counts available slots */
 	sem_t items; /* Counts available items */
} sbuf_t;

void sbuf_init(sbuf_t *sp, int n)
{
 	sp->buf = calloc(n, sizeof(int));
 	sp->n = n; /* Buffer holds max of n items */
 	sp->front = sp->rear = 0; /* Empty buffer iff front == rear */
 	sem_init(&sp->mutex, 0, 1); /* Binary semaphore for locking */
 	sem_init(&sp->slots, 0, n); /* Initially, buf has n empty slots */
 	sem_init(&sp->items, 0, 0); /* Initially, buf has 0 items */
}

void sbuf_deinit(sbuf_t *sp)
{
 	free(sp->buf);
}

void sbuf_insert(sbuf_t *sp, int item)
{
 	sem_wait(&sp->slots); /* Wait for available slot */
 	sem_wait(&sp->mutex); /* Lock the buffer */
 	sp->buf[(++sp->rear)%(sp->n)] = item; /* Insert the item */
 	sem_post(&sp->mutex); /* Unlock the buffer */
 	sem_post(&sp->items); /* Announce available item */
}

int sbuf_remove(sbuf_t *sp)
{
 	int item;
 	sem_wait(&sp->items); /* Wait for available item */
 	sem_wait(&sp->mutex); /* Lock the buffer */
 	item = sp->buf[(++sp->front)%(sp->n)]; /* Remove the item */
 	sem_post(&sp->mutex); /* Unlock the buffer */
 	sem_post(&sp->slots); /* Announce available slot */
 	return item;
}

void *thread(void *buffer)
{
 	long i; 
	sbuf_t *buf = buffer;

 	for (i = 0; i < SECTION_SIZE; i++)
	{
		sbuf_insert(buf, cnt);
	}

	sem_wait(&buf->mutex);
	cnt++;
	sem_post(&buf->mutex);
} 

int main()
{
	sbuf_t *new_buf;
 	
	pthread_t tid1, tid2, tid3, tid4;
	sbuf_init(new_buf, 21);

	pthread_create(&tid1, NULL, thread, new_buf);
 	pthread_create(&tid2, NULL, thread, new_buf);
	pthread_create(&tid3, NULL, thread, new_buf);
	pthread_create(&tid4, NULL, thread, new_buf);
	pthread_join(tid1, NULL);
	pthread_join(tid2, NULL);
	pthread_join(tid3, NULL);
	pthread_join(tid4, NULL);

	for (int i = 0; i < SIZE; i++)
	{
		printf("%d\n", new_buf->buf[i]);
	}
}
