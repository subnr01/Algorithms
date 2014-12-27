/*

Given Preorder traversal of a BST, check if each non-leaf node has only one child. 
Assume that the BST contains unique entries.

Examples

Input: pre[] = {20, 10, 11, 13, 12}
Output: Yes
The give array represents following BST. In the following BST, every internal
node has exactly 1 child. Therefor, the output is true.

        20
       /
      10
       \
        11
          \
           13
           /
         12

*/


/* 
if all internal nodes have only one child in a BST, then all the descendants
of every node are either smaller or larger than the node. The reason is simple,
since the tree is BST and every node has only one child, all descendants of a
node will either be on left side or right side, means all descendants will
either be smaller or greater. 
*/


bool hasOnlyOneChild(int pre[], int size)
{
    int nextDiff, lastDiff;
 
    for (int i=0; i<size-1; i++)
    {
        nextDiff = pre[i] - pre[i+1];
        lastDiff = pre[i] - pre[size-1];
        if (nextDiff*lastDiff < 0)
            return false;;
    }
    return true;
}


