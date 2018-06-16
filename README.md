# README
Brute force algorithm comparison to Johnson's algorithm for solving two and three machines flowshop problem.
NEH algorithm (O(n^2)) and Tabu algorithm for three machines flowshop problem.

Tasks are created in loop. Values of Mx (where x is machine number) are generated randomly,
they represent time needed for x machine to process task.
Computation time available for later comparison.

You may want to change:
1. Number of tasks by changing `TASK_COUNT`
2. Minimal time for machine by changing `MIN_TIME`
3. Maximal time for machine by changing `MAX_TIME`
4. Tabu algorithm run time by changing `TABOO_TIME`
5. You can save some time by turning off `SHOW_PERMUTATIONS`
6. To `GENERATE_PLOT` You will need `gnuplot`
7. I used `GENERATE_TEST_DATA` to generate tables below

### Test times

#### Two Machines
| Number of tasks: |Johnson's algorithm |make span | Brute force | make span|
| ------------- |-------------:| -----:| -----:| -----:|
|2|0.007 ms|19|0.006 ms|19|
|3|0.007 ms|37|0.01 ms|37|
|4|0.007 ms|52|0.014 ms|52|
|5|0.007 ms|61|0.036 ms|61|
|6|0.009 ms|72|0.192 ms|72|
|7|0.008 ms|59|1.386 ms|59|
|8|0.013 ms|98|11.962 ms|98|
|9|0.015 ms|86|138.003 ms|86|
|10|0.014 ms|107|1369.05 ms|107|
|11|0.017 ms|124|16103.2 ms|124|
|12|0.014 ms|123|198605 ms|123|

#### Three Machines
| Number of tasks: |Johnson's algorithm | make span | Brute force | make span| NEH algorithm | make span| Tabu algorithm | make span |
| ------------- |-------------:| -----:| -----:| -----:|----:|----:|----:|----:|
|3|0.007 ms|53|0.004 ms|53|0.009 ms|53|20675.4 ms|53|
|4|0.007 ms|87|0.01 ms|81|0.012 ms|81|20420.4 ms|81|
|5|0.007 ms|63|0.04 ms|63|0.015 ms|67|20606.8 ms|64|
|6|0.014 ms|79|0.404 ms|71|0.027 ms|71|20023.7 ms|71|
|7|0.064 ms|85|2.285 ms|85|0.028 ms|85|20623.3 ms|85|
|8|0.011 ms|112|20.08 ms|112|0.04 ms|112|20790.6 ms|112|
|9|0.013 ms|153|270.539 ms|153|0.045 ms|153|20963.2 ms|156|
|10|0.015 ms|128|3593.9 ms|127|0.064 ms|127|20950.6 ms|128|
|11|0.014 ms|131|25595.4 ms|128|0.076 ms|128|20203.1 ms|128|
|12|0.049 ms|136|269797 ms|136|0.082 ms|136|20069.9 ms|136|

### Visualisation
I'm using `gnuplot` to visualise chosen task order.

Example visualisation for three machines (number above arrow represents task ID):
![alt text](jplot3.svg "Three machines tasks runtime visualisation")

### Summary
Johnson's algorithm is significantly faster than brute force and gives the same results as brute force.
Three machines version of Johnson's algorithm is not perfect but it is close enough for the time savings.
Three machines NEH algorithm gives almost ideal results (most of the time, they are the same as brute force) 
in a time comparable to Johnson's algorithm.
Tabu algorithm gives results comparable to NEH and algorithm and mostly better than Johnson's algorithm.
This implementation of Tabu algorithm is very simple and time based.

*for SPD lab pt11 on PWR*
