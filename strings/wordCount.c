/*

Count the number of words in a string 

*/

int countNumWords(const char *str) {
 
  bool inWord = false;
  int wordCount = 0;
 
  while (*str) {
 
    if (!inWord && isalpha(*str)) {
      inWord = true;
      wordCount++;
    }
    else if (inWord && *str == ' ') {
      inWord = false;
    }
    str++;
  }
  return wordCount;
}