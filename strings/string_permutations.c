/*


Implement a routine that prints all possible orderings of the characters in a
string. In other words, print all permutations that use all the characters from
the original string. For example, given the string “hat”, your function should
print the strings “tha”, “aht”, “tah”, “ath”, “hta”, and “hat”. Treat each
character in the input string as a distinct character, even if it is repeated.
Given the string “aaa”, your routine should print “aaa” six times. You may print
the permutations in any order you choose.

*/


/* Function to print permutations of string
   This function takes three parameters:
   1. String
   2. Starting index of the string
   3. Ending index of the string. */
void permute(char *a, int i, int n) 
{
   int j; 
   if (i == n)
     printf("%s\n", a);
   else
   {
        for (j = i; j <= n; j++)
       {
          swap((a+i), (a+j));
          permute(a, i+1, n);
          swap((a+i), (a+j)); //backtrack
       }
   }
} 
 