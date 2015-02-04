/*


Given a binary matrix, print all unique rows of the given matrix. 
Input:
	{0, 1, 0, 0, 1}
        {1, 0, 1, 1, 0}
        {0, 1, 0, 0, 1}
        {1, 1, 1, 0, 0}
Output:
	0 1 0 0 1 
	1 0 1 1 0 
	1 1 1 0 0 

Method 2 (Use Binary Search Tree)
Find the decimal equivalent of each row and insert it into BST. Each node of the BST will contain two fields,
one field for the decimal value, other for row number. Do not insert a node if it is duplicated. Finally,
traverse the BST and print the corresponding rows.
Time complexity: O( ROW x COL x log( ROW ) )
Auxiliary Space: O( ROW )
This method will lead to Integer Overflow if number of columns is large.

Method 3 (Use Trie data structure) Since the matrix is boolean, a variant of
Trie data structure can be used where each node will be having two children one
for 0 and other for 1. Insert each row in the Trie. If the row is already there,
don’t print the row. If row is not there in Trie, insert it in Trie and print
it.


*/

// given matrix.
void findUniqueRows( int (*M)[COL] )
{
    Node* root = NULL; // create an empty Trie
    int i;
 
    // Iterate through all rows
    for ( i = 0; i < ROW; ++i )
        // insert row to TRIE
        if ( insert(&root, M, i, 0) )
            // unique row found, print it
            printRow( M, i );
}


