/*

	
Implement a function that prints all possible combinations of the characters in
a string. These combinations range in length from one to the length of the
string. Two combinations that differ only in ordering of their characters are
the same combination. In other words, “12” and “31” are different combinations
from the input string “123”, but “21” is the same as “12”.


*/

/*
For each letter from input start position to end of input string
    Select the letter into the current position in output string
    Print letters in output string
    If the current letter isn't the last in the input string
Generate remaining combinations starting at next position with iteration starting
at next letter beyond the letter just selected
After all that hard work, the algorithm looks pretty simple! You’re ready to code it. Here’s a C# version:

*/
void combine( string str ){
    int           length = str.Length;
    char[]        instr = str.ToCharArray();
    StringBuilder outstr = new StringBuilder();
    doCombine( instr, outstr, length, 0, 0 );
}

void doCombine( char[] instr, StringBuilder outstr, int length,
                int level, int start ){
    for( int i = start; i < length; i++ ){
        outstr.Append( instr[i] );
        Console.WriteLine( outstr );

        if( i < length - 1 ){
            doCombine( instr, outstr, length, level + 1, i + 1 );
        }

        outstr.Length = outstr.Length - 1;
    }
}