/*

Given a binary tree, print the elements in 
post-order iteratively without using recursion.


Post-order traversal is useful in some types of tree operations:

Tree deletion. In order to free up allocated memory of all nodes in a tree, 
the nodes must be deleted in the order where the current node can only be 
deleted when both of its left and right subtrees are deleted.
Evaluating post-fix notation.

*/

/* Solution: 
We use a prev variable to keep track of the previously-traversed
node. Let’s assume curr is the current node that’s on top of the stack. When
prev is curr‘s parent, we are traversing down the tree. In this case, we try to
traverse to curr‘s left child if available (ie, push left child to the stack).
If it is not available, we look at curr‘s right child. If both left and right
child do not exist (ie, curr is a leaf node), we print curr‘s value and pop it
off the stack.

If prev is curr‘s left child, we are traversing up the tree from the left. We
look at curr‘s right child. If it is available, then traverse down the right
child (ie, push right child to the stack), otherwise print curr‘s value and pop
it off the stack.

If prev is curr‘s right child, we are traversing up the tree from the right. In
this case, we print curr‘s value and pop it off the stack.

*/

void postOrderTraversalIterative(BinaryTree *root) {
  if (!root) return;
  stack<BinaryTree*> s;
  s.push(root);
  BinaryTree *prev = NULL;
  while (!s.empty()) {
    BinaryTree *curr = s.top();
    if (!prev || prev->left == curr || prev->right == curr) {
      if (curr->left)
        s.push(curr->left);
      else if (curr->right)
        s.push(curr->right);
    } else if (curr->left == prev) {
      if (curr->right)
        s.push(curr->right);
    } else {
      cout << curr->data << " ";
      s.pop();
    }
    prev = curr;
  }
}


/*

Another Solution

Push the root node to the first stack.
Pop a node from the first stack, and push it to the second stack.
Then push its left child followed by its right child to the first stack.
Repeat step 2) and 3) until the first stack is empty.
Once done, the second stack would have all the nodes ready to be 
traversed in post-order. Pop off the nodes from the second stack one 
by one and you’re done.

*/

