/*

Given an 32-bit integer X, 
swap the i-th and j-th bit


A swap is actually required only if the two bits are different. 
This implies that a swap is required if the XOR of the bits is 1. 
Assume two bits x and y need to be swapped. Then,

x' = x ^ ( x ^ y ) 
y' = y ^ ( x ^ y )

If two bits are same, x ^ y is 0 and (0,1) XOR 0 is the bit itself. 
Otherwise, x ^ y is 1 and (0,1) XOR 1 is (1,0)

*/


int swap(int num, int i, int j)
{
 
 //Take the ith bit and the jth bit XOR it.
 //Use AND to preserve the result.
 int xor = ((num>>i) ^ (num>>j)) & 1;
 
 /* Now XOR the number with the ith bit in place and jth bit in place */
 return num ^ (xor<<i) ^ (xor<<j);
}


