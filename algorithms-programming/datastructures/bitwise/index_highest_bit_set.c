x & 0xFFFF0000 && (i += 16, x >>= 16), 
x & 0xFF00 && (i += 8, x >>= 8), 
x & 0xF0 && (i += 4, x >>= 4), 
x & 0x0C && (i += 2, x>>= 2), 
x & 2 && (i += 1); 