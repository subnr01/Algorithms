
/*

Given a Singly Linked List which has data members sorted in ascending order. 
Construct a Balanced Binary Search Tree which has same data members as the given Linked List.

Examples:

Input:  Linked List 1->2->3
Output: A Balanced BST 
     2   
   /  \  
  1    3 


Input: Linked List 1->2->3->4->5->6->7
Output: A Balanced BST
        4
      /   \
     2     6
   /  \   / \
  1   3  4   7  

Input: Linked List 1->2->3->4
Output: A Balanced BST
      3   
    /  \  
   2    4 
 / 
1

Input:  Linked List 1->2->3->4->5->6
Output: A Balanced BST
      4   
    /   \  
   2     6 
 /  \   / 
1   3  5   

*/


struct tree* Construct_tree ( struct node *head, int n)
{

	if (n <= 0)
		return NULL;

	struct tree *leftchild = Construct_tree(head, n/2)

	struct tree *root = newNode(head->data);
	root->left = leftchild;

	head = head->next;

	root->right = Construct_tree(head, n-n/2-1);

	return root;

}


