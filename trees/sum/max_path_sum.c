/*

Find the maximum path sum between two leaves of a binary tree Given a binary
tree in which each node element contains a number. Find the maximum possible sum
from one leaf node to another. 

The maximum sum path may or may not go through
root. For example, in the following binary tree, 
the maximum sum is 27(3 + 6 + 9 + 0 – 1 + 10). 
Expected time complexity is O(n).


http://www.geeksforgeeks.org/find-maximum-path-sum-two-leaves-binary-tree/

*/


// A utility function to find the maximum sum between any two leaves.
// This function calculates two values:
// 1) Maximum path sum between two leaves which is stored in res.
// 2) The maximum root to leaf path sum which is returned.
int maxPathSumUtil(struct Node *root, int &res)
{
    // Base case
    if (root==NULL) return 0;
 
    // Find maximum sum in left and right subtree. Also find
    // maximum root to leaf sums in left and right subtrees
    // and store them in lLPSum and rLPSum
    int lLPSum = maxPathSumUtil(root->left, res);
    int rLPSum = maxPathSumUtil(root->right, res);
 
    // Find the maximum path sum passing through root
    int curr_sum = max((lLPSum+rLPSum+root->data), max(lLPSum, rLPSum));
 
    // Update res (or result) if needed
    if (res < curr_sum)
        res = curr_sum;
 
    // Return the maximum root to leaf path sum
    return max(lLPSum, rLPSum)+root->data;
}

