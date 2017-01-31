Create a pool of threads.

Once 10 threads have been generated.
Each thread will generate 2 random numbers and print these out.

Add a barrier function to wait for all threads to be created before printing random numbers.

Added 2 pthread barriers. 
	One to wait for all threads to spawn before printing 
	One for waiting for the threads to complete before calling pthread_join. (Although technically not required, it's an example of syncing the cleanup if threads were persistent).
