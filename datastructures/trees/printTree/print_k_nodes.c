/*

Given a root of a tree, and an integer k. Print all the nodes which are at k distance from root.

For example, in the below tree, 4, 5 & 8 are at distance 2 from root.
            1
          /   \
        2      3
      /  \    /
    4     5  8 

*/

void printKDistant(node *root , int k)    
{
   if(root == NULL) 
      return;
   if( k == 0 )
   {
      printf( "%d ", root->data );
      return ;
   }
   else
   {      
      printKDistant( root->left, k-1 ) ;
      printKDistant( root->right, k-1 ) ;
   }
}
     
