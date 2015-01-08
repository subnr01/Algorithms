/*
Given a Binary Tree, convert it to a Binary Search Tree. The conversion must be done in such a way that 
keeps the original structure of Binary Tree.

Examples.

Example 1
Input:
          10
         /  \
        2    7
       / \
      8   4
Output:
          8
         /  \
        4    10
       / \
      2   7
*/


/*

Following is a 3 step solution for converting Binary tree to Binary Search Tree.
1) Create a temp array arr[] that stores inorder traversal of the tree. This step takes O(n) time.
2) Sort the temp array arr[]. Time complexity of this step depends upon the sorting algorithm. In the following
   implementation, Quick Sort is used which takes (n^2) time. This can be done in O(nLogn) time using
   Heap Sort or Merge Sort.
3) Again do inorder traversal of tree and copy array elements to tree nodes one by one. This step takes O(n) time.


*/


void storeInorder (struct node* node, int inorder[], int *index_ptr)
{
    // Base Case
    if (node == NULL)
        return;
 
    /* first store the left subtree */
    storeInorder (node->left, inorder, index_ptr);
 
    /* Copy the root's data */
    inorder[*index_ptr] = node->data;
    (*index_ptr)++;  // increase index for next entry
 
    /* finally store the right subtree */
    storeInorder (node->right, inorder, index_ptr);
}
 
/* A helper function to count nodes in a Binary Tree */
int countNodes (struct node* root)
{
    if (root == NULL)
     return 0;
    return countNodes (root->left) +
           countNodes (root->right) + 1;
}
 
// Following function is needed for library function qsort()
int compare (const void * a, const void * b)
{
    return ( *(int*)a - *(int*)b );
}
 
/* A helper function that copies contents of arr[] to Binary Tree. 
   This functon basically does Inorder traversal of Binary Tree and 
   one by one copy arr[] elements to Binary Tree nodes */
void arrayToBST (int *arr, struct node* root, int *index_ptr)
{
    // Base Case
    if (root == NULL)
      return;
 
    /* first update the left subtree */
    arrayToBST (arr, root->left, index_ptr);
 
    /* Now update root's data and increment index */
    root->data = arr[*index_ptr];
    (*index_ptr)++;
 
    /* finally update the right subtree */
    arrayToBST (arr, root->right, index_ptr);
}
 
// This function converts a given Binary Tree to BST
void binaryTreeToBST (struct node *root)
{
    // base case: tree is empty
    if(root == NULL)
       return;
 
    /* Count the number of nodes in Binary Tree so that
       we know the size of temporary array to be created */
    int n = countNodes (root);
 
    // Create a temp array arr[] and store inorder traversal of tree in arr[]
    int *arr = new int[n];
    int i = 0;
    storeInorder (root, arr, &i);
 
    // Sort the array using library function for quick sort
    qsort (arr, n, sizeof(arr[0]), compare);
 
    // Copy array elements back to Binary Tree
    i = 0;
    arrayToBST (arr, root, &i);
 
    // delete dynamically allocated memory to avoid meory leak
    delete [] arr;
}
 
