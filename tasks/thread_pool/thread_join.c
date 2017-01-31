#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>

#define MAXTHREADS 10

// Create a pthread barrier type object

pthread_barrier_t barrier1, barrier2;

void *threadFunc(void *id){
	int num = *((int*)id);
	pthread_t a = pthread_self();
	printf("Thread %d has been created\n", num);
	printf("value: %lu\n",(unsigned long)a);
// Wait on the pthread barrier , for all 10 threads to initialize	
	pthread_barrier_wait(&barrier1);
	for(int i=1; i<3; i++){
	int random = (rand() %100);
	printf("Thread %d generated %d\n",num,random);
	sleep(2);
	}
	pthread_barrier_wait(&barrier2);
// Wait for all threads to complete before returning
}

int main(){
// 10 threads id array
	pthread_t tid[MAXTHREADS];

// Seed the random number generation with current time
	srand((unsigned) time(0));

// Initiate the pthread_barriers with the number of threads in use
	pthread_barrier_init(&barrier1, NULL, MAXTHREADS);
	pthread_barrier_init(&barrier2, NULL, MAXTHREADS+1);

	for ( int i=0; i<MAXTHREADS; i++) {
		printf("Creating thread %d...\n", i);
		pthread_create(&tid[i], NULL, threadFunc, &i);
		sleep(1);
	}

// Wait for all threads to complete, then call the pthread join loop
	pthread_barrier_wait(&barrier2);
	printf("Threads have completed, cleaning up the threads");
	
	for ( int i=0; i<MAXTHREADS; i++) {
		pthread_join(tid[i], NULL);
		printf("Thread %d has now returned\n",i);
	}
	exit(0);
}
