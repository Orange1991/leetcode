public class S2 {
  public int countSubstrings(String s) {
    int len = s.length();
    char[] chars = new char[len];
    for (int i = 0; i < len; ++i) {
      chars[i] = s.charAt(i);
    }

    int count = 0;
    for (int i = 0; i < len; ++i) {
      int l = i;
      int r = i;
      while (l > -1 && r < len && chars[l--] == chars[r++]) {
        ++count;
      }
      if (i != len - 1) {
        l = i;
        r = i + 1;
        while (l > -1 && r < len && chars[l--] == chars[r++]) {
          ++count;
        }
      }
    }
    return count;
  }

  public static void main(String[] args) {
    Solution s = new Solution();
    System.out.println(s.countSubstrings("aaa"));
    System.out.println(s.countSubstrings("abc"));
  }
}