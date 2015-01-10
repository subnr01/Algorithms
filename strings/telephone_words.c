/* 
People often give others their telephone number as a word representing the
seven-digit number. For example, if my telephone number were 866-2665, I could
tell people my number is “TOOCOOL,” instead of the hard-to-remember seven-digit
number. Note that many other possibilities (most of which are nonsensical) can
represent 866-2665.


Write a routine that takes a seven-digit telephone number and prints out all of
the possible “words” or combinations of letters that can represent the given
number. 
Because the 0 and 1 keys have no letters on them, you should change only
the digits 2–9 to letters. You’ll be passed an array of seven integers, with
each element being one digit in the number. You may assume that only valid phone
numbers will be passed to your routine. You can use the helper routine 

char getCharKey( int telephoneKey, int place ) 

which takes a telephone key (0–9) and
a place of either 1, 2, 3 and returns the character corresponding to the letter
in that position on the specified key. For example, GetCharKey(3, 2) will return
‘E’ because the telephone key 3 has the letters “DEF” on it and ‘E’ is the
second letter.


*/

/*
If the current digit is past the last digit
    Print the word because you're at the end
Else
    For each of the three digits that can represent the current digit, going from
low to high
        Have the letter represent the current digit
        Move to next digit and recurse
        If the current digit is a 0 or a 1, return
The code is as follows:

*/

static final int PHONE_NUMBER_LENGTH = 7;

void printTelephoneWords( int[] phoneNum ){
    char[] result = new char[ PHONE_NUMBER_LENGTH ];

    doPrintTelephoneWords( phoneNum, 0, result );
 }

void doPrintTelephoneWords( int[] phoneNum, int curDigit,
                            char[] result ){
    if( curDigit == PHONE_NUMBER_LENGTH ){
   	  System.out.println( new String( result ) );
	  return;
    }

    for( int i = 1; i <= 3; i++ ){
        result[ curDigit ] = getCharKey( phoneNum[curDigit], i );
        doPrintTelephoneWords( phoneNum, curDigit + 1, result );
        if( phoneNum[curDigit] == 0 ||
            phoneNum[curDigit] == 1) return;
    }
}

/*

What is the running time of this algorithm? It can be no less than O(3n) 
because there are 3n solutions, so any correct solution must be at least O(3n).
Getting each new word requires only constant time operations so the running time is indeed O(3n).
Important 	
Reimplement PrintTelephoneWords without using recursion.


*/



/* 
Iterative solution
*/

static final int PHONE_NUMBER_LENGTH = 7;

void printTelephoneWords( int phoneNum[] ){
    char[] result = new char[ PHONE_NUMBER_LENGTH ];
    int i;

    /* Initialize the result (in our example,
     * put GWP1WAR in result).
     */
    for( i = 0; i < PHONE_NUMBER_LENGTH; i++ )
        result[i] = getCharKey( phoneNum[i], 1 );

    /* Main loop begins */
    while( true ){
        for( i = 0; i < PHONE_NUMBER_LENGTH; ++i ){
            System.out.print( result[i] );
        }
        System.out.print( '\n' );

        /* Start at the end and try to increment from right
         * to left.
         */
        for( i = PHONE_NUMBER_LENGTH - 1; i >= -1; i-- ){
            /* You're done because you
             * tried to carry the leftmost digit.
             */
            if( i == -1 ) return;

            /* Otherwise, we're not done and must continue. */

            /* You want to start with this condition so that you can
             * deal with the special cases, 0 and 1 right away.
             */
            if( getCharKey( phoneNum[i], 3 ) == result[i] ||
                phoneNum[i] == 0 || phoneNum[i] == 1 ){
                result[i] = getCharKey( phoneNum[i], 1 );
                /* No break, so loop continues to next digit */
            } else if ( getCharKey( phoneNum[i], 1 ) == result[i] ){
                result[i] = getCharKey( phoneNum[i], 2 );
                break;
            } else if ( getCharKey( phoneNum[i], 2 ) == result[i] ){
                result[i] = getCharKey( phoneNum[i], 3 );
                break;
            }
        }
    }
}

