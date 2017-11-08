
public class Solution {
  public int repeatedStringMatch(String A, String B) {
    StringBuilder sb = new StringBuilder(A);
    int lenA = A.length();
    int lenB = B.length();
    int times = 1;
    if (lenA >= lenB) {
        sb.append(A);
    } else {
      while (sb.length() <= lenB) {
        sb.append(A);
      }
    }
    String str = sb.toString();
    int index = str.indexOf(B);
    if (index == -1) {
      return -1;
    } else {
      int end = index + lenB;
      return end / lenA + ((end % lenA == 0) ? 0 : 1);
    }
  }

  private void test(String A, String B) {
    System.out.println(A + ", " + B + ", " + repeatedStringMatch(A, B));
  }

  public static void main(String[] args) {
    Solution s = new Solution();
    s.test("abcd", "abcd");
    s.test("abcd", "cdabcdab");
    s.test("a", "aa");
    s.test("abababaaba", "aabaaba");
  }
}