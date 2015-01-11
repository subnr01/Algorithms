 /*
 Consider lines of slope -1 passing between nodes (dotted lines in below diagram). Diagonal sum in a binary tree is sum 
 of all node’s data lying between these lines. Given a Binary Tree, print all diagonal sums.

For the following input tree, output should be 9, 19, 42.
9 is sum of 1, 3 and 5.
19 is sum of 2, 6, 4 and 7.
42 is sum of 9, 10, 11 and 12.

        1
    2       3
 9      6  4    5   
  10  11  12 7
*/

/*

The idea is to keep track of vertical distance from top diagonal passing through root. We increment the
vertical distance we go down to next diagonal.
1. Add root with vertical distance as 0 to the queue.
2. Process the sum of all right child and right of right child and so on.
3. Add left child current node into the queue for later processing. The vertical distance of left child is 
   vertical distance of current node plus 1.
4. Keep doing 2nd, 3rd and 4th step till the queue is empty.

*/

 // Diagonal sum method
    public void diagonalSum()
    {
        // Queue which stores tree nodes
        Queue<TreeNode> queue = new LinkedList<TreeNode>();
 
        // Map to store sum of node's data lying diagonally
        Map<Integer, Integer> map = new TreeMap<>();
 
        // Assign the root's vertical distance as 0.
        root.vd = 0;
 
        // Add root node to the queue
        queue.add(root);
 
        // Loop while the queue is not empty
        while (!queue.isEmpty())
        {
            // Remove the front tree node from queue.
            TreeNode curr = queue.remove();
 
            // Get the vertical distance of the dequeued node.
            int vd = curr.vd;
 
            // Sum over this node's right-child, right-of-right-child
            // and so on
            while (curr != null)
            {
                int prevSum = (map.get(vd) == null)? 0: map.get(vd);
                map.put(vd, prevSum + curr.data);
 
                // If for any node the left child is not null add
                // it to the queue for future processing.
                if (curr.left != null)
                {
                    curr.left.vd = vd+1;
                    queue.add(curr.left);
                }
 
                // Move to the current node's right child.
                curr = curr.right;
            }
        }
 
        // Make an entry set from map.
        Set<Entry<Integer, Integer>> set = map.entrySet();
 
        // Make an iterator
        Iterator<Entry<Integer, Integer>> iterator = set.iterator();
 
        // Traverse the map elements using the iterator.
        while (iterator.hasNext())
        {
            Map.Entry<Integer, Integer> me = iterator.next();
            System.out.print(me.getValue()+" ");
        }
    }
}
