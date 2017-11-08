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
    public TreeNode trimBST(TreeNode root, int L, int R) {
        if (root == null) {
            return null;
        }
        if (root.val > R) {
            return trimBST(root.left, L, R);
        } else if (root.val < L) {
            return trimBST(root.right, L, R);
        } else {
            trimLeftChild(root, L, R);
            trimRightChild(root, L, R);
            return root;
        }
    }

    public void trimLeftChild(TreeNode root, int L, int R) {
        while (root.left != null) {
            if (root.left.val < L) {
                root.left = root.left.right;
            } else {
                break;
            }
        }
        if (root.left != null) {
            trimLeftChild(root.left, L, R);
        }
    }

    public void trimRightChild(TreeNode root, int L, int R) {
        while (root.right != null) {
            if (root.right.val > R) {
                root.right = root.right.left;
            } else {
                break;
            }
        }
        if (root.right != null) {
            trimRightChild(root.right, L, R);
        }
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
        Solution s = new Solution();
        TreeNode n1 = new TreeNode(1);
        TreeNode n2 = new TreeNode(0);
        TreeNode n3 = new TreeNode(2);
        n1.left = n2;
        n1.right = n3;
        print(n1);
        TreeNode r = s.trimBST(n1, 1, 2);
        print(r);

        TreeNode n4 = new TreeNode(3);
        TreeNode n5 = new TreeNode(0);
        TreeNode n6 = new TreeNode(4);
        TreeNode n7 = new TreeNode(2);
        TreeNode n8 = new TreeNode(1);
        n4.left = n5;
        n4.right = n6;
        n5.right = n7;
        n7.left = n8;
        print(n4);
        r = s.trimBST(n4, 0, 0);
        print(r);

        TreeNode n9 = new TreeNode(3);
        TreeNode n10 = new TreeNode(1);
        TreeNode n11 = new TreeNode(4);
        TreeNode n12 = new TreeNode(2);
        n9.left = n10;
        n9.right = n11;
        n10.right = n12;
        print(n9);
        r = s.trimBST(n9, 3, 4);
        print(r);
    }
}