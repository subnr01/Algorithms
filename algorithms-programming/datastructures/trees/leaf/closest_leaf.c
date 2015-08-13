/*

Given a Binary Tree and a key ‘k’, find distance of the closest leaf from ‘k’.

Examples:

              A
            /    \    
           B       C
                 /   \  
                E     F   
               /       \
              G         H
             / \       /
            I   J     K

Closest leaf to 'H' is 'K', so distance is 1 for 'H'
Closest leaf to 'C' is 'B', so distance is 2 for 'C'
Closest leaf to 'E' is either 'I' or 'J', so distance is 2 for 'E' 
Closest leaf to 'B' is 'B' itself, so distance is 0 for 'B' 


*/


/*

Solution

The idea is to traverse the given tree in preorder and keep track of ancestors
in an array. When we reach the given key, we evaluate distance of the closest
leaf in subtree rooted with given key. We also traverse all ancestors one by one
and find distance of the closest leaf in the subtree rooted with ancestor. We
compare all distances and return minimum.

*/



// A utility function to find distance of closest leaf of the tree
// rooted under given root
int closestDown(struct Node *root)
{
    // Base cases
    if (root == NULL)
        return INT_MAX;
    if (root->left == NULL && root->right == NULL)
        return 0;
 
    // Return minimum of left and right, plus one
    return 1 + getMin(closestDown(root->left), closestDown(root->right));
}
 
// Returns distance of the cloest leaf to a given key 'k'.  The array
// ancestors is used to keep track of ancestors of current node and
// 'index' is used to keep track of curremt index in 'ancestors[]'
int findClosestUtil(struct Node *root, char k, struct Node *ancestors[],
                                               int index)
{
    // Base case
    if (root == NULL)
        return INT_MAX;
 
    // If key found
    if (root->key == k)
    {
        //  Find the cloest leaf under the subtree rooted with given key
        int res = closestDown(root);
 
        // Traverse all ancestors and update result if any parent node
        // gives smaller distance
        for (int i = index-1; i>=0; i--)
            res = getMin(res, index - i + closestDown(ancestors[i]));
        return res;
    }
 
    // If key node found, store current node and recur for left and
    // right childrens
    ancestors[index] = root;
    return getMin(findClosestUtil(root->left, k, ancestors, index+1),
                  findClosestUtil(root->right, k, ancestors, index+1));
 
}
 
// The main function that returns distance of the closest key to 'k'. It
// mainly uses recursive function findClosestUtil() to find the closes
// distance.
int findClosest(struct Node *root, char k)
{
    // Create an array to store ancestors
    // Assumptiom: Maximum height of tree is 100
    struct Node *ancestors[100];
 
    return findClosestUtil(root, k, ancestors, 0);
}