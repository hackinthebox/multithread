#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <unistd.h>

#define MAXTHREADS 2

// Create a static condition variable type
pthread_cond_t ready = PTHREAD_COND_INITIALIZER;

// Create a static mutex for protecting the condition variable
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

// Create the array which will be populated
int arr[10];

void *func_one(void *arg) {
	for ( int i=0; i<10; i++ ) { 
		arr[i] = 5;
		sleep(1);
	}
// Loop completed, signal to the condition variable that we're done
	pthread_cond_signal(&ready);
	
}

void *func_two(void *arg) {
// Wait on the condition variable 
	pthread_cond_wait(&ready,&lock);
	for ( int i=0; i<10; i++ ) { 
		printf("%d\n",arr[i]);
	}
	pthread_mutex_unlock(&lock);
}

int main() { 	
// Create 2 threads
	pthread_t tid[MAXTHREADS];
	pthread_create(&tid[0], NULL, func_one, NULL);
	printf("Thread 1 Created\n");
	pthread_create(&tid[1], NULL, func_two, NULL);
	printf("Thread 2 Created\n");
// Clean up threads
	for ( int i=0; i<MAXTHREADS; i++){ 
		pthread_join(tid[i], NULL);
		printf("Thread %d has been cleaned\n",i);
	}
	
}
