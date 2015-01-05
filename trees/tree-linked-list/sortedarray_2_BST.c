BinaryTree* sortedArrayToBST(int arr[], int start, int end) {
  if (start > end) return NULL;
  // same as (start+end)/2, avoids overflow.
  int mid = start + (end - start) / 2;
  BinaryTree *node = new BinaryTree(arr[mid]);
  node->left = sortedArrayToBST(arr, start, mid-1);
  node->right = sortedArrayToBST(arr, mid+1, end);
  return node;
}
 
BinaryTree* sortedArrayToBST(int arr[], int n) {
  return sortedArrayToBST(arr, 0, n-1);
}

