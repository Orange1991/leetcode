
/**
 * Definition for a binary tree node.
 */
class TreeNode {
  int val;
  TreeNode left;
  TreeNode right;
  TreeNode(int x) { val = x; }
}

public class S2 {
  public TreeNode constructMaximumBinaryTree(int[] nums) {
    int len = nums.length;
    if (len == 0) return null;
    if (len == 1) return new TreeNode(nums[0]);
    int cur = 0;
    TreeNode node = new TreeNode(nums[0]);
    while (cur < len) {
      int nextBig = 1;
      while (nextBig < len && nums[nextBig] < nums[cur]) {
        ++nextBig;
      }
      if (nextBig < len) {
        TreeNode parent = new TreeNode(nums[nextBig]);
        parent.left = node;
        
      }
    }
  }
}
