public class Solution2{
  public int findNumberOfLIS(int[] nums){
    int len = nums.length;
    int longest = 0;
    int num = 0;
    int[] longestFromI = new int[len];
    int[] numFromI = new int[len];
    for(int start = len - 1; start > -1; --start){
      int longestFromStart = 1;
      int numFromStart = 1;
      for(int end = start + 1; end < len; ++end){
        if(nums[start] < nums[end]){
          if(longestFromStart < 1 + longestFromI[end]){
            longestFromStart = 1 + longestFromI[end];
            numFromStart = numFromI[end];
          }else if(longestFromStart == 1 + longestFromI[end]){
            numFromStart += numFromI[end];
          }
        }
      }
      if(longest < longestFromStart){
        longest = longestFromStart;
        num = numFromStart;
      }else if(longest == longestFromStart){
        num += numFromStart;
      }
      longestFromI[start] = longestFromStart;
      numFromI[start] = numFromStart;
    }
    return num;
  }

  public static void main(String[] args){
    Solution2 s = new Solution2();
    int[] nums1 = {1, 3, 5, 4, 7};
    System.out.println(s.findNumberOfLIS(nums1));
    int[] nums2 = {2, 2, 2};
    System.out.println(s.findNumberOfLIS(nums2));
    int[] nums3 = {2};
    System.out.println(s.findNumberOfLIS(nums3));
  }
}
