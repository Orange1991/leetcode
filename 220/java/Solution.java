import java.util.SortedSet;
import java.util.TreeSet;

public class Solution {
    public boolean containsNearbyAlmostDuplicate(int[] nums, int k, int t) {
        if (nums.length < 2 || k <= 0 || t < 0) return false;
        SortedSet<Long> set = new TreeSet<Long>();
        for (int i = 0; i < nums.length; ++i) {
            SortedSet<Long> sub = set.subSet((long)nums[i] - t, (long)nums[i] + t + 1);
            if (!sub.isEmpty()) return true;
            if (i >= k) set.remove((long)nums[i - k]);
            set.add((long)nums[i]);
        }
        return false;
    }

    public void test(int[] nums, int k, int t) {
        if (nums.length < 1) return;
        System.out.format("[");
        for (int i = 0; i < nums.length - 1; ++i)
            System.out.format("%d,", nums[i]);
        System.out.format("%d], k=%d, t=%d, ", nums[nums.length - 1], k, t);
        if (new Solution().containsNearbyAlmostDuplicate(nums, k, t))
            System.out.format("there have nearby almost duplicate(s)\n");
        else
            System.out.format("there have no nearby almost duplicate\n");
    }

    public static void main(String[] args) {
        int nums[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
        Solution s = new Solution();
        s.test(nums, 3, 0);
        s.test(nums, 3, 1);
        nums = new int[] {-1, -1};        
        s.test(nums, 1, 0);
        s.test(nums, 1, -1);
        nums = new int[] {-1, 2147483647};        
        s.test(nums, 1, 2147483647);
        nums = new int[] {1, 2};        
        s.test(nums, 0, 1);
    }
}
