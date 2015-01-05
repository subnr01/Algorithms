// This is a modified in-order traversal adapted to this problem.
// prev (init to NULL) is used to keep track of previously traversed node.
// head pointer is updated with the list's head as recursion ends.
void treeToDoublyList(Node *p, Node *& prev, Node *& head) {
  if (!p) return;
  treeToDoublyList(p->left, prev, head);
  // current node's left points to previous node
  p->left = prev;
  if (prev)
    prev->right = p;  // previous node's right points to current node
  else
    head = p; // current node (smallest element) is head of
              // the list if previous node is not available
  // as soon as the recursion ends, the head's left pointer 
  // points to the last node, and the last node's right pointer
  // points to the head pointer.
  Node *right = p->right;
  head->left = p;
  p->right = head;
  // updates previous node
  prev = p;
  treeToDoublyList(right, prev, head);
}

// Given an ordered binary tree, returns a sorted circular
// doubly-linked list. The conversion is done in-place.
Node* treeToDoublyList(Node *root) {
  Node *prev = NULL;
  Node *head = NULL;
  treeToDoublyList(root, prev, head);
  return head;
}
