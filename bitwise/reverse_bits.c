
/*
Reverse bits of a number
*/

/* 

The idea is to keep putting set bits of the num in reverse_num until num
becomes zero. After num becomes zero, shift the remaining bits of reverse_num.

Let num is stored using 8 bits and num be 00000110. After the loop you will get
reverse_num as 00000011. Now you need to left shift reverse_num 5 more times and
you get the exact reverse 01100000.

*/
unsigned int reverseBits(unsigned int num)
{
    unsigned int count = sizeof(num) * 8 - 1;
    unsigned int reverse_num = num;
     
    num >>= 1; 
    while(num)
    {
       reverse_num <<= 1;       
       reverse_num |= num & 1;
       num >>= 1;
       count--;
    }
    reverse_num <<= count;
    return reverse_num;
}
 