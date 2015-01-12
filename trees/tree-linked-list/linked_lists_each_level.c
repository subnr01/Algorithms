

void print_d_level_node(BTNode *root)
{
    list<BTNode *> l0, l1; // 2 linked lists
    list<BTNode *>::iterator it;
    int level = 0;

    l0.push_back(root);

    while(!l0.empty()){

        cout << "level " << level++ << " -- ";
        /* Print the tree elements at level */
        for(it = l0.begin(); it != l0.end(); ++it){
            cout << (*it)->v << " ";
        }
        cout << endl;

        /* Push all the children into new linked list */
        for(it = l0.begin(); it != l0.end(); ++it){
            if((*it)->left != NULL){
                l1.push_back((*it)->left);
            }

            if((*it)->right != NULL){
                l1.push_back((*it)->right);
            }
        }

        /* No more children */
        if(l1.empty()){
            break;
        }


        l0.clear();
        l0.resize(l1.size());   // make sure enough space is reserved

        /* Copy l0 linked list elements to l1 */
        copy(l1.begin(), l1.end(), l0.begin());

        l1.clear();
    }

}