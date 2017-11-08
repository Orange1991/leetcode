public class Solution {
  private int longest;
  private int[] subLongest;
  private int[] subLongestNums;

  public int findNumberOfLIS(int[] nums) {
    int len = nums.length;
    longest = 0;
    this.subLongest = new int[len];
    this.subLongestNums = new int[len];
    findNumberOfLIS(nums, 0);
    int num = 0;
    for (int i=0; i<len; ++i) {
      if (subLongest[i] == longest) {
        num += subLongestNums[i];
      }
    }
    return num;
  }

  private int findNumberOfLIS(int[] nums, int start) {
    int end = nums.length;
    if (start >= end) {
      return 0;
    }
    if (subLongest[start] != 0) {
      return subLongest[start];
    }

    int subLongestFromStart = 1;
    int subLongestNumsFromStart = 1;
    for (int i=start+1; i<end; ++i) {
      int subLongestFromI = findNumberOfLIS(nums, i);
      if (nums[start] < nums[i]) {
        if (subLongestFromStart < 1 + subLongestFromI) {
          subLongestFromStart = 1 + subLongestFromI;
          subLongestNumsFromStart = subLongestNums[i];
        } else if (subLongestFromStart == 1 + subLongestFromI) {
          subLongestNumsFromStart += subLongestNums[i];
        }
      }
    }
    if (subLongestFromStart > longest) {
      longest = subLongestFromStart;
    }
    subLongest[start] = subLongestFromStart;
    subLongestNums[start] = subLongestNumsFromStart;

    return subLongestFromStart;
  }

  public static void main(String[] args) {
    Solution s = new Solution();
    int[] nums1 = {1,3,5,4,7};
    System.out.println(s.findNumberOfLIS(nums1));
    int[] nums2 = {2,2,2};
    System.out.println(s.findNumberOfLIS(nums2));
    int[] nums3 = {2};
    System.out.println(s.findNumberOfLIS(nums3));
  }
}
