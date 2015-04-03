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
void transformTreeUtil(struct Node *root, int *sum)
{
   // Base case
   if (root == NULL)  return;
 
   // Recur for right subtree
   transformTreeUtil(root->right, sum);
 
   // Update sum
   *sum = *sum + root->data;
 
   // Store old sum in current node
   root->data = *sum - root->data;
 
   // Recur for left subtree
   transformTreeUtil(root->left, sum);
}
 
// A wrapper over transformTreeUtil()
void transformTree(struct Node *root)
{
    int sum = 0; // Initialize sum
    transformTreeUtil(root, &sum);
}