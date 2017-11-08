public class Solution {
  public int findLengthOfLCIS(int[] nums) {
    int len = nums.length;
    if (len == 1) {
      return 1;
    }
    int max = 0;
    int start = 0;
    int end = 1;
    while (end < len) {
      while (end < len && nums[end] > nums[end - 1]) {
        ++end;
      }
      int subLen = end - start;
      if (subLen > max) {
        max = subLen;
      }
      start = end;
      end = end + 1;
    }
    return max;
  }

  public static void main(String[] args) {
    Solution s = new Solution();
    int[] nums1 = {1,3,5,4,7};
    System.out.println(s.findLengthOfLCIS(nums1));
    int[] nums2 = {2,2,2};
    System.out.println(s.findLengthOfLCIS(nums2));
    int[] nums3 = {2};
    System.out.println(s.findLengthOfLCIS(nums3));
  }
}
