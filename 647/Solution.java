public class Solution {
  public int countSubstrings(String s) {
    int len = s.length();
    int[][] isPalindromic = new int[len][len];
    int[] count = { 0 };
    for (int i = 0; i < len; ++i) {
      for (int j = 0, maxJ = len - i; j < maxJ; ++j) {
        countSubstrings(s, j, j + i, isPalindromic, count);
      }
    }
    return count[0];
  }

  private boolean countSubstrings(String s, int i, int j, int[][] isPalindromic, int[] count) {
    if (i > j) {
      return true;
    }
    int cache = isPalindromic[i][j];
    if (cache != 0) {
      return cache == 1;
    }
    if (i == j) {
      isPalindromic[i][j] = 1;
      ++count[0];
      return true;
    }
    if (s.charAt(i) == s.charAt(j)) {
      boolean is = countSubstrings(s, i + 1, j - 1, isPalindromic, count);
      if (is) {
        ++count[0];
      }
      isPalindromic[i][j] = is ? 1 : -1;
      return is;
    } else {
      isPalindromic[i][j] = -1;
      return false;
    }
  }

  public static void main(String[] args) {
    Solution s = new Solution();
    System.out.println(s.countSubstrings("aaa"));
    System.out.println(s.countSubstrings("abc"));
  }
}