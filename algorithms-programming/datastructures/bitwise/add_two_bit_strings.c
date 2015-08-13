// The main function that adds two bit sequences and returns the addition
string addBitStrings( string first, string second )
{
    string result;  // To store the sum bits
 
    // make the lengths same before adding
    int length = makeEqualLength(first, second);
 
    int carry = 0;  // Initialize carry
 
    // Add all bits one by one
    for (int i = length-1 ; i >= 0 ; i--)
    {
        int firstBit = first.at(i) - '0';
        int secondBit = second.at(i) - '0';
 
        // boolean expression for sum of 3 bits
        int sum = (firstBit ^ secondBit ^ carry)+'0';
 
        result = (char)sum + result;
 
        // boolean expression for 3-bit addition
        carry = (firstBit & secondBit) | (secondBit & carry) | (firstBit & carry);
    }
 
    // if overflow, then add a leading 1
    if (carry)
        result = '1' + result;
 
    return result;
}