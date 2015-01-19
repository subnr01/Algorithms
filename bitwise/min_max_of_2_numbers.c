
/*
Min and max 
*/


Minimum of x and y will be
y + ((x - y) & ((x - y) >>(sizeof(int) * CHAR_BIT - 1)))



Maximum of x and y will be 
x - ((x - y) & ((x - y) >> (sizeof(int) * CHAR_BIT - 1)))

