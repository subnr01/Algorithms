/*
Given a number x = 0x25. Convert it into y = 0x25252525
*/

int converint(int a)
{
return a<<24|a<<16|a<<8|a;
}


