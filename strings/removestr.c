/*

Write an efficient function in C# that deletes characters from a string. Use the prototype
string removeChars( string str, string remove );
where any character existing in remove must be deleted from str. 
For example, given a str of “Battle of the Vowels: Hawaii vs. Grozny” a
nd a remove of “aeiou”, the function should transform str to “Bttl f th Vwls: Hw vs. Grzny”. Justify any design decisions you make and discuss the efficiency of your solution.

*/



string removeChars( string str, string remove ){
    char[] s = str.toCharArray();
    char[] r = remove.toCharArray();
    bool[] flags = new bool[128]; // assumes ASCII!
    int    len = s.Length;
    int    src, dst;

    // Set flags for characters to be removed
    for( src = 0; src < len; ++src ){
        flags[r[src]] = true;
    }
    src = 0;
    dst = 0;

    // Now loop through all the characters,
    // copying only if they aren't flagged
    while( src < len ){
        if( !flags[ (int)s[src] ] ){
            s[dst++] = s[src];
        }
        ++src;
    }

    return new string( s, 0, dst );
}