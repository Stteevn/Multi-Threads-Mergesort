# OS Bonus1 Report

*唐千栋 11612730*

### Implement

This is a multithreading version merge sort. We would use pthread in this program.

1. When the array is divided into a sub-array which has less than 5 elements, we would use `qsort()` to increase performance. 
2. We would use global array instead of dynamic allocating local array.
3. When we need to copy array to a new array, we would use `memcpy()`

### Input

```bash
$ ./mergesort n thread
```

n is the length of array

thread is the max number of thread.

### Output



size is the length of array

the second line is the number of thread created

the third line would return true if the sort result is true, else false

the fourth line is time for this program.

### Experiment

The program would randomly choose n numbers. 

experiment machine is i7 4-core

| n/thread | 1      | 2      | 4      | 8      | 16     |
| -------- | ------ | ------ | ------ | ------ | ------ |
| 10k      | 1ms    | 1ms    | 1ms    | 1ms    | 5ms    |
| 100k     | 7ms    | 6ms    | 5ms    | 5ms    | 2ms    |
| 1m       | 29ms   | 16ms   | 14ms   | 9ms    | 9ms    |
| 10m      | 315ms  | 176ms  | 108ms  | 95ms   | 88ms   |
| 100m     | 3889ms | 2209ms | 1390ms | 1125ms | 1101ms |

When the array size is small, the performance of different thread is almost the same.

When the array size is larger than 10m, the performance of multithreads is greatly better than single thread.

When the number of threads increases, the performance also increases. The consuming time with two threads is about half of the time with single thread. And the consuming time with four threads is also about half of the time with two threads. However, when the thread is greater than 4, the improved efficiency is not that obvious. 

The reason why improved efficiency is not obvious when thread is greater than 4 is mainly because the number of processor is smaller than the number of threads, then these 8 threads can not run parallel at the same time.

The reason why consuming time with two threads is not exactly half of the time with single thread is because thread switching would consume some extra time.
