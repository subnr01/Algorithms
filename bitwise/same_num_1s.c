/*

given a 32-bit integer x 
find the smallest integer x0 > x 
with the same number of ones in binary representation 

x = 76
x0 = 81

*/

given a number x = 1000111100

lo = x & -x; // locate the lowest set bit: lo = 100
lz = (x + lo) & ~x; // locate the lowest zero above lo: lz = 1000000
x += lo; // flip the 'lz' bit: x = 1001000000
x |= (lz / lo / 2); // add the rest number of ones: x = 1001000111