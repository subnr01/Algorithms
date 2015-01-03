/*

Given a Singly Linked List, starting from the second node delete all alternate
nodes of it. For example, if the given linked list is 1->2->3->4->5 then your
function should convert it to 1->3->5, and if the given linked list is
1->2->3->4 then convert it to 1->3.

*/


void deleteAltNode( struct node *head)
{
	if ( head == NULL)
		return;

	struct node *current, *next;

	current = head;
	next = current->left;

	while ( next != NULL) 
	{
	   current->left = next->left;
	   current = current->left;
	   free(next);
	   next = NULL;
	   if (current) {
		  next = current->left;
	   }
	}

}



void deleteAltNode_r(struct node *head)
{
	if (!head)
		return;

	struct node *next = head->left;
	
	if (!next)
		return;

	head->left = next->left;
	free(next);

	deleteAltNode_r(head->left);
}

