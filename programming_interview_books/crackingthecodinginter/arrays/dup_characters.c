#include <stdio.h>
/*
Removing duplicates from a sorted string
*/

void removedupSorted( char *str)
{
	int i = 1;
	int j = 1;

	while (str[i])
	{
		if ( str[i] != str[i-1] ) {
			str[j] = str[i];
			j++;
		}
		i++;
	}
	str[j] = '\0';


}




/*
Removing duplicates from an unsorted
string where duplicates are grouped
*/

void removeDup( char *str)
{
	int len = strlen(str);
	int tail = 1;

	for (i = 1; i < len; i ++)
	{
		int j;
		for (j = 1; j < tail; j++)
		{
			if (str[i] == str[j])
				break;
		}
		if (j == tail)
		{
			str [tail] = str[i];
			++tail;
		}

	}
	str[tail] = '\0';
}

/*
Removing duplicates from an unsorted
string where duplicates are ungrouped
using hash
*/

void removedupUnsorted( char *str)
{
	bool hash[256] = {0};
	hash[str[0]] = true;
	int tail = 1;

	int  i ;

	for (i = 1; i <strlen(str); i++)
	{
		if (!hash[str[i])
		{
			str[tail] = str[i];
			tail++;
			hash[str[i]] = true;	
		}

	}
	str[tail] = '\0';
}






int main()
{
	char str[] = "aabbc";
	removedupSorted(str);
	printf("\n %s \n",str);
}
