Mutex Examples 

Static Mutex:
Create a pool of 10 threads , each of the threads will print a list of random numbers. 
Each thread must acquire the lock so that only one thread prints numbers at a time.

Dynamic Mutex: 
Create a pool of 10 threads , each of the threads will access elements in an array of data structures. To ensure there is no data corruption between threads, the thread will acquire a lock on each individual data structure.
