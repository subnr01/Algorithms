/*

Given two Linked Lists, create union and intersection lists that contain union 
and intersection of the elements present in the given lists. Order of elments in 
output lists doesn’t matter.

Example:

Input:

   List1: 10->15->4->20
   lsit2:  8->4->2->10

Output:

   Intersection List: 4->10
   Union List: 2->8->20->4->15->10

*/



struct node *union( struct node *head1, struct node *head2)
{
	if ( !head1 && !head2)
		return NULL;
	
	sort(&head1);
	sort(&head2);

	struct node temp;

	struct node *start = &temp;

	while ( head1 != NULL && head2 != NULL)
	{
		if ( head1->data < head2->data)
		{
			start->next = newnode(head1->data);
			head1 = head1->next;
		} else if ( head1->data > head2->data )
		{
			start->next = newnode(head2->data);
			head2 = head2->next;
		}
		} else if ( head1->data == head2->data )
		{
			start->next = newnode(head2->data);
			head1 = head1->next;
			head2 = head2->next;
		}
		start = start->next;
	}
	
	while (head1)
	{
		start->next = newnode(head1->data);
		head1 = head1->next;
		start = start->next;		
	}

	while (head2)
	{
		start->next = newnode(head2->data);
		head1 = head1->next;
		start = start->next;		
	}

	start->next = NULL;
	return temp->next;

}



struct node *intersection( struct node *head1, struct node *head2)
{
	if ( !head1 && !head2)
		return NULL;
	
	sort(&head1);
	sort(&head2);

	struct node temp;

	struct node *start = &temp;

	while ( head1 != NULL && head2 != NULL)
	{
		
		if ( head1->data == head2->data )
		{
			start->next = newnode(head2->data);
			start = start->next;
		}
		if (head1->next > head2->next)
			head1 = head1->next;
		else
			head2 = head2->next;
		
	}
	
	if (start)
		start->next = NULL;
	
	return temp->next;

}