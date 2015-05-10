Determine the absolute value of an integer without branching
 ( i.e. without using any if else statement etc)


int v; // we want to find the absolute value of v 
unsigned int r; // the result goes here 
int const mask = v >> sizeof(int) * CHAR_BIT - 1; 

r = (v + mask) ^ mask; 


//When you right shift a negative number 31 times, then resultant value is -1.

