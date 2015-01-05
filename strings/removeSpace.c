/* 

Remove spaces from a string


*/


void removeSpace(char *str) {
  char *p1 = str, *p2 = str;
  
  do {

    while (*p2 == ' ')  //if the character space, then increment p2
      p2++;

  } while (*p1++ = *p2++); //increment p1 for every valid p2 character
}
