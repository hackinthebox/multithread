Simple Mutex example.

Create 10 threads. Each thread will print out 5 numbers individually. 

To ensure each thread prints its list of numbers un-interrupted.
Threads will need to acquire a mutex lock before calling the print function.
