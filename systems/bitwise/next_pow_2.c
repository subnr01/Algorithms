/*
If number is already power of 2 then return

Right shift 1 until it is greater than
the number. That will give the nearest power of
2
*/


unsigned int nextPowerOf2(unsigned int n)
{
    unsigned int p = 1;
    if (n && !(n & (n - 1)))
        return n;
 
    while (p < n) {
        p <<= 1;
    }
    return p;
}

