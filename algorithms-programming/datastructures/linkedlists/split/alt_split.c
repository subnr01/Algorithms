/*

Write a function AlternatingSplit() which takes one list and divides up its nodes to make
two smaller lists. The sublists should be made from alternating elements in the original
list. So if the original list is {a, b, a, b, a}, then one sublist should be {a, a, a} and the
other should be {b, b}.

*/



void AlternatingSplit ( struct node *head, struct node **head1, struct node **head2)
{
	struct node *a = NULL; 
	struct node *b = NULL; 
	struct node *current = head;
	while (current)
	{
		MoveNode(&a, &current); 
		if (current)
			MoveNode(&b, &current); 
	}
	*head1 = a;
	*head2 = b;
}

void MoveNode(struct node** dest, struct node** head) 
{
  /* the front source node  */
  struct node* newNode = *head; 
  assert(newNode != NULL);
   
  /* Advance the source pointer */
  *head = newNode->next;
   
  /* Link the old dest off the new node */
  newNode->next = *dest; 
   
  /* Move dest to point to the new node */
  *dest = newNode; 
}


