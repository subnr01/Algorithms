/*
http://leetcode.com/2010/09/saving-binary-search-tree-to-file.html
For example, if the given traversal is {10, 5, 1, 7, 40, 50}, then the output should be root of following tree.

     10
   /   \
  5     40
 /  \      \
1    7      50  



First we look at the Recursive O(n^2) solution and
then the stack solution O(n)


*/



/* 

Recursive O(n^2) solution

In this solution, we call the function recursively.
We start from the first element in the preorder array.
Run a for loop and get the index of the greatest element 
after the first element.

So our left child range becomes (second element, greatest element index - 1)
and our right child range becomes
( greatest element index, last element of the array)

We run the recursion, until our low and high elements become either equal or
low becomes greater than high.

For a single element condition, if we find
the preorder index to be equal to the total elements
in the array, then we return


*/ 


// A recursive function to construct Full from pre[]. preIndex is used
// to keep track of index in pre[].
struct node* constructTreeUtil (int pre[], int* preIndex,
                                int low, int high, int size)
{
    // Base case
    if (*preIndex >= size || low > high)
        return NULL;
 
    // The first node in preorder traversal is root. So take the node at
    // preIndex from pre[] and make it root, and increment preIndex
    struct node* root = newNode ( pre[*preIndex] );
    *preIndex = *preIndex + 1;
 
    // If the current subarry has only one element, no need to recur
    if (low == high)
        return root;
 
    // Search for the first element greater than root
    int i;
    for ( i = low; i <= high; ++i )
        if ( pre[ i ] > root->data )
            break;
 
    // Use the index of element found in postorder to divide postorder array in
    // two parts. Left subtree and right subtree
    root->left = constructTreeUtil ( pre, preIndex, *preIndex, i - 1, size );
    root->right = constructTreeUtil ( pre, preIndex, i, high, size );
 
    return root;
}
 
// The main function to construct BST from given preorder traversal.
// This function mainly uses constructTreeUtil()
struct node *constructTree (int pre[], int size)
{
    int preIndex = 0;
    return constructTreeUtil (pre, &preIndex, 0, size - 1, size);
}

===========================================================================================================================

/* 
Construct tree for preorder 

Recursive function with O(n)

Here we obviate the need for 
running a for loop inside the 
recursive function thereby 
saving time complexity.

We take the highest as INT_MAX
and lowest as INT_MIN
and so in our first iteration,
pre-order index should lie between
INT_MIN and INT_MAX.
The subsequent iterations must
be INT_MIN and preorder index
and preorder index + 1 and
INT_MAX.

SO in this approach, we 
run recursion based on
values of array while in 
the other approach we run
recursion based on
index of array

*/

// A recursive function to construct BST from pre[]. preIndex is used
// to keep track of index in pre[].
struct node* constructTreeUtil( int pre[], int* preIndex, int key,
                                int min, int max, int size )
{
    // Base case
    if( *preIndex >= size )
        return NULL;
  
    struct node* root = NULL;
  
    // If current element of pre[] is in range, then
    // only it is part of current subtree
    if( key > min && key < max )
    {
        // Allocate memory for root of this subtree and increment *preIndex
        root = newNode ( key );
        *preIndex = *preIndex + 1;
         
        if (*preIndex < size)
        {
            // Contruct the subtree under root
            // All nodes which are in range {min .. key} will go in left
            // subtree, and first such node will be root of left subtree.
            root->left = constructTreeUtil( pre, preIndex, pre[*preIndex],
                                        min, key, size );
  
            // All nodes which are in range {key..max} will go in right
            // subtree, and first such node will be root of right subtree.
            root->right = constructTreeUtil( pre, preIndex, pre[*preIndex],
                                         key, max, size );
        }
    }
  
    return root;
}
 
// The main function to construct BST from given preorder traversal.
// This function mainly uses constructTreeUtil()
struct node *constructTree (int pre[], int size)
{
    int preIndex = 0;
    return constructTreeUtil ( pre, &preIndex, pre[0], INT_MIN, INT_MAX, size );
}


===========================================================================================================================

/* 
Solution using stack

O(n) solution

1. We create the root for the first element and push the root
   into the stack.
2. We run a loop to all the elements of the array.
3. If stackis not empty and we find that the top of the stack
   is less than the current array element in the loop
   we pop until we find the stack top to be greater.
4. The last popped element becomes the parent and the 
   current array element becomes its right child. we
   then push this right child into the stack. The right
   child becomes the current stack top.
5. If we find that the stack top is greater, then
   the current element becomes the left child of
   the current stack top. We then push the left
   child into the stack so that it becomes
   the current stack top.


*/


// The main function that constructs BST from pre[]
Node* constructTree ( int pre[], int size )
{
    // Create a stack of capacity equal to size
    Stack* stack = createStack( size );
 
    // The first element of pre[] is always root
    Node* root = newNode( pre[0] );
 
    // Push root
    push( stack, root );
 
    int i;
    Node* temp;
 
    // Iterate through rest of the size-1 items of given preorder array
    for ( i = 1; i < size; ++i )
    {
        temp = NULL;
 
        /* Keep on popping while the next value is greater than
           stack's top value. */
        while ( !isEmpty( stack ) && pre[i] > peek( stack )->data )
            temp = pop( stack );
 
        // Make this greater value as the right child and push it to the stack
        if ( temp != NULL)
        {
            temp->right = newNode( pre[i] );
            push( stack, temp->right );
        }
 
        // If the next value is less than the stack's top value, make this value
        // as the left child of the stack's top node. Push the new node to stack
        else
        {
            peek( stack )->left = newNode( pre[i] );
            push( stack, peek( stack )->left );
        }
    }
 
    return root;
}








