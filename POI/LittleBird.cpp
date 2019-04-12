/*
SOLUTION : For each query, do a O(n) deque optimised DP. note that if the minimum is a lesser val, we just do a 
+1 with it, as in any case the second minimum will be greater by atleast 1. (also note that to break ties 
while inserting, if there are 2 numbers that are same, the number with the greater height is better.)
*/