/*

Write a function that reverses the order of the words in a string. 
For example, your function should transform the string “Do or do not, 
there is no try.” to “try. no is there not, do or Do”. Assume that all
 words are space delimited and treat punctuation the same as letters.


*/


/*
Solution 1:
1, Have two pointers, one traversing the sentence looking for space 
   while the other points to beginning of each word.
2. Reverse every word.
3. Reverse the entire sentence at the end.
*/

/*Function to reverse words*/
void reverseWords(char *s)
{
  char *word_begin = s;
  char *temp = s; /* temp is for word boundry */
 
  /*STEP 1 of the above algorithm */
  while( *temp )
  {
    temp++;
    if (*temp == '\0')
    {
      reverse(word_begin, temp-1);
    }
    else if(*temp == ' ')
    {
      reverse(word_begin, temp-1);
      word_begin = temp+1;
    }
  } /* End of while */
 
   /*STEP 2 of the above algorithm */
  reverse(s, temp-1);
}



 bool reverseWords( char str[] ){
    char *buffer;
    int tokenReadPos, wordReadPos, wordEnd, writePos = 0;

    /* Position of the last character is length - 1 */
    tokenReadPos = strlen(str) - 1;

    buffer = (char *) malloc(tokenReadPos + 2);
    if( !buffer )
        return false; /* reverseWords failed */

    while( tokenReadPos >= 0 ){

        if( str[tokenReadPos] == ' ' ){ /* Non-word characters */
            /* Write character */
            buffer[writePos++] = str[tokenReadPos--];

        } else {  /* Word characters */
            /* Store position of end of word */
            wordEnd = tokenReadPos;

            /* Scan to next non-word character */
            while( tokenReadPos >= 0 && str[tokenReadPos] != ' ' )
                tokenReadPos--;

            /* tokenReadPos went past the start of the word */
            wordReadPos = tokenReadPos + 1;

           /* Copy the characters of the word */
           while( wordReadPos <= wordEnd ){
               buffer[writePos++] = str[wordReadPos++];
           }
        }
    }
    /* null terminate buffer and copy over str */
    buffer[writePos] = '\0';
    strcpy(str, buffer);

    free(buffer);

    return true; /* ReverseWords successful */
}




/* Another solution */

void reverseWords( char str[] ){
    int start = 0, end = 0, length;

    length = strlen(str);
    /* Reverse entire string */
    reverseString(str, start, length - 1);

    while( end < length ){
       if( str[end] != ' ' ){ /* Skip non-word characters */

           /* Save position of beginning of word */
           start = end;

           /* Scan to next non-word character */
           while( end < length && str[end] != ' ' )
               end++;
            /* Back up to end of word */
            end--;

            /* Reverse word */
            reverseString( str, start, end );
        }
        end++; /* Advance to next token */
    }
}

void reverseString( char str[], int start, int end ){
    char temp;
    while( end > start ){
        /* Exchange characters */
        temp = str[start];
        str[start] = str[end];
        str[end] = temp;

        /* Move indices towards middle */
        start++; end--;
    }
}

