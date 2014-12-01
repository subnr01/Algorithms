
/* Given a sentence to tell whether it is a panagram or not */


#include <stdio.h>
#include <string.h>

void panagram (char *s)
{
	int a[26] = {0};
	int index = 0;
	int total = 0;
	char ch ;
	while ( (ch = *s++))
	{
		if ( ch >='a' && ch <= 'z')
		{
			index = ch - 'a';
		}
		else {
			continue;
		}
		total  = total + !a[index];
		a[index] = 1;
		
	}
	if ( total == 26)
	{
		printf ( "it is an panagram");
		return;
	}	
}

int main()
{
	char s[100];
	printf("\n Enter ur sentence");
	fgets(s, sizeof(s), stdin);
	printf ("\n length IS %d",(int)strlen(s));
	panagram(s);
}
