#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>

#define MAXTHREADS 10

// Create a simple data structure prototype 
struct data_array {
	int count;
	pthread_mutex_t	lock;
} data[5];


void *threadFunc(void *id){
	int num = *((int*)id);	
// Create a loop , each thread will update the count of one of the data structs at random with a random value 0-100, adding to the existing value.
	for(int a=0; a<5; a++){
	int rand_count = (rand() %100);
	int rand_ptr = (rand() %5);
// Acquia the data struct lock before updating the data struct
	pthread_mutex_lock(&data[rand_ptr].lock);
	printf("[%d]: Locked struct %d\n",num,rand_ptr);
	printf("[%d]: Updating struct %d , adding %d to count\n",num,rand_ptr,rand_count);
	data[rand_ptr].count = data[rand_ptr].count + rand_count;
// Release the data struct lock
	pthread_mutex_unlock(&data[rand_ptr].lock);
	}
}


int main(){
	pthread_t tid[MAXTHREADS];

// Seed the random number generator
	srand((unsigned) time(0));

// We must initialize count to 0 , incase the random struct pointer doesn't hit every struct.
	for ( int i=0; i<5; i++ ){
		data[i].count = 0;
	}

// Create an array of data structs to play with, this is done statically instead of on the heap for simples
// Initate the mutex locks in the data structure
	for ( int i=0; i<5; i++ ) {
		pthread_mutex_init(&data[i].lock, NULL);
	}

// Create a memory location to store the thread id's to prevent overwrites
	int thread_num[MAXTHREADS];
	
	for ( int i=0; i<MAXTHREADS; i++) {
		thread_num[i] = i+1;
		pthread_create(&tid[i], NULL, threadFunc, &thread_num[i]);
	}

	for ( int i=0; i<MAXTHREADS; i++) {
		pthread_join(tid[i], NULL);
	}
// Print out the completed data structs
	for ( int i=0; i<5; i++) {
		printf("Data[%d] count = %d\n",i,data[i].count);
	}
	exit(0);

}
