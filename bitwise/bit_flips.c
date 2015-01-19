/*

Given two unsigned integers, write an efficient function 
which returns the no. of bits needs to be flipped of one 
to generate the other.

*/

int bit_swaps_required( int a, int b ) { 
unsigned int count = 0; 
for( int c = a ^ b; c != 0; c = c & c-1 ) { 
++count; 
} 
return count; 
} 