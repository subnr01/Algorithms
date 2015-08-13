/*

To check whether two strings are anagrams:
1. Sort both strings and do a string compare
2. Use hash table and find whether any character is unique in
	only one string


/*
Using Sort
*/

bool isAnagrams( char *str1, char *str2)
{

	if ( strlen(str1) != strlen(str2))
			return false;

	return (sort(str1) == sort(str2));
}


/* 
Using hash 
Note the characters in both the strings may be repeated
*/

bool is isAnagrams( char *str1, char *str2)
{
	if ( strlen(str1) != strlen(str2))
			return false;

	int unique = 0;
	int hash[256] = {0};
	int i;
	int num = 0;

	while (*str2)
	{
		if (hash[*str2] == 0) {
			unique++;
		}
		hash[*str2]++;
		str2++;
	}

	int i;

	for (i = 0; i < len; i++)
	{
		if (hash[str2[i]] == 0)
			return 0;


		--hash[str2[i]];

		if (hash[str2[i]] == 0)
			num++;

		if (num == unique)
		{
			return i == len-1;
		}

	}
	return 0;
}

