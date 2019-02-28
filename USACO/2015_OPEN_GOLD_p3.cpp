/*
SOLUTION: [DIFFERENT THAT INTENDED] For each left index L, find the maximum right index R, such that (R-L) < L,R
which means, any cow starting in [L,R] will be unable to break free. How to do this? Well, for each L, we know
what the maximum R can be. its just L + Sj. If the distance were longer, something could run up and break my left.
Now we also maintain for each haybale a value R-freeSpace. if this is negetive, that means free space is more.
so we just binsrch on the segtree in range [L,L+Sj] for the last value greater than 0. To update this segtree ,we
just need lazy updates.

COMPLEXITY: O(nlogn)
*/