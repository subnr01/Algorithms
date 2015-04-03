/*

Morris traversal for inorder

*/



/*
Solution

We create links to the inorder successor
and print the data using these links
and finally revert the changes 
to restore the original tree
*/





/* Function to traverse binary tree without recursion and 
   without stack */
void MorrisTraversal(struct tNode *root)
{
  struct tNode *current,*pre;
 
  if(root == NULL)
     return; 
 
  current = root;
  while(current != NULL)
  {                 
    if(current->left == NULL)
    {
      printf(" %d ", current->data);
      current = current->right;      
    }    
    else
    {
      /* Find the inorder predecessor of current */
      pre = current->left;
      while(pre->right != NULL && pre->right != current)
        pre = pre->right;
 
      /* Make current as right child of its inorder predecessor */
      if(pre->right == NULL)
      {
        pre->right = current;
        current = current->left;
      }
             
      /* Revert the changes made in if part to restore the original 
        tree i.e., fix the right child of predecssor */   
      else 
      {
        pre->right = NULL;
        printf(" %d ",current->data);
        current = current->right;      
      } /* End of if condition pre->right == NULL */
    } /* End of if condition current->left == NULL*/
  } /* End of while */
}
 