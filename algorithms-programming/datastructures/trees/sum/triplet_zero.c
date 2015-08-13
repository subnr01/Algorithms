
/*

Given a Balanced Binary Search Tree (BST), write a function
isTripletPresent() that returns true if there is a triplet in given
BST with sum equals to 0, otherwise returns false. Expected time
complexity is O(n^2) and only O(Logn) extra space can be used. You can
modify given Binary Search Tree. Note that height of a Balanced BST is
always O(Logn)

*/


/* 
Solution

Following is the solution that works in O(n^2) time and uses O(Logn) extra
space: 
1) Convert given BST to Doubly Linked List (DLL) 
2) Now iterate through every node of DLL and if the key of node is negative, 
then find a pair in DLL with sum equal to key of current node multiplied by -1. 
To find the pair, we
can use the approach used in hasArrayTwoCandidates() in method 1 of this post.

*/





// This function returns true if there is pair in DLL with sum equal
// to given sum. The algorithm is similar to hasArrayTwoCandidates()
// in method 1 of http://tinyurl.com/dy6palr
bool isPresentInDLL(node* head, node* tail, int sum)
{
    while (head != tail)
    {
        int curr = head->key + tail->key;
        if (curr == sum)
            return true;
        else if (curr > sum)
            tail = tail->left;
        else
            head = head->right;
    }
    return false;
}
 
// The main function that returns true if there is a 0 sum triplet in
// BST otherwise returns false
bool isTripletPresent(node *root)
{
    // Check if the given  BST is empty
    if (root == NULL)
       return false;
 
    // Convert given BST to doubly linked list.  head and tail store the
    // pointers to first and last nodes in DLLL
    node* head = NULL;
    node* tail = NULL;
    convertBSTtoDLL(root, &head, &tail);
 
    // Now iterate through every node and find if there is a pair with sum
    // equal to -1 * heaf->key where head is current node
    while ((head->right != tail) && (head->key < 0))
    {
        // If there is a pair with sum equal to  -1*head->key, then return
        // true else move forward
        if (isPresentInDLL(head->right, tail, -1*head->key))
            return true;
        else
            head = head->right;
    }
 
    // If we reach here, then there was no 0 sum triplet
    return false;
}
 
