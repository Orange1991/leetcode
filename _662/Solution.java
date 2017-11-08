package _662;

import java.util.Queue;
import java.util.LinkedList;

import util.TreeNode;

class Solution {
  public int widthOfBinaryTree(TreeNode root) {
    if (root == null) return 0;
    Queue<TreeNode> cur = null;
    Queue<TreeNode> next = new LinkedList<TreeNode>();
    next.add(root);
    TreeNode last = root;
    int max = 0;
    while (!next.isEmpty()) {
      cur = next;
      next = new LinkedList<TreeNode>();
      TreeNode node = null;
      TreeNode nextLast = null;
      int width = 0;

      while (!cur.isEmpty()) {
        node = cur.poll();
        if (node != null) {
          break;
        }
      }
      while (!cur.isEmpty()) {
        if (node == last) {
          break;
        }
        ++width;
        if (node != null) {
          next.add(node.left);
          next.add(node.right);
          if (node.left != null) {
            nextLast = node.right != null ? node.right : node.left;
          } else if (node.right != null) {
            nextLast = node.right;
          }
        } else {
          next.add(null);
          next.add(null);
        }
        node = cur.poll();
      }
      ++width;
      if (width > max) {
        max = width;
      }
      next.add(node.left);
      next.add(node.right);
      if (node.left != null) {
        nextLast = node.right != null ? node.right : node.left;
      } else if (node.right != null) {
        nextLast = node.right;
      }
      if (nextLast == null) {
        break;
      } else {
        last = nextLast;
      }
    }

    return max;
  }

private static void test(String[] nums) {
  Solution s = new Solution();
  TreeNode tree = TreeNode.constructTree(nums);
  TreeNode.printTree(tree);
  System.out.println("width: " + s.widthOfBinaryTree(tree) + "\n-----------------------------");
}

  public static void main(String[] args) {
    // Test 1
    String[] t1 = {"1", "3", "2", "5", "3", "null", "9"};
    test(t1);

    // Test 2
    String[] t2 = {"1", "3", "null", "5", "3"};
    test(t2);

    // Test 3
    String[] t3 = {"1", "3", "2", "5"};
    test(t3);

    // Test 4
    String[] t4 = {"1", "3", "2", "5", "null", "null", "9", "6", "null", "null", "7"};
    test(t4);
  }
}