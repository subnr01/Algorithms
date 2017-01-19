/*
Find whether a tree is height balanced or not
*/







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

