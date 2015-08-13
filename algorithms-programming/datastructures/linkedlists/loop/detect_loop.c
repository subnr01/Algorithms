/* 

Detect a loop in the linked list

*/


bool hasLoop(Node *head) {
  Node *slow = head, *fast = head;
  while (slow && fast && fast->next) {
    slow = slow->next;
    fast = fast->next->next;
    if (slow == fast)
      return true;
  }
  return false;
}

