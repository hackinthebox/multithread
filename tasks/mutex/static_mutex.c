#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>

#define MAXTHREADS 10

// Initialize a static mutex type
pthread_mutex_t lck = PTHREAD_MUTEX_INITIALIZER;

void *threadFunc(void *id){
	int num = *((int*)id);
// Acquire the static lock before printing the numbers 
	pthread_mutex_lock(&lck);
	printf("\nThread %d has acquired the lock\n",num);
	for(int i=1; i<6; i++){
	int random = (rand() %100);
	printf("[%d]:%d\n",num,random);
	}
// Release the static lock for the next thread before returning
	pthread_mutex_unlock(&lck);
}


int main(){
	pthread_t tid[MAXTHREADS];

	srand((unsigned) time(0));

// Create a seperate memory space for referencing the thread numbers, prevents the thread_num being overwritten before the threads have a chance to read from the memory space
	int thread_num[MAXTHREADS+1];
	
	for ( int i=0; i<MAXTHREADS; i++) {
		thread_num[i] = i+1;
		pthread_create(&tid[i], NULL, threadFunc, &thread_num[i]);
	}

	for ( int i=0; i<MAXTHREADS; i++) {
		pthread_join(tid[i], NULL);
	}
	exit(0);
}
