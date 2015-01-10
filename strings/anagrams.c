/* 

Check whether two strings are anagram of each other Write a function to check
whether two given strings are anagram of each other or not. An anagram of a
string is another string that contains same characters, only the order of
characters can be different. For example, “abcd” and “dabc” are anagram of each
other.

*/


/* function to check whether two strings are anagram of each other */
bool areAnagram(char *str1, char *str2)
{
    // Get lenghts of both strings
    int n1 = strlen(str1);
    int n2 = strlen(str2);
 
    // If lenght of both strings is not same, then they cannot
    // be anagram
    if (n1 != n2)
      return false;
 
    // Sort both strings
    quickSort (str1, 0, n1 - 1);
    quickSort (str2, 0, n2 - 1);
 
    // Compare sorted strings
    for (int i = 0; i < n1;  i++)
       if (str1[i] != str2[i])
         return false;
 
    return true;
}
 

 /*
 Method 2

 This method assumes that the set of possible characters in both strings is small. 
 In the following implementation, it is assumed that the characters are stored using 
 8 bit and there can be 256 possible characters.

1) Create count arrays of size 256 for both strings. Initialize all values in count arrays as 0.
2) Iterate through every character of both strings and increment the count of character 
   n the corresponding count arrays.
3) Compare count arrays. If both count arrays are same, then return true.
*/

/* function to check whether two strings are anagram of each other */
bool areAnagram(char *str1, char *str2)
{
    // Create two count arrays and initialize all values as 0
    int count1[NO_OF_CHARS] = {0};
    int count2[NO_OF_CHARS] = {0};
    int i;
 
    // For each character in input strings, increment count in
    // the corresponding count array
    for (i = 0; str1[i] && str2[i];  i++)
    {
        count1[str1[i]]++;
        count2[str2[i]]++;
    }
 
    // If both strings are of different length. Removing this condition
    // will make the program fail for strings like "aaca" and "aca"
    if (str1[i] || str2[i])
      return false;
 
    // Compare count arrays
    for (i = 0; i < NO_OF_CHARS; i++)
        if (count1[i] != count2[i])
            return false;
 
    return true;
}


