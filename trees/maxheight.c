
int maxheight( struct tree *node)
{

    if ( !node)
        return 0;

    int lh, rh;

    lh = maxheight(node->left);
    rh = maxheight(node->right);

    if (lh > rh)
    	hieght = lh;
    else 
    	hieght = rh;

    return (hieght+1);

}
