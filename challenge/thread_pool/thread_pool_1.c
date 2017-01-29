#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#define MAXTHREADS 10

// This example will spawn 10 threads , which will stay alive until the process completes.
// This shows why it is necessary to track thread progress in main , as the process could return before the threads have completed.
// pthread_join will block until the thread returns or is canceled

void *threadFunc(void *id){
	int num = *((int*)id);
	printf("Thread %d has been created\n", num);
	pthread_t a = pthread_self();
	printf("value: %lu\n",(unsigned long)a);
// keep thread alive
	while(1){
	}
}

int main(){
// 10 threads id array
	pthread_t tid[MAXTHREADS];

	for ( int i=0; i<MAXTHREADS; i++) {
		printf("Creating thread %d...\n", i);
		pthread_create(&tid[i], NULL, threadFunc, &i);
// we add a sleep to ensure the threads have time to spawn before the process completes and exits.
		sleep(1);
	}
	printf("All threads have now spawned\n");
	exit(0);
}
