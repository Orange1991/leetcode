class Solution {
  public int maximumSwap(int num) {
    if (num < 10) {
      return num;
    }
    String s = String.valueOf(num);
    char[] chars = s.toCharArray();
    for (int i=0, len=chars.length; i<len-1; ++i) {
      char max = chars[i];
      int maxIndex = i;
      for (int j=i+1; j<len; ++j) {
        if (chars[j] >= max) {
          max = chars[j];
          maxIndex = j;
        }
      }
      // found a bigger char
      if (max != chars[i]) {
        chars[maxIndex] = chars[i];
        chars[i] = max;
        break;
      }
    }
    return Integer.parseInt(String.valueOf(chars));
  }

  public static void main(String[] args) {
    Solution s = new Solution();
    System.out.println(s.maximumSwap(9999));
    System.out.println(s.maximumSwap(2736));
    System.out.println(s.maximumSwap(9973));
    System.out.println(s.maximumSwap(9979));
    System.out.println(s.maximumSwap(1));
    System.out.println(s.maximumSwap(1993));
  }
}