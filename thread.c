#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
// Simple example of creating a thread and passing some arguments to the thread function.

// Create a function pointer that will be initiated with the thread.
// To pass arguments to the thread, we need to use an arg type of void, then type cast to the correct type within the function. 
// When dealing with multiple arguments, we will use a struct to hold the argument values.
void *threadfunc(void *num){
// as we passed the address of i, here we type cast a to derefence the variable of type integer pointer. :)
	int a = *((int*)num);
	printf("Thread: The number is %d\n",a);
	return(NULL);
}

int main(){
	int i = 5;

// tid is an integer to identify the thread in the system.
	pthread_t tid;
	printf("Main function creating a thread...\n");

// creating the thread. Synopsis : 

// int pthread_create(pthread_t *thread, const pthread_attr_t *attr,
//    void *(*start_routine)(void*), void *arg);

// 1st arg is a pointer to the thread id , which is set by the function
// 2nd arg for the thread attributes, passing NULL uses the system default attributes.
// 3rd arg is the name of the function to be executed by the thread created.
// 4th arg is used to pass arguments to the thread, here we pass the address of integer i. 
	pthread_create(&tid, NULL, threadfunc, &i);
// pthread_join is the quivilent of wait for processes. This blocks the calling thread until the thread with id tid terminates.
	pthread_join(tid, NULL);
	printf("Main function thread completed.\n");
	exit(0);
}
