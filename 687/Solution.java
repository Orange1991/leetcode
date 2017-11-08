import java.lang.Math;

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
    public int longestUnivaluePath(TreeNode root) {
        int[] result = new int[1];
        result[0] = 0;
        if (root != null) {
            pathFromRootLen(root, result);
        }
        return result[0];
    }

    /**
     * Return the max len of path which start from root and not cross the root node.
     * When computing the max len of path, recursively visit every node and try to compute the length of path that
     * cross the root node and update the max path value.
     */
    private int pathFromRootLen(TreeNode root, int[] result) {
        int pathFromL = 0;
        int pathFromR = 0;
        int pathFromRootToL = 0;
        int pathFromRootToR = 0;
        if (root.left != null) {
            pathFromL = pathFromRootLen(root.left, result);
            pathFromRootToL = root.left.val == root.val ? 1 + pathFromL : 0;
        }
        if (root.right != null) {
            pathFromR = pathFromRootLen(root.right, result);
            pathFromRootToR = root.right.val == root.val ? 1 + pathFromR : 0;
        }
        int pathCrossRoot = pathFromRootToL + pathFromRootToR;
        if (result[0] < pathCrossRoot) {
            result[0] = pathCrossRoot;
        }
        return Math.max(pathFromRootToL, pathFromRootToR);
    }

    public static void main(String[] args) {
        TreeNode t1 = new TreeNode(1);
        TreeNode t2 = new TreeNode(4);
        TreeNode t3 = new TreeNode(5);
        TreeNode t4 = new TreeNode(4);
        TreeNode t5 = new TreeNode(4);
        TreeNode t6 = new TreeNode(5);
        t1.left = t2;
        t1.right = t3;
        t2.left = t4;
        t2.right = t5;
        t3.right = t6;
        System.out.println(new Solution().longestUnivaluePath(t1));
    }
}