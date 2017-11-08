class Solution {
  public int[] constructArray(int n, int k) {
    int bigNumCount = k / 2;
    int smallNumCount = n - bigNumCount;
    int[] res = new int[n];
    int cur = 0;
    int smallIndex = 0;
    int bigIndex = 0;
    if (bigNumCount > 0 && k % 2 == 0) {
      res[cur++] = n;
      ++bigIndex;
    }
    while (bigIndex < bigNumCount) {
      res[cur++] = ++smallIndex;
      res[cur++] = n - bigIndex++;
    }
    while (smallIndex < smallNumCount) {
      res[cur++] = ++smallIndex;
    }
    return res;
  }

  private static void print(int[] a) {
    for (int i=0, len=a.length; i<len; ++i) {
      System.out.print(a[i] + ", ");
    }
    System.out.println("");
  }

  private static void test(int n, int k) {
    System.out.println("n = " + n + ", k = " + k);
    int[] a = new Solution().constructArray(n, k);
    for (int i=0, len=a.length; i<len; ++i) {
      System.out.print(a[i] + ", ");
    }
    System.out.println("");
  }

  public static void main(String[] args) {
    test(3, 2);
    test(3, 1);
    test(10, 1);
    test(10, 2);
    test(10, 3);
    test(10, 4);
    test(10, 5);
    test(10, 6);
    test(10, 7);
    test(10, 8);
    test(10, 9);
  }
}