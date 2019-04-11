This C program uses the POSIX threads programming interface to demonstrate how multiple threads can perform synchronized access to shared data using a pthreads mutex and barrier.

Usage: ./simplethread 10

where 10 is the number of threads to create. In turn, each thread is responsible for incrementing a shared int variable by 1 for a total of 20 times.

A pthreads mutex is used to ensure that each iteration of the loop in the simpleThread() function increments the variable by exactly one. A pthreads barrier is used to ensure that each thread sees the same final value.
