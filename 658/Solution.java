import java.util.ArrayList;
import java.util.Collections;
import java.util.List;

class Solution {
  private class Tree {
    private Node head;
    private Node tail;

    public Tree() {
      this.head = new Node();
      this.tail = new Node();
      this.head.next = this.tail;
      this.tail.prev = this.head;
    }

    public Node add(int val, int diff) {
      Node p = head, n = p.next;
      while (n != tail && (n.diff < diff || n.diff == diff && n.val < val)) {
        p = n;
        n = n.next;
      }
      return add(p, n, val, diff);
    }

    public Node add(Node p, Node n, int val, int diff) {
      Node newNode = new Node(val, diff);
      p.next = newNode;
      newNode.prev = p;
      newNode.next = n;
      n.prev = newNode;
      return newNode;
    }

    public Node add(Node node, int val, int diff) {
      if (node == null) {
        return add(val, diff);
      }
      Node p, n;
      if (node.diff == diff) {
        if (node.val == val) {
          node.addOne();
          return node;
        } else if (node.val < val) {
          p = node;
          n = node.next;
        } else {
          p = node.prev;
          n = node;
        }
      } else if (node.diff < diff) {
        p = node;
        n = node.next;
        while (n != tail && (n.diff < diff || n.diff == diff && n.val < val)) {
          p = n;
          n = n.next;
        }
        if (n != tail && n.val == val) {
          n.addOne();
          return n;
        }
      } else {
        p = node.prev;
        n = node;
        while (p != head && (p.diff > diff || p.diff == diff && p.val > val)) {
          n = p;
          p = p.prev;
        }
        if (p != head && p.val == val) {
          p.addOne();
          return p;
        }
      }
      return add(p, n, val, diff);
    }

    public void print() {
      Node p = head.next;
      System.out.println("head");
      while (p != tail) {
        System.out.println("val: " + p.val + ", diff: " + p.diff + ", nums: " + p.nums);
        p = p.next;
      };
      System.out.println("tail");
    }
  }

  private class Node {
    public int val;
    public int diff;
    public int nums;
    public Node next;
    public Node prev;

    public Node() {
      this.next = null;
      this.prev = null;
    }

    public Node(int val, int diff) {
      this.val = val;
      this.diff = diff;
      this.nums = 1;
      this.next = null;
      this.prev = null;
    }

    public void addOne() {
      ++this.nums;
    }
  }

  public List<Integer> findClosestElements(int[] arr, int k, int x) {
    Tree tree = new Tree();
    Node node = null;
    for (int i = 0, len = arr.length; i < len; ++i) {
      node = tree.add(node, arr[i], Math.abs(x - arr[i]));
    }
    List<Integer> res = new ArrayList<Integer>();
    node = tree.head.next;
    while (k > 0) {
      int val = node.val;
      int nums = node.nums < k ? node.nums : k;
      k -= nums;
      for (int i=0; i<nums; ++i) {
        res.add(val);
      }
      node = node.next;
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