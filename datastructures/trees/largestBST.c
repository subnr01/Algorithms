/*

Given a binary tree, find the largest subtree which is a 
Binary Search Tree (BST), where largest means subtree with 
largest number of nodes in it.



It’s important that you understand the question correctly. 
Let’s try an example below. 
Which is the largest BST subtree?

         ____10____
        /          \
      __5_         15_
     /    \           \
     1     8           7

For most people, there would be two possible interpretations for the term “subtree”.

Is this ( subtree (1) ) the largest BST subtree?

         ____10____
        /          \
      __5_         15     -------- subtree (1)
     /    \ 
     1     8 
How about this one ( subtree (2) ) ?

      __5_
     /    \               -------- subtree (2)
     1     8 

According to Wikipedia, a subtree of a tree T is a tree consisting of a node in
T and all of its descendants in T. Therefore, there is no doubt that subtree (2)
is the correct answer, as subtree (1) does not include all of its descendants.
It is important that you understand the term subtree correctly. If you are not
sure, ask the interviewer and you should not make any assumptions.


*/

/*

A Bottom-up Approach:

The naive approach is using a top-down approach. It is hardly efficient, simply
because we are calling isBST() over and over again. Each time isBST() is called,
it traverses down to the leaves to verify if the subtree is a BST.

Let’s think from another perspective. Instead of traversing down the tree, why
not traverse up the tree using a bottom-up approach? In other words, we verify
the deeper nodes before we verify if the above nodes satisfy the BST
requirements.

The main reason of doing this is when one of the nodes does not satisfy the BST
properties, all subtrees above (which includes this node as well) must also not
satisfy the BST requirements.

First, let’s review our definition of a BST. A tree is a BST if the following
properties are satisfied:

Both left and right subtrees of a node are BSTs. The node’s value is greater
than its left subtree’s maximum. The node’s value is less than its right
subtree’s minimum. Using a bottom-up approach, we need to pass some information
up the tree. Obviously, we need to pass minimum and maximum values of the
subtree as we traverse up the tree, so the above subtrees could be verified for
BST’s properties.

As compared to the top-down approach, the bottom-up approach is such an awesome
choice because the results for total number of nodes could be passed up the
tree. This saves us from recalculating over and over again. The total number of
nodes for a subtree is simply the total number of nodes of its left and right
subtrees plus one.

Isn’t the bottom-up approach neat? It acts like magic until you understand it,
and solves all the problems that the top-down approach has. The run-time
complexity for the bottom-up approach is O(n). Beware of this gotcha when you
implement the algorithm. Even though a node’s left subtree is not a BST, you
must still continue traverse its right subtree as the largest BST subtree might
be contained in its right subtree.

*/

// Find the largest BST subtree in a binary tree.
// If the subtree is a BST, return total number of nodes.
// If the subtree is not a BST, -1 is returned.
int findLargestBSTSubtree(BinaryTree *p, int &min, int &max, 
                   int &maxNodes, BinaryTree *& largestBST) {
  if (!p) return 0;
  bool isBST = true;
  int leftNodes = findLargestBSTSubtree(p->left, min, max, maxNodes, largestBST);
  int currMin = (leftNodes == 0) ? p->data : min;
  if (leftNodes == -1 || 
     (leftNodes != 0 && p->data <= max))
    isBST = false;
  int rightNodes = findLargestBSTSubtree(p->right, min, max, maxNodes, largestBST);
  int currMax = (rightNodes == 0) ? p->data : max;
  if (rightNodes == -1 || 
     (rightNodes != 0 && p->data >= min))
    isBST = false;
  if (isBST) {
    min = currMin;
    max = currMax;
    int totalNodes = leftNodes + rightNodes + 1;
    if (totalNodes > maxNodes) {
      maxNodes = totalNodes;
      largestBST = p;
    }
    return totalNodes;
  } else {
    return -1;   // This subtree is not a BST
  }
}
 
BinaryTree* findLargestBSTSubtree(BinaryTree *root) {
  BinaryTree *largestBST = NULL;
  int min, max;
  int maxNodes = INT_MIN;
  findLargestBSTSubtree(root, min, max, maxNodes, largestBST);
  return largestBST;
}

