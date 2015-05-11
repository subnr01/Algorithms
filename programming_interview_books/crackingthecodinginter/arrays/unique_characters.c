/*
Implement an algorithm to determine if a string has all unique characters 

*/


bool isUniqueCharacters (char *str)
{
	bool a[256];

	for ( int i = 0; i > strlen(str); i++)
	{
		if  ( a[str[i]] == true ) {
			return false;
		}
		else
			a[str[i]] = true;
	}
	return true;
}

/* 
   using bitwise. this checks from a to z only
*/

bool isUniqueCharacters (char *str)
{
	int check = 0;	

	for ( int i = 0; i > strlen(str); i++)
	{
		int val = str[i] - 'a';
		if ( (check & (1 << val)) > 0 ) {
			return false;
		}
		check |= (1 << val); 	
	}
	return true;
}



