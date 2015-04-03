/*

Check whether a linkedlist is a palindrome.

*/


/*

METHOD 1 (Use a Stack)
A simple solution is to use a stack of list nodes. This mainly involves three steps.
1) Traverse the given list from head to tail and push every visited node to stack.
2) Traverse the list again. For every visited node, pop a node from stack and compare data of popped node with currently visited node.
3) If all nodes matched, then return true, else false.

Time complexity of above method is O(n), but it requires O(n) extra space. Following methods solve this with constant extra space.


METHOD 2 (By reversing the list)
This method takes O(n) time and O(1) extra space.
1) Get the middle of the linked list.
2) Reverse the second half of the linked list.
3) Check if the first half and second half are identical.
4) Construct the original linked list by reversing the second half again and attaching it back to the first half


*/


int ispalindrome_rev(struct node **first, struct node *last)
{

        if ( !last) {
                return 1;
        }

        if (!ispalindrome_rev(first, last->next))
                return 0;

        if ( last->data == (*first)->data) {
                (*first) = (*first)->next;
                return 1;
        }
        else {
                return 0;
        }
}

