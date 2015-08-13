/*
Replace spaces in the string with '%20'
*/


void replaceChar( char *str)
{
	/* count the number of spaces */
	int num_space = 0;
	while (*str)
	{
		if (*str == ' ')
		{
			num_space++;
		}
	}
	if (!num_space)
		return;

	/* every space need to be replaced with %20 */
	int newlen = strlen(str) + 2*num_space;

	str[newlen] = '\0';

	int i;
	for (i = strlen(str)-1 ; i>0; i--)
	{
		if (str[i] = ' ')
		{
			str[newlen - 1] = '0';
			str[num_len - 2] = '2';
			str[newlen - 3] = '%';
			newlen -= 3;
		}
		else {
			str[newlen - 1] = str[i];
			newlen--;
		}
	}


}