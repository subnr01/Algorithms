/*

isPalindrome(x)
1) Find number of bits in x using sizeof() operator.
2) Initialize left and right positions as 1 and n respectively.
3) Do following while left ‘l’ is smaller than right ‘r’.
..…..a) If bit at position ‘l’ is not same as bit at position ‘r’, then return false.
..…..b) Increment ‘l’ and decrement ‘r’, i.e., do l++ and r–-.
4) If we reach here, it means we didn’t find a mismatching bit.


*/

// This function returns true if k'th bit in x is set (or 1).
// For example if x (0010) is 2 and k is 2, then it returns true
bool isKthBitSet(unsigned int x, unsigned int k)
{
    return (x & (1 << (k-1)))? true: false;
}
 
// This function returns true if binary representation of x is
// palindrome. For example (1000...001) is paldindrome
bool isPalindrome(unsigned int x)
{
    int l = 1; // Initialize left position
    int r = sizeof(unsigned int)*8; // initialize right position
 
    // One by one compare bits
    while (l < r)
    {
        if (isKthBitSet(x, l) != isKthBitSet(x, r))
            return false;
        l++;     r--;
    }
    return true;
}





/*
Another solution
*/


boolean isPalindrome(int x)
{
    int y=0,z=x;
    while(z)
    {
        y = (y<<1)|(z&1);
        z=z>>1;
    }
    return (y==x)?true:false;
}
