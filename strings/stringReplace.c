/*
Replace all occurrence of the given pattern to ‘X’.
For example, given that the pattern=”abc”, replace “abcdeffdfegabcabc” with 
“XdeffdfegX”. Note that multiple occurrences of abc’s that are contiguous 
will be replaced with only one ‘X’.



*/


/*

Solution: 
We should take advantage that the replacement is only one character in
length. Assume that the pattern is at least one character in length, then the
replacement’s length will never exceed the pattern’s length. This means that
when we overwrite the existing string with replacement, we would never overwrite
characters that would be read next.

Two pointers are also used for an efficient in-place replacement, which
traverses the string once without any extra memory.

*/

bool isMatch(char *str, const char* pattern) {
  while (*pattern)
    if (*str++ != *pattern++)
      return false;
  return true;
}
 
void replace(char str[], const char *pattern) {
  if (str == NULL || pattern == NULL) return;
  char *pSlow = str, *pFast = str;
  int pLen = strlen(pattern);
  while (*pFast != '\0') {
    bool matched = false;
    while (isMatch(pFast, pattern)) {
      matched = true;
      pFast += pLen;
    }
    if (matched)
      *pSlow++ = 'X';
    // tricky case to handle here:
    // pFast might be pointing to '\0',
    // and you don't want to increment past it
    if (*pFast != '\0')
      *pSlow++ = *pFast++;  // *p++ = (*p)++
  }
  // don't forget to add a null character at the end!
  *pSlow = '\0';
}