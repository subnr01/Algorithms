/*

Remove duplicates from unsorted linked list
*/



/*
Without hash table 
*/

/* Function to remove duplicates from a unsorted linked list */
void removeDuplicates(struct node *start)
{
  struct node *ptr1, *ptr2, *dup;
  ptr1 = start;
 
  /* Pick elements one by one */
  while(ptr1 != NULL && ptr1->next != NULL)
  {
     ptr2 = ptr1;
 
     /* Compare the picked element with rest of the elements */
     while(ptr2->next != NULL)
     {
       /* If duplicate then delete it */
       if(ptr1->data == ptr2->next->data)
       {
          /* sequence of steps is important here */
          dup = ptr2->next;
          ptr2->next = ptr2->next->next;
          free(dup);
       }
       else /* This is tricky */
       {
          ptr2 = ptr2->next;
       }
     }
     ptr1 = ptr1->next;
  }
}


/* 
with hash table
*/


void deleteDups ( LinkedListNode n)
{
	Hashtable table = new Hashtable();
	LinkedListNode prev = NULL;

	while ( n!=NULL)
	{
		if (table.containsKey(n.data))
		{
			prev->next = n->next;
			free(n);
			n = prev->next;

		}
		else
		{
			table.put(n.data,true);
			prev = n;
			
		}
		n = n->next;

	}
}
