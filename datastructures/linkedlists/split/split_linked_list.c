/* 
 
Split linkedlist in the middle

*/

/* 

Solution: We use two pointers (we call it a slow pointer and a fast pointer).
The slow pointer advances one node at a time, while the fast pointer advances
two nodes at a time. By the time the fast pointer reaches the end, the slow
pointer would have reached the splitting point (or near). Care must be taken to
account those special cases. Below is a solution that works for all cases.

*/



void FrontBackSplit(Node *head, Node **front, Node **back) {
  if (!head) return;  // Handle empty list
  Node *front_last_node;
  Node *slow = head;
  Node *fast = head;
  while (fast) {
    front_last_node = slow;
    slow = slow->next;
    fast = (fast->next) ? fast->next->next : NULL;
  }
  front_last_node->next = NULL;  // ends the front sublist
  *front = head;
  *back = slow;
}

