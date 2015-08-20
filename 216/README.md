#Leetcode 217 Combination Sum III 组合求和

##原题地址
https://leetcode.com/problems/combination-sum-iii/

##题目描述
Find all possible combinations of k numbers that add up to a number n, given that only numbers from 1 to 9 can be used and each combination should be a unique set of numbers.
找出所有可能的和为n的k项组合，组合的项仅能从1-9中选择，且组合中数字不能重复。

Ensure that numbers within the set are sorted in ascending order.
确保集合内数字为升序。

Example 1:
例1：

Input: 
输入：

`k = 3, n = 7`

Output:
输出：

`[[1,2,4]]`

Example 2:
例2：

Input:
输入：
` k = 3, n = 9`

Output:
输出：

`[[1,2,6], [1,3,5], [2,3,4]]`

##解题思路
这个问题还是比较简单的。在求解时我们把关注点放在**给和等于n的k项组合选择第一项**上，这样，加入我们已经选择好了第一项x，剩下的问题就是给和等于n-x的k-1项组合选择第一项。另外，由于本题还有其他约束：1.不能重复；2.组合内元素升序排列；因此可以更具体的说剩下的问题是**在大于x的数中给和等于n-x的k-1组合选择第一项**，这样直到k-1为0且n-x为0时，就找到了一个可行的组合。

我们可以编写一个函数，每次都是选择组合内的某一项，并递归调用来选择下一项。需要特别说明的一点是，为了保证数字不重复，我们通常会使用一个标志数组来记录数字的使用情况，然而我们这里不用这么做。我们可以通过**在大于x的数中选择**这个约束来保证，**递归选择下一项时是在从未使用过的数字中选择的，一定不会重复，而且这样还能保证每一项添加到组合中时是以升序排列的**。

##代码

```
class Solution {
public:
    /**
     * 返回和为n的k项组合
     * 备选数字只能是1-9，且在某特定组合内数字不能重复使用
     * @param k 组合项个数
     * @param n k项的和
     * @return 所有可能的组合
     */
    vector<vector<int> > combinationSum3(int k, int n) {
        vector<int> nums;
        vector<vector<int> > ans;
        // 在(0, 9]中选择和为n的k项组合
        combinationSum(nums, 0, k, n, ans);
        return ans;
    }
private:
    /**
     * 返回和为sum的count项组合
     * 备选数字只能是1-9，且在某特定组合内数字不能重复使用
     * 每次调用的效果是给和等于sum的count项组合选择第一个数字
     * @param nums 当前组合
     * @param last 当前组合的最大数字
     * @param count 组合项个数
     * @param sum 所有项的和
     * @param ans 可行解
     */
    void combinationSum(vector<int>& nums, int last, int count, int sum, vector<vector<int> >& ans) {
        // 添加可行解
        if (sum == 0 && count == 0) { ans.push_back(nums); return; }
        
        // 以下过程为在(last, end]区间内选择和为sum的count项组合的第一个数字
        int end = sum < 9 ? sum : 9; // 如果当前sum小于9，则缩小数字选取范围
        end -= count - 1; // 尝试缩小数字选取范围，为后面的count-1个数留取选择空间
        for (int i = last + 1; i <= end; ++i) { // 在选取范围内选择一个数字
            nums.push_back(i); // 添加到组合中
            combinationSum(nums, i, count - 1, sum - i, ans); // 递归调用，选取剩余的count-1个数
            nums.pop_back(); // 弹出组合中的最后一个数，以备下次循环选择另一个备选数字
        }
    }
};
```

> 完整代码 [https://github.com/Orange1991/leetcode/blob/master/216/cpp/main.cpp](https://github.com/Orange1991/leetcode/blob/master/216/cpp/main.cpp)

##测试数据

    k = 3, n = 7, comninations = 
    [
        [1, 2, 4]
    ]
    k = 3, n = 9, comninations = 
    [
        [1, 2, 6],
        [1, 3, 5],
        [2, 3, 4]
    ]
    k = 3, n = 24, comninations = 
    [
        [7, 8, 9]
    ]
    k = 3, n = 25, comninations = 
    [
    ]
    k = 8, n = 40, comninations = 
    [
        [1, 2, 3, 4, 6, 7, 8, 9]
    ]

##博文地址
http://blog.csdn.net/smile_watermelon/article/details/47808595

---
2015/8/20
