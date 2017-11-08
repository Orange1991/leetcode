class Solution {
    public boolean checkPossibility(int[] nums) {
        boolean modified = false;
        for (int i=0, end=nums.length-1; i<end; ++i) {
            if (nums[i] > nums[i+1]) {
                if (modified) {
                    // if we have modified once, this is the second time we meet decending order
                    return false;
                } else {
                    // if this is the first time we meet decending order
                    // need to check that whether there are more than one number that bigger than nums[i+1] before i+1
                    // only need to check if nums[i-1] > nums[i+1]
                    if (i > 0 && nums[i - 1] > nums[i + 1]) {
                        // more than one number that bigger than nums[i+1]
                        modified = true;
                        nums[i + 1] = nums[i];
                    }
                    if (!modified) {
                        // has not modified, we would like to set nums[i] as the smaller nums[i + 1]
                        // [3, 2, 2, 4] -> [2, 2, 2, 4]
                        modified = true;
                        nums[i] = nums[i + 1];
                    }
                }
            }
        }
        for (int i=0, len=nums.length; i<len; ++i) {
            System.out.print(nums[i] + ",");
        }
        return true;
    }

    public static void main(String[] args) {
        Solution s = new Solution();
        int[] x = {3,4,2,3};
        System.out.println(s.checkPossibility(x));
    }
}