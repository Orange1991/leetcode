import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

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
  public List<TreeNode> findDuplicateSubtrees(TreeNode root) {
    List<TreeNode> res = new ArrayList<TreeNode>();
    Map<String, Integer> map = new HashMap<String, Integer>();
    postOrderTraversal(root, map, res);
    return res;
  }

  private String postOrderTraversal(TreeNode root, Map<String, Integer> map, List<TreeNode> res) {
    String s;
    if (root == null) {
      s = "#";
    } else {
      s = root.val + "," + postOrderTraversal(root.left, map, res) + postOrderTraversal(root.right, map, res);
    }
    if (!"#".equals(s)) {
      Integer cur = map.get(s);
      if (cur == null) {
        map.put(s, 1);
      } else {
        if (cur == 1) {
          res.add(root);
          map.put(s, 2);
        }
      }
    }
    return s;
  }

  private static String printNode(TreeNode node) {
    if (node == null) {
      return "null";
    }
    return "val: " + node.val + ", left: " + printNode(node.left) + ", right: " + printNode(node.right);
  }

  public static void main(String[] args) {
    /* Test 1
    TreeNode n1, n2, n3, n4, n5, n6, n7;
    n1 = new TreeNode(1);
    n2 = new TreeNode(2);
    n3 = new TreeNode(3);
    n4 = new TreeNode(4);
    n5 = new TreeNode(2);
    n6 = new TreeNode(4);
    n7 = new TreeNode(4);
    n1.left = n2;
    n1.right = n3;
    n2.left = n4;
    n3.left = n5;
    n3.right = n6;
    n5.left = n7;
    */
    /* Test 2
    TreeNode n1, n2, n3, n4, n5;
    n1 = new TreeNode(2);
    n2 = new TreeNode(2);
    n3 = new TreeNode(2);
    n4 = new TreeNode(3);
    n5 = new TreeNode(3);
    n1.left = n2;
    n1.right = n3;
    n2.left = n4;
    n3.left = n5;
     */
    TreeNode n1, n2, n3, n4, n5, n6;
    n1 = new TreeNode(0);
    n2 = new TreeNode(0);
    n3 = new TreeNode(0);
    n4 = new TreeNode(0);
    n5 = new TreeNode(0);
    n6 = new TreeNode(0);
    n1.left = n2;
    n1.right = n3;
    n2.left = n4;
    n3.right = n5;
    n5.right = n6;
    List<TreeNode> res = new Solution().findDuplicateSubtrees(n1);
    for (TreeNode node : res) {
      System.out.println(printNode(node));
    }
  }
}