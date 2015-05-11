/*
Check string rotation using only one call to strstr
*/

bool checkRotation(char *str1, char *str2)
{
	if (strlen(str1) != strlen(str2))
		return false;

	char temp[256];

	strcpy(temp,str1);
	strcat(temp,str1);

	/* Concatenate the string to itself and 
	   find whether the second string is 
	   part of this concatenated string
	*/

	if (strstr(temp,str2) == NULL)
		return false;

}