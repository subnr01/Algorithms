/*

Given a BST, transform it into greater sum tree where each 
node contains sum of all nodes greater than that node.


*/


/*

Method 2 (Using only one traversal) By leveraging the fact that the tree is a
BST, we can find an O(n) solution. The idea is to traverse BST in reverse
inorder. Reverse inorder traversal of a BST gives us keys in decreasing order.
Before visiting a node, we visit all greater nodes of that node. While
traversing we keep track of sum of keys which is the sum of all the keys greater
than the key of current node.


*/






// Recursive function to transform a BST to sum tree.
// This function traverses the tree in reverse inorder so
// that we have visited all greater key nodes of the currently
// visited node
// A recursive function that traverses the given BST in reverse inorder and
// for every key, adds all greater keys to it
void addGreaterUtil(struct node *root, int *sum_ptr)
{
    // Base Case
    if (root == NULL)
        return;
 
    // Recur for right subtree first so that sum of all greater
    // nodes is stored at sum_ptr
    addGreaterUtil(root->right, sum_ptr);
 
    // Update the value at sum_ptr
    *sum_ptr = *sum_ptr + root->key;
 
    // Update key of this node
    root->key = *sum_ptr;
 
    // Recur for left subtree so that the updated sum is added
    // to smaller nodes
    addGreaterUtil(root->left, sum_ptr);
}
 
// A wrapper over addGreaterUtil().  It initializes sum and calls
// addGreaterUtil() to recursivel upodate and use value of sum
void addGreater(struct node *root)
{
    int sum = 0;
    addGreaterUtil(root, &sum);
}
