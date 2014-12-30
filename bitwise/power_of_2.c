
/*

Check whether the number 
is power of 2

*/


int isPowerof2( int x)
{
	if (x && !(x & (x-1)))
		return 1;
	else
		return 0;
}