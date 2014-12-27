/*

Given a binary tree and two level numbers ‘low’ and ‘high’, print nodes from level low to level high.

For example consider the binary tree given in below diagram. 

Input: Root of below tree, low = 2, high = 4

Output:
8 22
4 12
10 14<>


*/



/*

We can print nodes in O(n) time using queue based iterative level
order traversal. The idea is to do simple queue based level order
traversal. While doing inorder traversal, add a marker node at the
end. Whenever we see a marker node, we increase level number. If level
number is between low and high, then print nodes.

*/



/* Given a binary tree, print nodes from level number 'low' to level
   number 'high'*/
void printLevels(Node* root, int low, int high)
{
    queue <Node *> Q;
 
    Node *marker = new Node; // Marker node to indicate end of level
 
    int level = 1;   // Initialize level number
 
    // Enqueue the only first level node and marker node for end of level
    Q.push(root);
    Q.push(marker);
 
    // Simple level order traversal loop
    while (Q.empty() == false)
    {
        // Remove the front item from queue
        Node *n = Q.front();
        Q.pop();
 
        // Check if end of level is reached
        if (n == marker)
        {
            // print a new line and increment level number
            cout << endl;
            level++;
 
            // Check if marker node was last node in queue or
            // level number is beyond the given upper limit
            if (Q.empty() == true || level > high) break;
 
            // Enqueue the marker for end of next level
            Q.push(marker);
 
            // If this is marker, then we don't need print it
            // and enqueue its children
            continue;
        }
 
        // If level is equal to or greater than given lower level,
        // print it
        if (level >= low)
            cout << n->key << " ";
 
        // Enqueue children of non-marker node
        if (n->left != NULL)  Q.push(n->left);
        if (n->right != NULL) Q.push(n->right);
    }
}