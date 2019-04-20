/*
SOLUTION : Store (frequency,number) pairs in HLD. while queries, traverse the segtrees. Write all the pairs in a array and do inversion count. The count of such numbers amortizes to be quite less. Prove : take use of the fact that only logn light childs are changed, and that inside the segtrees, the number of changes is amortized.
*/