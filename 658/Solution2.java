import java.util.Arrays;
import java.util.ArrayList;
import java.util.Collections;;
import java.util.List;

public class Solution2 {
  class Node implements Comparable<Node> {
    public int val;
    public int diff;

    public Node(int val, int diff) {
      this.val = val;
      this.diff = diff;
    }

    public int compareTo(Node another) {
      if (diff > another.diff || diff == another.diff && val > another.val) {
        return 1;
      } else {
        return -1;
      }
    }
  }

  public List<Integer> findClosestElements(int[] arr, int k, int x) {
    Node[] nodes = new Node[arr.length];
    for (int i = 0, len = arr.length; i < len; ++i) {
      nodes[i] = new Node(arr[i], Math.abs(x - arr[i]));
    }
    Arrays.sort(nodes);
    List<Integer> res = new ArrayList<Integer>();
    int cur = 0;
    while (k-- > 0) {
      res.add(nodes[cur++].val);
    }
    Collections.sort(res);
    return res;
  }

  public static void main(String[] args) {
    int[] nums = {1,2,3,4,5,1,-3};
    Solution s = new Solution();
    List<Integer> res = s.findClosestElements(nums, 4, -1);
    for (int i = 0, len = res.size(); i < len; ++i) {
      System.out.print(res.get(i) + ", ");
    }
    int[] nums2 = {1,2,3,4,5};
    res = s.findClosestElements(nums2, 4, 3);
    for (int i = 0, len = res.size(); i < len; ++i) {
      System.out.print(res.get(i) + ", ");
    }
  }
}
