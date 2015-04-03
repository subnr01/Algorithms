/*

divisble by 9

*/

/*
n/9 can be written in terms of n/8 using the following simple formula.

n/9 = n/8 - n/72

*/


// Bitwise operator based function to check divisibility by 9
bool isDivBy9(int n)
{
    // Base cases
    if (n == 0 || n == 9)
        return true;
    if (n < 9)
        return false;
 
    // If n is greater than 9, then recur for [floor(n/9) - n%8]
    return isDivBy9((int)(n>>3) - (int)(n&7));
}
 

 