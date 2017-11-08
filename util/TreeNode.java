package util;

import java.util.Queue;
import java.util.LinkedList;

public class TreeNode {
  public int val;
  public TreeNode left;
  public TreeNode right;
  TreeNode(int x) { val = x; }

  public static void printTree(TreeNode root) {
    if (root == null) {
      System.out.println("null");
    } else {
      print(root, "");
    }
    System.out.println("-----------------------------");
  }

  private static void print(TreeNode root, String prefix) {
    if (root != null) {
      print(root.right, prefix + "\t");
    }
    System.out.println(prefix + (root == null ? "" : root.val));
    if (root != null) {
      print(root.left, prefix + "\t");
    }
  }

  public static TreeNode constructTree(String[] nums) {
    if (nums.length == 0 || nums[0].equals("null")) return null;
    TreeNode root = new TreeNode(Integer.parseInt(nums[0]));
    int len = nums.length;
    int cur = 1;
    Queue<TreeNode> nodes = new LinkedList<TreeNode>();
    nodes.add(root);
    while (cur < len && !nodes.isEmpty()) {
      TreeNode node = nodes.poll();
      if (!nums[cur].equals("null")) {
        node.left = new TreeNode(Integer.parseInt(nums[cur]));
        nodes.add(node.left);
      }
      ++cur;
      if (cur < len && !nums[cur].equals("null")) {
        node.right = new TreeNode(Integer.parseInt(nums[cur]));
        nodes.add(node.right);
      }
      ++cur;
    }
    return root;
  }
}
