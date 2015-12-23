/*


Construct a Balanced Binary Search Tree which has same data members as the given Doubly Linked List.
Given a Doubly Linked List which has data members sorted in ascending order.

 The tree must be constructed in-place (No new node should be allocated for tree conversion)
Input: Doubly Linked List 1 <--> 2 <-->3 <--> 4 <-->5 <--> 6 <--> 7
Output: A Balanced BST
        4
      /   \
     2     6
   /  \   / \
  1   3  4   7  


*/



struct node* doubly_bst( struct node **head, int n)
{
	if (n == 0)
		return NULL;

	//head points to the left child

	struct node *left = doubly_bst(head, n/2); //returns the left child
	
	struct node *root = *head;   //head points to the root of tree

	root->left = left;        //assigned the left child

	*head = *head->right;      //Now we point to the right child

	root->right = doubly_bst(head, n-n/2-1); //returns the right child

	return root;

}






}
