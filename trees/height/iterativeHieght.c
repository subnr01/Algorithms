Below is the code for finding the maximum depth of a binary tree using post-order traversal, without recursion.



int maxDepthIterative(BinaryTree *root) {
  if (!root) return 0;
  stack<BinaryTree*> s;
  s.push(root);
  int maxDepth = 0;
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
      s.pop();
    }
    prev = curr;
    if (s.size() > maxDepth)
      maxDepth = s.size();
  }
  return maxDepth;
}
