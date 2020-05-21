	Concurrent Quicksort
A concurrent algorithm is one that can be executed concurrently. Most standard computer algorithms are sequential algorithms and assume that the algorithm is run from start to finish without any other processes executing. These often do not behave correctly when run concurrently, as demonstrated at right, and are often nondeterministic, as the actual sequence of computations is determined by the external scheduler. Concurrency often adds significant complexity to an algorithm, requiring concurrency control such as mutual exclusion to avoid problems such as race conditions.
Concurrent Algorithm
	When ever you call my algorithm, you need to initialize the maximum number of threads you want the program to run. Whatever that value, is going to be stored in my thread_max variable which will hold that value. If it’s a concurrent, that value will be greater than 1 but if it’s a sequential, the value will be 0. I have a counter which is set 0. That counter will loop through the thread_max variable. Every time the quick sort function is called, the counter is incremented by a factor of 2. It will run until the counter reaches my thread_max value and then runs sequentially. The qsort runs 2 thread each time.

The difference between a concurrent and a sequential quicksort can be observed below, and it will be discussed.
List Size   Sequential Sort Time (s)   Concurrent Sort Time (s)
             min     max    average     min     max    average
---------   -----   -----   -------    -----   -----   -------
1           0.0000  0.0000  0.00000    0.0000  0.0000  0.00000
10          0.0000  0.0000  0.00000    0.0000  0.0000  0.00000
100         0.0000  0.0000  0.00000    0.0000  0.0000  0.00000
1000        0.0000  0.0000  0.00001    0.0000  0.0000  0.00001
10000       0.0001  0.0001  0.00010    0.0001  0.0011  0.00021
100000      0.0012  0.0012  0.00119    0.0012  0.0013  0.00120
1000000     0.0148  0.0161  0.01514    0.0108  0.0168  0.01480

The graph above compares the sequential and concurrent sort with their average time with various list size to determine which is faster.
List size from 1 – 1000:
When running my algorithm, with vector size from 1 to 1000, I saw that they both have the same average time, and none is faster than the other or at most slightly by a factor of 1/10^6. So, if you vector size if within than range, either one of those can be used for best average time.
List size from 10000 and higher-up.
When running my algorithm, with vector size from 10000 and higher-up, the concurrent sort faster than the sequential sort. The concurrent sort beats the sequential sort just slightly for the vector size of 10000 to 100000. But as you increase the size to 1000000 going up, average run time difference between the two increases significantly. So, the best sort for that size will be concurrent.

Conclusion:
From the all the data above observed, we saw that concurrent sort is faster than the sequential sort.


Final data observation:
List Size   Sequential Sort Time (s)   Concurrent Sort Time (s)
             min     max    average     min     max    average
---------   -----   -----   -------    -----   -----   -------
1           0.0000  0.0000  0.00000    0.0000  0.0000  0.00000
10          0.0000  0.0000  0.00000    0.0000  0.0000  0.00000
100         0.0000  0.0000  0.00000    0.0000  0.0000  0.00000
1000        0.0000  0.0000  0.00001    0.0000  0.0000  0.00001
10000       0.0001  0.0001  0.00012    0.0001  0.0001  0.00012
100000      0.0014  0.0016  0.00149    0.0013  0.0016  0.00147
1000000     0.0165  0.0183  0.01772    0.0087  0.0183  0.01707

