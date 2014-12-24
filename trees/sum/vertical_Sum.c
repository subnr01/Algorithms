/*

Given a Binary Tree, find vertical sum of the nodes that are in same vertical line. 
Print all sums through different vertical lines.

Examples:

      1
    /   \
  2      3
 / \    / \
4   5  6   7
The tree has 5 vertical lines

Vertical-Line-1 has only one node 4 => vertical sum is 4
Vertical-Line-2: has only one node 2=> vertical sum is 2
Vertical-Line-3: has three nodes: 1,5,6 => vertical sum is 1+5+6 = 12
Vertical-Line-4: has only one node 3 => vertical sum is 3
Vertical-Line-5: has only one node 7 => vertical sum is 7

So expected output is 4, 2, 12, 3 and 7



*/

/*
Have a hash table. 
Start with root = 0.
So every left u subtract -1 and every right you add 1.
Since  when you add 1, you update the same
hash entry, so all nodes in the same vertical line
map to the same entry
*/




 // A wrapper over VerticalSumUtil()
    private void VerticalSum(TreeNode root) {
  
        // base case
        if (root == null) { return; }
  
        // Creates an empty hashMap hM
        HashMap<Integer, Integer> hM = new HashMap<Integer, Integer>();
  
        // Calls the VerticalSumUtil() to store the vertical sum values in hM
        VerticalSumUtil(root, 0, hM);
  
        // Prints the values stored by VerticalSumUtil()
        if (hM != null) {
            System.out.println(hM.entrySet());
        }
    }
  
    // Traverses the tree in Inoorder form and builds a hashMap hM that
    // contains the vertical sum
    private void VerticalSumUtil(TreeNode root, int hD,
                                          HashMap<Integer, Integer> hM) {
  
        // base case
        if (root == null) {  return; }
  
        // Store the values in hM for left subtree
        VerticalSumUtil(root.left(), hD - 1, hM);
  
        // Update vertical sum for hD of this node
        int prevSum = (hM.get(hD) == null) ? 0 : hM.get(hD);
        hM.put(hD, prevSum + root.key());
  
        // Store the values in hM for right subtree
        VerticalSumUtil(root.right(), hD + 1, hM);
    }
}