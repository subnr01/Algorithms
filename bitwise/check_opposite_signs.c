/*
Check whether two numbers have opposite signs

*/

/*

The function is written only for compilers where size of an integer is 32 bit.
The expression basically checks sign of (x^y) using bitwise operator ‘>>’. As
mentioned above, the sign bit for negative numbers is always 1. The sign bit is
the leftmost bit in binary representation. So we need to checks whether the 32th
bit (or leftmost bit) of x^y is 1 or not. We do it by right shifting the value
of x^y by 31, so that the sign bit becomes the least significant bit. If sign
bit is 1, then the value of (x^y)>>31 will be 1, otherwise 0.

*/

bool oppositeSigns(int x, int y)
{
    return ((x ^ y) >> 31); //get the sign bit of the result.if it is 1 then that means one of the numbers was zero, so opposite
}

