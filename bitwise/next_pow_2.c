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

