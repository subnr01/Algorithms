/*

A given array represents a tree in such a way that the array value 
gives the parent node of that particular index. 
The value of the root node index would always be -1. Find the height of the tree.

Height of a Binary Tree is number of nodes on the path from 
root to the deepest leaf node, the number includes both root and leaf.

Input: parent[] = {1 5 5 2 2 -1 3}
Output: 4
The given array represents following Binary Tree 
         5
        /  \
       1    2
      /    / \
     0    3   4
         /
        6 


Input: parent[] = {-1, 0, 0, 1, 1, 3, 5};
Output: 5
The given array represents following Binary Tree 
         0
       /   \
      1     2
     / \
    3   4
   /
  5 
 /
6

*/

// This function fills depth of i'th element in parent[].  The depth is
// filled in depth[i].
void fillDepth(int parent[], int i, int depth[])
{
    // If depth[i] is already filled
    if (depth[i])
        return;
 
    // If node at index i is root
    if (parent[i] == -1)
    {
        depth[i] = 1;
        return;
    }
 
    // If depth of parent is not evaluated before, then evaluate
    // depth of parent first
    if (depth[parent[i]] == 0)
        fillDepth(parent, parent[i], depth);
 
    // Depth of this node is depth of parent plus 1
    depth[i] = depth[parent[i]]  + 1;
}
 
// This function returns height of binary tree represented by
// parent array
int findHeight(int parent[], int n)
{
    // Create an array to store depth of all nodes/ and
    // initialize depth of every node as 0 (an invalid
    // value). Depth of root is 1
    int depth[n];
    for (int i = 0; i < n; i++)
        depth[i] = 0;
 
    // fill depth of all nodes
    for (int i = 0; i < n; i++)
        fillDepth(parent, i, depth);
 
    // The height of binary tree is maximum of all depths.
    // Find the maximum value in depth[] and assign it to ht.
    int ht = depth[0];
    for (int i=1; i<n; i++)
        if (ht < depth[i])
            ht = depth[i];
    return ht;
}