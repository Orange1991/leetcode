#Leetcode 152 Maximum Product Subarray 子数组最大乘积

##原题地址
https://leetcode.com/problems/maximum-product-subarray/

##题目描述
Find the contiguous subarray within an array (containing at least one number) which has the largest product.
在数组（至少包含一个元素）中找到一个连续的子数组，使得该子数组元素的乘积最大。

For example, given the array `[2,3,-2,4]`,
例如，给出数组`[2,3,-2,4]`

the contiguous subarray `[2,3]` has the largest product = `6`
其连续的子数组`[2,3]`有最大的乘积`6`

##解题思路
题中给出的提示是动态规划，我们来看该问题如何拆分为子问题。

由于所有的元素都是整数，我们观察可以发现，元素基本上可以分为三类：`正数`/`负数`/`0`，针对于这三类元素，有以下几条一定成立的规律：
> 1. 任何数乘以0之后乘积都为0
> 2. 正数乘以负数之后乘积变为负数
> 3. 负数乘以负数之后乘积变为正数

通过上述第一条规律，如果我们的最大连续数组中包含了一个0元素，则其乘积将永远为0，不可能再变大，因此我们尝试**将数组以0分割为不包含0的多个子数组**，然后求得所有不包含0的子数组的最大连续元素乘积，其中的最大值就是原始数组的最大连续元素乘积。

通过上述第二条、第三条规律我们可以总结出，如果连续元素中包含**偶数个负数**的话，其乘积为正数，此时最大乘积就是所有元素的乘积；如果连续元素中包含**奇数个负数**（假设为n），则其最大乘积只可能包含其中的n-1个负数。我们还可以得知，当子数组中有奇数个负数时，最大乘积要么是**第一个负数之后的所有数的乘积**，要么是**最后一个负数之前的所有数的乘积**（去掉一个负数之后剩余所有元素的乘积是正数）。

除了以上提到的，还有一些边界情况需要处理，详见算法和代码。

##算法描述
> 1. max初始化为数组中的最大元素值（为了防止最终结果应该为0时出现错误，因为在后面的处理中把所有的0元素都删去了，如[-1,0,-2]）
> 2. 将数组以0分割为多个子数组，处理每个子数组，执行3-5步骤，更新max
> 3. 如果子数组只有一个元素，则该元素有可能为最大乘积，与max比较并更新max
> 4. 计算子数组中负数的个数，如果负数个数为偶数个，则将子数组中所有元素相乘，与max比较并更新max
> 5. 如果负数个数为奇数个，则最大值的后选值有两个：第一个负数之后的所有元素的乘积和最后一个负数之前的所有元素的乘积，将二者分别与max比较并更新max

##代码 c

```
/** 求最大子数组乘积 */
int maxProduct(int* nums, int numsSize) {   
    int subHead = 0, subTail = 0, max = *nums, index = 0, negNums = 0, product = 0;
    int start = 0, end = 0;

    /* 初始化最大值为数组中的最大元素 */
    for (index = 1; index < numsSize; ++index)
        if (max < *(nums + index)) max = *(nums + index);

    /* 将数组处理成不包含0的多个子数组
     * 子数组以subHead（包含）开始，以subTail（不包含）结尾 */
    while (subHead < numsSize) {
        // 略过当前子数组首部的0
        while (subHead < numsSize && *(nums + subHead) == 0) ++subHead;
        if (subHead == numsSize) break; // 如果没有下一个子数组，则处理结束
        subTail = subHead + 1; // 初始化subTail
        // 继续扩展子数组，直到数组结尾或者某一个元素为0
        while (subTail < numsSize && *(nums + subTail) != 0) ++subTail;

        // 至此，可以保证subHead和subTail之间的元素全都不为0

        /* 如果当前子数组仅有一个元素，则最大乘积只可能是其唯一的元素 */
        if (subTail == subHead + 1) {
            if (max < *(nums + subHead)) max = *(nums + subHead);
            subHead = subTail + 1;
            continue; // 当前子数组处理结束，继续下一个子数组的处理
        }

        /* 统计子数组中负数的个数 */
        negNums = 0;
        for (index = subHead; index < subTail; ++index)
            if (*(nums + index) < 0) ++negNums;
        
        /* 求最大乘积 */
        if (negNums & 1) { // 如果子数组中负数的个数为奇数
                           // 最大乘积是第一个负数元素之后的所有元素的乘积
                           // 或者最后一个负数元素之前的所有元素的乘积

            /* 求第一个负数元素之后的所有元素的乘积 */
            start = subHead;
            end = subTail;
            for (; start < subTail; ++start) // 找到第一个负数元素
                if (*(nums + start) < 0) break;
            ++start;
            if (start < end) { // 第一个负数元素不是最后一个元素
                product = 1;
                for (index = start; index < end; ++index) 
                    product *= *(nums + index);
                if (max < product) max = product;
            }

            /* 求最后一个负数元素之前的所有元素的乘积 */
            start = subHead;
            end = subTail;
            for (; end > start; --end) // 找到最后一个负数元素
                if (*(nums + end - 1) < 0) break;
            --end;
            if (end > start) { // 最后一个负数元素不是第一个元素
                product = 1;
                for (index = start; index < end; ++index) 
                    product *= *(nums + index);
                if (max < product) max = product;
            }
        } else { // 如果子数组中负数的个数为偶数，则最大乘积是所有元素的乘积
            product = 1;
            for (index = subHead; index < subTail; ++index)
                product *= *(nums + index);
            if (max < product) max = product;
        }

        subHead = subTail + 1;
    }

    return max;
}
```
> 完整代码[https://github.com/Orange1991/leetcode/blob/master/152/c/main.c](https://github.com/Orange1991/leetcode/blob/master/152/c/main.c)

##运行情况
| Language | Status | Time |
| :------- | :----- | :--- |
| c        | Accept | 4ms  |


##测试数据

    [-2] : -2
    [1, 0, 0, 0] : 1
    [0, -2, -3] : 6
    [5, 6, -3, 0] : 30
    [0, -2, 0, -2, -3, 4, 0, 5, 6, -3] : 30
    [0, -2, 0, -2, -3, 4, 0, 5, 6, -3, 0, -2, 2, 3, 4, -3, -1] : 144
    [2, -5, -2, -4, 3] : 24
    [-2, 0, -1] : 0

##博文地址
http://blog.csdn.net/smile_watermelon/article/details/47256659

---
2015/8/3
