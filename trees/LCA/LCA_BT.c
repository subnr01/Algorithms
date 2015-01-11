/*

Given a binary tree, find the lowest common ancestor of two given nodes in the tree.


        _______3______
       /              \
    ___5__          ___1__
   /      \        /      \
   6      _2       0       8
         /  \
         7   4

 Using the tree above as an example, the LCA of nodes 5 and 1 is 3. 
 Please note that LCA for nodes 5 and 4 is 5.        


 /*  
 A Top-Down Approach (Worst case O(n2) ): 
 Let’s try the top-down approach
where we traverse the nodes from the top to the bottom. First, if the current
node is one of the two nodes, it must be the LCA of the two nodes. If not, we
count the number of nodes that matches either p or q in the left subtree (which
we call totalMatches). If totalMatches equals 1, then we know the right subtree
will contain the other node. Therefore, the current node must be the LCA. If
totalMatches equals 2, we know that both nodes are contained in the left
subtree, so we traverse to its left child. Similar with the case where
totalMatches equals 0 where we traverse to its right child.

*/

// Return #nodes that matches P or Q in the subtree.
int countMatchesPQ(Node *root, Node *p, Node *q) {
  if (!root) return 0;
  int matches = countMatchesPQ(root->left, p, q) + countMatchesPQ(root->right, p, q);
  if (root == p || root == q)
    return 1 + matches;
  else
    return matches;
}
 
Node *LCA(Node *root, Node *p, Node *q) {
  if (!root || !p || !q) return NULL;
  if (root == p || root == q) return root;
  int totalMatches = countMatchesPQ(root->left, p, q);
  if (totalMatches == 1)
    return root;
  else if (totalMatches == 2)
    return LCA(root->left, p, q);
  else /* totalMatches == 0 */
    return LCA(root->right, p, q);
}


/*
What is the run time complexity of this top-down approach?

First, just for fun, we assume that the tree contains n nodes and is balanced
(with its height equals to log(n) ). In this case, the run time complexity would
be O(n). Most people would guess a higher ordered complexity than O(n) due to
the function countMatchesPQ() traverses the same nodes over and over again.
Notice that the tree is balanced, you cut off half of the nodes you need to
traverse in each recursive call of LCA() function. The proof that the complexity
is indeed O(n) is left as an exercise to the reader.

What if the tree is not necessarily balanced? Then in the worst case the
complexity could go up to O(n2). Why? Could you come up with such case? (Hint:
The tree might be a degenerate tree).

*/

/*
A Bottom-up Approach (Worst case O(n) ):


Using a bottom-up approach, we can improve over the top-down approach by
avoiding traversing the same nodes over and over again.

We traverse from the bottom, and once we reach a node which matches one of the
two nodes, we pass it up to its parent. The parent would then test its left and
right subtree if each contain one of the two nodes. If yes, then the parent must
be the LCA and we pass its parent up to the root. If not, we pass the lower node
which contains either one of the two nodes (if the left or right subtree
contains either p or q), or NULL (if both the left and right subtree does not
contain either p or q) up.

Sounds complicated? Surprisingly the code appears to be much simpler than the top-down one.

*/

Node *LCA(Node *root, Node *p, Node *q) {
  if (!root) return NULL;
  if (root == p || root == q) return root;
  Node *L = LCA(root->left, p, q);
  Node *R = LCA(root->right, p, q);
  if (L && R) return root;  // if p and q are on both sides
  return L ? L : R;  // either one of p,q is on one side OR p,q is not in L&R subtrees
}




/*

With parent pointer

A little creativity is needed here. Since we have the parent pointer, we could
easily get the distance (height) of both nodes from the root. Once we knew both
heights, we could subtract from one another and get the height’s difference
(dh). If you observe carefully from the previous solution, the node which is
closer to the root is always dh steps ahead of the deeper node. We could
eliminate the need of marking visited nodes altogether. Why?

The reason is simple, if we advance the deeper node dh steps above, both nodes
would be at the same depth. Then, we advance both nodes one level at a time.
They would then eventually intersect at one node, which is the LCA of both
nodes. If not, one of the node would eventually reach NULL (root’s parent),
which we conclude that both nodes are not in the same tree. However, that part
of code shouldn’t be reached, since the problem statement assumed that both
nodes are in the same tree.

*/

int getHeight(Node *p) {
  int height = 0;
  while (p) {
    height++;
    p = p->parent;
  }
  return height;
}
 
// As root->parent is NULL, we don't need to pass root in.
Node *LCA(Node *p, Node *q) {
  int h1 = getHeight(p);
  int h2 = getHeight(q);
  // swap both nodes in case p is deeper than q.
  if (h1 > h2) {
    swap(h1, h2);
    swap(p, q);
  }
  // invariant: h1 <= h2.
  int dh = h2 - h1;
  for (int h = 0; h < dh; h++)
    q = q->parent;
  while (p && q) {
    if (p == q) return p;
    p = p->parent;
    q = q->parent;
  }
  return NULL;  // p and q are not in the same tree
}