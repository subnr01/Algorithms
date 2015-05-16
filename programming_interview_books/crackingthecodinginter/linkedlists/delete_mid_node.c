
/* 
Delete middle of a linked list
*/

void delete( struct node *mid)
{
	if ( !mid->next)
		return;


	struct node *p = mid->next;

	mid->data = p->data; // Copy the data 
	
	// Change the pointer, now we have two 
	// pointers having same data
	mid->next = p->next;

	// free the next pointer
	free(p);
}