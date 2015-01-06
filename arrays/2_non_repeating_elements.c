/*

Find two non repeating elements of an array
Given an array in which all numbers except two are repeated once. 
(i.e. we have 2n+2 numbers and n numbers are occurring twice and 
remaining two have occurred once). Find those two numbers in the 
most efficient way.


*/


/* This finction sets the values of *x and *y to nonr-epeating
 elements in an array arr[] of size n*/
void get2NonRepeatingNos(int arr[], int n, int *x, int *y)
{
  int xor = arr[0]; /* Will hold xor of all elements */
  int set_bit_no;  /* Will have only single set bit of xor */
  int i;
  *x = 0;
  *y = 0;
 
  /* Get the xor of all elements */
  for(i = 1; i < n; i++)
   xor ^= arr[i];
 
  /* Get the rightmost set bit in set_bit_no */
  set_bit_no = xor & ~(xor-1);
 
  /* Now divide elements in two sets by comparing rightmost set
   bit of xor with bit at same position in each element. */
  for(i = 0; i < n; i++)
  {
    if(arr[i] & set_bit_no)
     *x = *x ^ arr[i]; /*XOR of first set */
    else
     *y = *y ^ arr[i]; /*XOR of second set*/
  }
}


