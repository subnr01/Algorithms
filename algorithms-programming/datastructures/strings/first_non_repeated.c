/*


Write an efficient function to find the first nonrepeated character in a string. 
For instance, the first nonrepeated character in “total” is ‘o’ and the first 
nonrepeated character in “teeter” is ‘r’. Discuss the efficiency of your algorithm.

*/

public static Character firstNonRepeated( String str ){
    Hashtable charHash = new Hashtable();
    int i, length;
    Character c;
    Integer intgr;

    length = str.length();

    // Scan str, building hash table
    for (i = 0; i < length; i++) {
        c = new Character(str.charAt(i));
        intgr = (Integer) charHash.get(c);
        if (intgr == null) {
            charHash.put(c, new Integer(1));
        } else {
            // Increment count corresponding to c
            charHash.put(c, new Integer(intgr.intValue() + 1));
        }
    }

    // Search hashtable in order of str
    for (i = 0; i < length; i++) {
        c = new Character(str.charAt(i));
        if (((Integer)charHash.get(c)).intValue() == 1)
            return c;
    }
    return null;

}