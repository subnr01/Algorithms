/*
Assuming you have three N bit unsigned integers a, b and c, 
what is the min number of bits you would need to store the result of a * b + c?
*/



Another easy way to understand this is : consider N to be 8 bits or 1 byte... An
unsigned int of 1 byte can have a max value of 255. Now applying the given
equation with the maximum values possible:

a*b + c = 255*255 + 255 = 65280

we know unsigned 8 bit value max is 255 . Similarly unsigned 16 bit value is
65536 and 65280 is less than 65536. Hence we need 16bits for storing the result
or 2N bits.
