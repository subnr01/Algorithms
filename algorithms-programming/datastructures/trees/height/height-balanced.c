/*
Find whether a tree is height balanced or not
*/


bool isBalanced(struct node *root) 
{ 
int lh; /* for height of left subtree */ 
int rh; /* for height of right subtree */ 

/* If tree is empty then return true */ 
if(root == NULL) 
return 1; 

/* Get the height of left and right sub trees */ 
lh = height(root->left); 
rh = height(root->right); 

if( abs(lh-rh) <= 1 &&  
isBalanced(root->left) && isBalanced(root->right)) 
return 1; 

/* If we reach here then tree is not height-balanced */ 
return 0; 
} 


/* Another solution */

class Solution {
public:
    bool isBalanced(TreeNode *root) {
        int height = 0;
        return isBalancedRe(root, height);
    }
    
    bool isBalancedRe(TreeNode *root, int &height){
        if (!root) return true;
        
        int leftHeight = 0, rightHeight = 0;
        if (!isBalancedRe(root->left, leftHeight)) return false;
        if (!isBalancedRe(root->right, rightHeight)) return false;
        if (abs(leftHeight-rightHeight) > 1) return false;
        
        height = 1 + max(leftHeight, rightHeight);
        return true;
    }
};

