


/*
Find out the maximum sum of
 value from root to each leaf
*/




find_Max(Node *root){
if (root==null)
return 0;
else
return max((find_Max(root->left), find_Max(root->right))+root->value;
}