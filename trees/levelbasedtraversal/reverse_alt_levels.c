/*

Given a Perfect Binary Tree, reverse the alternate level nodes of the binary tree.

  
Given tree: 
               a
            /     \
           b       c
         /  \     /  \
        d    e    f    g
       / \  / \  / \  / \
       h  i j  k l  m  n  o 

Modified tree:
  	       	   a
            /     \
           c       b
         /  \     /  \
        d    e    f    g
       / \  / \  / \  / \
      o  n m  l k  j  i  h 


  */


  /*

  Solution

  A tricky solution is to do two inorder traversals. Following are steps to be
followed. 1) Traverse the given tree in inorder fashion and store all odd level
nodes in an auxiliary array. For the above example given tree, contents of array
become {h, i, b, j, k, l, m, c, n, o}

2) Reverse the array. The array now becomes {o, n, c, m, l, k, j, b, i, h}

3) Traverse the tree again inorder fashion. While traversing the tree, one by
one take elements from array and store elements from array to every odd level
traversed node. For the above example, we traverse ‘h’ first in above array and
replace ‘h’ with ‘o’. Then we traverse ‘i’ and replace it with n.

*/



// The main function to reverse alternate nodes of a binary tree
void reverseAlternate(struct Node *root)
{
    // Create an auxiliary array to store nodes of alternate levels
    char *arr = new char[MAX];
    int index = 0;
 
    // First store nodes of alternate levels
    storeAlternate(root, arr, &index, 0);
 
    // Reverse the array
    reverse(arr, index);
 
    // Update tree by taking elements from array
    index = 0;
    modifyTree(root, arr, &index, 0);
}

// Function to store nodes of alternate levels in an array
void storeAlternate(Node *root, char arr[], int *index, int l)
{
    // Base case
    if (root == NULL) return;
 
    // Store elements of left subtree
    storeAlternate(root->left, arr, index, l+1);
 
    // Store this node only if this is a odd level node
    if (l%2 != 0)
    {
        arr[*index] = root->data;
        (*index)++;
    }
 
    // Store elements of right subtree
    storeAlternate(root->right, arr, index, l+1);
}

// Function to modify Binary Tree (All odd level nodes are
// updated by taking elements from array in inorder fashion)
void modifyTree(Node *root, char arr[], int *index, int l)
{
    // Base case
    if (root == NULL) return;
 
    // Update nodes in left subtree
    modifyTree(root->left, arr, index, l+1);
 
    // Update this node only if this is an odd level node
    if (l%2 != 0)
    {
        root->data = arr[*index];
        (*index)++;
    }
 
    // Update nodes in right subtree
    modifyTree(root->right, arr, index, l+1);
}

