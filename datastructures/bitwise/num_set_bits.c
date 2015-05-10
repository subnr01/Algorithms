/*

Write a function that takes an unsigned integer and returns the number of ’1′ bits it has. 
For example, the 32-bit integer ’11′ has binary representation 00000000000000000000000000001011, 
so the function should return 3.


*/


int number_of_ones(unsigned int x) {
  int total_ones = 0;
  while (x != 0) {
    x = x & (x-1);
    total_ones++;
  }
  return total_ones;
}