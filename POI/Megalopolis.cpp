/*
SOLUTION : make a euler tour, but use the edges instead. Now, each edge will have 2 occurances, once +1 and
once -1. When a query comes, it will be some prefix of the euler array. note that subtrees can be skipped 
due to the presence of inverse of +1, so we wont be overcounting. While converting to motorways,
set both the costs to 0. We need a DS for rangesum/point update. use segtree or BITS.
*/