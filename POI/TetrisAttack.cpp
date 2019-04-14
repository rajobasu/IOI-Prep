/*
SOLUTION : map the numbers according to the ordering of each number's first occurance. Now number of swaps 
required is the number of inversions in the second occurance. we can now simulate the swaps, swapping each 
a and b are adjacent and b < a. Keep track of all the info in a segtree, or possibly in O(1) time.
*/