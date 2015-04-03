
/*

Serialize a binary tree

Store the Preorder traversal and a
marker for null pointers.

Let the marker for NULL pointers be '-1'
Input:
     12
    /
  13
Output: 12 13 -1 -1

Input:
      20
    /   \
   8     22 
Output: 20 8 -1 -1 22 -1 -1 


Deserialize a binary tree
Deserialization can be done by simply reading data from file one by one.

*/


#define MARKER -1
 
/* A binary tree Node has key, pointer to left and right children */
struct Node
{
    int key;
    struct Node* left, *right;
};



// This function stores a tree in a file pointed by fp
void serialize(Node *root, FILE *fp)
{
    // If current node is NULL, store marker
    if (root == NULL)
    {
        fprintf(fp, "%d ", MARKER);
        return;
    }
 
    // Else, store current node and recur for its children
    fprintf(fp, "%d ", root->key);
    serialize(root->left, fp);
    serialize(root->right, fp);
}
 
// This function constructs a tree from a file pointed by 'fp'
void deSerialize(Node **root, FILE *fp)
{
    // Read next item from file. If theere are no more items or next
    // item is marker, then return
    int val;
    if ( !fscanf(fp, "%d ", &val) || val == MARKER)
       return;
 
    // Else create node with this item and recur for children
    struct node *temp = newNode(val);
    *root = temp;
    deSerialize(&temp->left, fp);
    deSerialize(&temp->right, fp);
}

