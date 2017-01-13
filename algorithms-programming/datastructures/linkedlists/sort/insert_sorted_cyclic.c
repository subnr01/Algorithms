/*

Given a node from a cyclic linked list which has been sorted, write 
a function to insert a value into the list such that it remains a cyclic 
sorted list. The given node can be any single node in the list.

*/


void insert(Node ** head, int x) {
  if (!head) {
    *head = new Node(x);
    (*aNode)->next = *(head);
    return;
  }
 
  Node *first = (*head);
  Node *second = (*head)->next;
  while(second != head)
  {
    if (x <= first->data && x >= second->data) break;   // For case 1)
    first = second;
    second = second->next;
  
  } 
 
  Node *newNode = new Node(x);
  newNode->next = second;
  first->next = newNode;
  
  if (x <= second->data) {
    *head = newNode;
  }
}
