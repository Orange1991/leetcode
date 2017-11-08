/**
 * Definition for a binary tree node.
 */
class TreeNode {
  int val;
  TreeNode left;
  TreeNode right;
  TreeNode(int x) { val = x; }
}

public class Solution {
  public TreeNode constructMaximumBinaryTree(int[] nums) {
    return constructMaximumBinaryTree(nums, 0, nums.length - 1);
  }
  private TreeNode constructMaximumBinaryTree(int[] nums, int from, int to) {
    if (from > to) {
      return null;
    }
    TreeNode node = new TreeNode(nums[from]);
    if (from == to) {
      return node;
    }
    int cur = from;
    while (cur <= to) {
      int nextBig = cur + 1;
      while (nextBig <= to && nums[nextBig] < nums[cur]) {
        ++nextBig;
      }
      if (nextBig <= to) {
        TreeNode parent = new TreeNode(nums[nextBig]);
        node.right = constructMaximumBinaryTree(nums, cur + 1, nextBig - 1);
        parent.left = node;
        cur = nextBig;
        node = parent;
      } else {
        node.right = constructMaximumBinaryTree(nums, cur + 1, to);
        break;
      }
    }
    return node;
  }

  private static void print(TreeNode root) {
    if (root == null) {
      System.out.println("null");
    } else {
      print(root, 0);
    }
    System.out.println("-----------------------------");
  }

  private static void print(TreeNode root, int level) {
    if (root == null) {
      return;
    }
    print(root.right, level + 1);
    StringBuilder s = new StringBuilder();
    int restTab = level;
    while (restTab > 0) {
      s.append("\t");
      --restTab;
    }
    s.append(root.val);
    System.out.println(s.toString());
    print(root.left, level + 1);
  }

  public static void main(String[] args) {
    int[] nums = {3,2,1,6,0,5};
    // int[] nums = {1,2,3};
    Solution s = new Solution();
    TreeNode node = s.constructMaximumBinaryTree(nums);
    print(node);
  }
}