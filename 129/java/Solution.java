class TreeNode {
    int val;
    TreeNode left;
    TreeNode right;
    TreeNode(int x) { val = x; }
}

public class Solution {
    public int sumNumbers(TreeNode root) {
        sumRootToLeaf(root, 0);
        return sum;
    }
    
    private int sum = 0;

    private void sumRootToLeaf(TreeNode root, int val) {
        if (root == null) return;
        val *= 10;
        val += root.val;

        if (root.left == null && root.right == null) {
            sum += val;
            return;
        }

        sumRootToLeaf(root.left, val);
        sumRootToLeaf(root.right, val);
    }

    public static void main(String[] args) {
        TreeNode n1 = new TreeNode(1), n2 = new TreeNode(2), n3 = new TreeNode(3);
        n1.left = n2; 
        n1.right = n3;
        System.out.println(new Solution().sumNumbers(n1));
    }
}
