#include<stdio.h>


int main()
{

	int a = 4;
	int b = 0;
	int c = a;
	int n;
	int res1 = 1;
	int res2 = 1;
	int res;
	n = b;

	while (n > 0)
	{
		if (n % 2)
		{
			n = n/2;
			res1 = res1 * res1;
		} else {
			n = n - 1;
			res2 = res2 * a
		}

		
	}
	res = res1 * res2;

	printf("\n value of res is %d \n",res);
}