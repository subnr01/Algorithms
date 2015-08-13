/*

Return the head of the loop
of a linked list

*/


1--> 2 --> 3 --> 4 --> 5 --> (6 --> 7 --> 8 -->9 -->10)

1--> 2 --> 3 --> 4 --> 5 --> 6 --> 7 --> (8 -->9 -->10)

Algorithm:

1. Use a slow pointer and a fast pointer and find where they meet.
2. Move a node from the head and the slow pointer together. The point 
   they meet is the loop




struct node *findloophead( struct node *head)
{
	struct node *slow = head;
	struct node *fast = head;

	while ( fast->next != NULL)
	{
		slow = slow->next;
		fast = fast->next;
		if ( !fast->next)
			fast = fast->next;
		if ( slow == fast)
			break;
	}

	if ( fast->next == NULL)
		return;


	struct node *p = head;

	while ( p != slow)
	{
		p = p->next;
		slow = slow->next;
	}

	return slow;

}

