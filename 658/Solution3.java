import java.util.ArrayList;
import java.util.List;

public class Solution3 {
  public List<Integer> findClosestElements(int[] arr, int k, int x) {
    int len = arr.length;
    int[] diffs = new int[len];
    int minDiff = Integer.MAX_VALUE;
    int mid = 0;
    for (int i = 0; i < len; ++i) {
      int diff = Math.abs(x - arr[i]);
      diffs[i] = diff;
      if (diff > minDiff) {
        break;
      }
      if (diff < minDiff) {
        minDiff = diff;
        mid = i;
      }
      if (diff == 0) {
        break;
      }
    }
    int[] big = new int[len];
    int[] small = new int[len];
    int bigCnt = 0;
    int smallCnt = 0;
    int rest = k;

    big[bigCnt++] = arr[mid];
    --rest;

    int front = mid - 1;
    int back = mid + 1;
    while (front > -1 && back < len && rest > 0) {
      int diffFront = diffs[front];
      int diffBack = Math.abs(x - arr[back]);
      if (diffFront <= diffBack) {
        small[smallCnt++] = arr[front--];
      } else {
        big[bigCnt++] = arr[back++];
      }
      --rest;
    }
    while (front > -1 && rest > 0) {
      small[smallCnt++] = arr[front--];
      --rest;
    }
    while (back < len && rest > 0) {
      big[bigCnt++] = arr[back++];
      --rest;
    }
    List<Integer> res = new ArrayList<Integer>();
    for (int i = smallCnt - 1; i > -1; --i) {
      res.add(small[i]);
    }
    for (int i = 0; i < bigCnt; ++i) {
      res.add(big[i]);
    }
    return res;
  }

  public static void main(String[] args) {
    int[] nums = {1,2,3,4,5,1,-3};
    Solution s = new Solution();
    List<Integer> res = s.findClosestElements(nums, 4, -1);
    for (int i = 0, len = res.size(); i < len; ++i) {
      System.out.print(res.get(i) + ", ");
    }
    int[] nums2 = {1,2,3,4,5};
    res = s.findClosestElements(nums2, 4, 3);
    for (int i = 0, len = res.size(); i < len; ++i) {
      System.out.print(res.get(i) + ", ");
    }
  }
}