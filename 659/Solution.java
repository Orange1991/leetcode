class Solution {
  public boolean isPossible(int[] nums) {
    int pre = Integer.MIN_VALUE, p1 = 0, p2 = 0, p3 = 0;
    int cur, c1, c2, c3, count;
    int len = nums.length;
    for (int i = 0; i < len; pre = cur, p1 = c1, p2 = c2, p3 = c3) {
      // count numbers of cur
      for (cur = nums[i], count = 0; i < len && cur == nums[i]; ++count, ++i);

      if (cur != pre + 1) {
        if (p1 != 0 || p2 != 0) {
          // [1, 2, 4, 5, 6] -> when meet 4, it's not ascending number of 2 and p2 = 1, it's not ended
          return false;
        } else {
          c1 = count;
          c2 = 0;
          c3 = 0;
        }
      } else {
        if (count < p1 + p2) {
          // [1, 2, 2, 3] -> when meet 3, p1 = 1, p2 = 1, but we only have one 3
          return false;
        }
        c2 = p1;
        c3 = p2 + Math.min(p3, count - p1 - p2);
        // c1 = count - c2 - c3; this is same with below statement
        c1 = Math.max(count - p1 - p2 - p3, 0);
      }
    }
    return p1 == 0 && p2 == 0;
  }
}