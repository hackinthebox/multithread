A simple thread example. 

A single argument is passed to the thread. This is passed as a void pointer and then type cast back to the integer type and printed to stdout.
The thread is then cleaned up with pthread_join.
