# Travelling Salesperson 2D
## Input
Your program should take as input a single TSP instance. It will be run several times, once for every test case. The time limit is per test case.

The first line of standard input contains an integer 1 ≤ _N_ ≤ 1000, the number of points. The following _N_ 
lines each contain a pair of real numbers _x_, _y_ giving the coordinates of the _N_ points. 
All numbers in the input have an absolute value bounded by 10^6.

The distance between two points is computed as the Euclidean distance between the two points, _rounded to the nearest integer_.

## Output
Standard output should consist of _N_ lines, the _i_’th of which should contain the (0-based) index of the _i_’th point visited.

## Score
* Let _Opt_ be the length of an optimal tour, 
* Let _Val_ be the length of the tour found by your solution, and 
* Let _Naive_ be the length of the tour found by the algorithm below.

Define _x_ = (_Val_ - _Opt_) / (_Naive_ - _Opt_). 
(In the special case that _Naive_ = _Opt_, define _x_ = 0 if _Val_ = _Opt_, AND _x_ = _inf_ IF _Val_ > _Opt_.)

The score on a test case is 0.02^_x_. Thus, if your tour is optimal, you will get 1 point on this test case. 
If your score is halfway between _Naive_ and _Opt_, you get roughly 0.14 points. 
The total score of your submission is the sum of your score over all test cases. There will be a total of 50 test cases. 
Thus, an implementation of the algorithm below should give a score of at least 1 (it will get 0.02 points on most test cases, 
and 1.0 points on some easy cases where it manages to find an optimal solution).

The algorithm giving the value _Naive_ is as follows:
```
GreedyTour
   tour[0] = 0
   used[0] = true
   for i = 1 to n-1
      best = -1
      for j = 0 to n-1
         if not used[j] and (best = -1 or dist(tour[i-1],j) < dist(tour[i-1],best))
            best = j
      tour[i] = best
      used[best] = true
   return tour
```
The sample output gives the tour found by GreedyTour on the sample input. The length of the tour is 323.

## Sample Input
```
10
95.0129 61.5432
23.1139 79.1937
60.6843 92.1813
48.5982 73.8207
89.1299 17.6266
76.2097 40.5706
45.6468 93.5470
1.8504 91.6904
82.1407 41.0270
44.4703 89.3650
```
## Sample Output
```
0
8
5
4
3
9
6
2
1
7
```
