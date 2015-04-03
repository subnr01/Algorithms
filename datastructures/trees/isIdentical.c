
bool isIdentical( struct tree *node1, struct tree * node2)
{
    /*
     * Cases to be covered:
     * 1. Both  are  null
     * 2. one of them is null;
     * 3. structure does not match
     * 4. structure match
     */
    
      if ( !node1 && !node2) {
          return true;
      }

      if ( !node1 && node2)
          return false;

      if ( node1 && !node2)
          return false;

      if ( node1->data != node2->data)
          return false;


      return ( isIdentical ( node1->right, node2->right)  && ( node1->left, node2->left));


    
