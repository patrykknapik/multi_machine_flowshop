# README
Brute force algorithm comparison to Johnson's algorithm for solving two and three machines flowshop problem.
NEH algorithm (O(n^2)) for three machines flowshop problem.

Tasks are created in loop. Values of Mx (where x is machine number) are generated randomly,
they represent time needed for x machine to process task.
Computation time available for later comparison.

You may want to change:
1. Number of tasks by changing `TASK_COUNT`
2. Minimal time for machine by changing `MIN_TIME`
3. Maximal time for machine by changing `MAX_TIME`
4. You can save some time by turning off `SHOW_PERMUTATIONS`
5. To `GENERATE_PLOT` You will need `gnuplot`
6. I used `GENERATE_TEST_DATA` to generate tables below

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
| Number of tasks: |Johnson's algorithm | make span | Brute force | make span| NEH algorithm | make span|
| ------------- |-------------:| -----:| -----:| -----:|----:|----:|
|2|0.007 ms|34|0.007 ms|34|0.014 ms|34|
|3|0.008 ms|57|0.009 ms|55|0.012 ms|55|
|4|0.007 ms|54|0.012 ms|54|0.012 ms|54|
|5|0.009 ms|66|0.055 ms|63|0.02 ms|64|
|6|0.011 ms|72|0.326 ms|67|0.026 ms|68|
|7|0.008 ms|97|1.854 ms|84|0.024 ms|84|
|8|0.009 ms|88|16.771 ms|88|0.029 ms|88|
|9|0.016 ms|123|290.34 ms|116|0.053 ms|116|
|10|0.016 ms|115|4221.17 ms|111|0.059 ms|111|
|11|0.011 ms|137|31826.8 ms|128|0.05 ms|128|
|12|0.011 ms|174|266816 ms|160|0.057 ms|160|

### Visualisation
I'm using `gnuplot` to visualise chosen task order.

Example visualisation for three machines (number above arrow represents task ID):
![alt text](jplot3.svg "Three machines tasks runtime visualisation")

### Summary
Johnson's algorithm is significantly faster than brute force and gives the same results as brute force.
Three machines version of Johnson's algorithm is not perfect but it is close enough for the time savings.
Three machines NEH algorithm gives almost ideal results (most of the time, they are the same as brute force) 
in a time comparable to Johnson's algorithm.

*for SPD lab pt11 on PWR*
