
public class Solution {
  public int minSteps(int n) {
    if (n == 1) {
      return 0;
    } else if (n == 2) {
      return 2;
    }
    int MAX = 1000;
    int[] cache = new int[MAX + 1];
    cache[1] = 1;
    cache[2] = 2;
    return minSteps(n, cache);
  }

  private int minSteps(int n, int[] cache) {
    if (cache[n] != 0) {
      return cache[n];
    }
    int min = n;
    int lastPaste = n / 2;
    while (lastPaste > 1) {
      if (n % lastPaste == 0) {
        int step = n / lastPaste;
        step += minSteps(lastPaste, cache);
        if (step < min) {
          min = step;
        }
      }
      lastPaste--;
    }
    cache[n] = min;
    return min;
  }

  public static void main(String[] args) {
    Solution s = new Solution();
    System.out.println(s.minSteps(1));
    System.out.println(s.minSteps(2));
    System.out.println(s.minSteps(3));
    System.out.println(s.minSteps(4));
    System.out.println(s.minSteps(5));
    System.out.println(s.minSteps(6));
    System.out.println(s.minSteps(7));
    System.out.println(s.minSteps(8));
    System.out.println(s.minSteps(9));
    System.out.println(s.minSteps(10));
    System.out.println(s.minSteps(100));
  }
}
