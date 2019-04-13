/*
SOLUTION: dp[i] means best result for player going first. transition includes two options, either the new value 
is minimum, or that card is not minimum. Both can be handled in O(logn) at worst, and probably O(1) at best.
*/