#Leetcode 179 Largest Number 构造最大数字

##原题地址
https://leetcode.com/problems/largest-number/

##题目描述
Given a list of non negative integers, arrange them such that they form the largest number.
给出一组非负数字，对它们进行整理排列使它们构成最大的数字。

For example, given `[3, 30, 34, 5, 9]`, the largest formed number is `9534330`.
例如，给出`[3, 30, 34, 5, 9]`，可以构成的最大的数字是`9534330`。

Note: The result may be very large, so you need to return a string instead of an integer.
注意：结果可能会非常大，因此你需要返回一个字符串而不是整数。

##解题思路
一开始想这个题想得真的很复杂，直观上看起来最高位的数字越高的肯定排列越考前，例如：[9, 8, 765]按照最高位来排列就可以形成最大的数字98765。然而，在两个数字的最高位相同时情况变得复杂起来，并不能简单按次高位来判定，例如[52, 524, 526, 54, 57]。最后还是网上看了一下，答案还是很意外，如果我们无法确定两个数字排列顺序的话，我们尝试将两者按照两种顺序组合在一起，看哪个结果比较大就好了。例如，对于52和524，52+524拼在一起是52524，524+52拼在一起是52452，比较得出52524 > 52452，因此52应该排在524前面。另外，由于两个数字拼在一起之后可能会非常大，因此我们将数字转换为字符串再拼接；除了不会溢出之外，字符串的拼接也比整数的拼接要容易太多。字符串拼接在一起之后，其大小比较结果是按照字典序排序的，且其结果与整数拼接结果一致，例如"52524" > "52452"。

##算法描述

> 1. 将所有整数转化为字符串
> 2. 对所有字符串进行排序，排序规则为`如果ab > ba，a排在b的前面`
> 3. 把排好序的字符串拼接在一起

**特殊值0** 有一个特例就是，如果所有数字都是0，则其排序好之后最前面的一个也是0，所以拼接之后的字符串的第一个也是0，即"0000..."，这种情况下应当返回"0"。

##代码 cpp

```
class Solution {
public:
    /** 
     * 生成最大数字
     * @param nums 备选数字
     * @return 最大数字字符串
     */
    string largestNumber(vector<int>& nums) {   
        int len = nums.size();

        /* 数字转化为字符串 */
        vector<string> strs;
        for (int i = 0; i < len; ++i) {
            char buff[20];
            sprintf(buff, "%d", nums[i]);
            strs.push_back(buff); 
        }

        /* 排序 */
        sort(strs.begin(), strs.end(), cmp);

        /* 拼接结果 */
        string ret;
        for (int i = 0; i < len; ++i) ret += strs[i];
        
        /* 特殊值0 */
        if (ret == "" || ret[0] == '0') ret = "0";

        return ret;
    }

    /** 按照a+b和b+a的字典序判定a和b的“大小”关系 */
    static bool cmp(string a, string b) { return a + b > b + a; }
};
```
> 完整代码 [https://github.com/Orange1991/leetcode/blob/master/179/cpp/main.cpp](https://github.com/Orange1991/leetcode/blob/master/179/cpp/main.cpp)

##运行情况
| Language | Status | Time |
| :------- | :----- | :--- |
| cpp      | Accept | 8ms  |


##测试数据

    [9,98,92,8,89,5,55,5,56,567,562,545,542,52,562] : 9989289856756562562555554554252
    [3,30,34,5,9,0] : 95343300
    [2048,48] : 482048
    [2048] : 2048
    [0,0] : 0
    [8247,824] : 8248247

##博文地址
http://blog.csdn.net/smile_watermelon/article/details/47293793

---
2015/8/5
