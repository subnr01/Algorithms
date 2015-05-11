#include <stdio.h>
#include <string.h>
void reverse(char *str)
{
	char *start;
	char *end;

	start = str;
	end  = str + strlen(str) - 1;

	while (start < end)
	{
		char temp;
		temp = *start;
		*start = *end;
		*end = temp;
		start++;
		end--;
	}
	str = end;

}

int main()
{
	char p[] = "hello";
	printf("\n the string is %s",p);
	reverse(p);
	printf("\n the string is %s",p);

}