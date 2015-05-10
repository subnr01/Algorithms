/*
Check integer overflow


There can be overflow only if signs of two numbers are same, and sign of sum is opposite to the signs of numbers.

1)  Calculate sum
2)  If both numbers are positive and sum is negative then return -1
     Else 
        If both numbers are negative and sum is positive then return -1
        Else return 0

*/       

int addOvf(int* result, int a, int b)
{
   if( a > INT_MAX - b)
     return -1;
   else
   {
     *result = a + b;
      return 0;
   }
}