/*

Implement an algorithm to determine if a string 
has all unique characters What if you can not use additional data structures?


*/

boolean uniqueStr( String str)
{
	boolean[] char_set  = new boolean[256];
	for ( i 0 to str.length())
	{
		int val = str[i];
		if (char_set[val])
			return false;

		char_set[val] = true;
	}
}