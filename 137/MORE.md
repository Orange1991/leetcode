#Leetcode Single Number 扩展
##问题描述
[Leetcode 137 Single Number II 仅出现一次的数字](http://blog.csdn.net/smile_watermelon/article/details/47748227) 中提出了一个更一般的问题：**有一个数组，其中有一个元素出现了x次，其余所有元素都出现了y次(x < y)，找出这个出现了x次的元素**，要求**时间复杂度O(n)，空间复杂度O(1)**。

##解题思路
实际上，[Leetcode 136 Single Number 仅出现一次的数字](http://blog.csdn.net/smile_watermelon/article/details/47733979) 和 [Leetcode 137 Single Number II 仅出现一次的数字](http://blog.csdn.net/smile_watermelon/article/details/47748227) 都是这个一般问题的特例。136是最特殊的一个例子，我们从中可以找到的规律不是很明显；在137中我们已经给出使用one two three作为掩码来统计每一位上1的出现次数的方法，对于我们解决此题很有启发。出现x次的情况下，我们用一个大小为x的动态数组来存储各掩码即可，然后在每次获取到一个数字后，循环更新所有的掩码，最终第y个掩码所代表的数字就是只出现了y次的元素。

为了统一处理，我们掩码数组大小设为x+1，用times[x+1]来表示，其中times[i]表示出现i次的位。

具体逻辑请看后面的代码。

##代码
```
/**
 * 返回特殊的数字
 * 特殊数字仅出现y次，其余数字均出现x次，x>0，y>0，x>y
 * @param nums 数字集合
 * @param numsSize 集合大小
 * @param x 普通数字出现次数
 * @param y 特殊数字出现次数
 */
int specialNumber(int *nums, int numsSize, int x, int y) {
    int num, change, i;
    int* times = (int*)malloc(sizeof(int) * (x + 1));
    for (i = 1; i <= x; ++i) *(times + i) = 0;
    while (numsSize) {
        *times = ~0; // 置全1，保证*(times+1)结果的正确性
        // 获取当前要统计的数字
        num = *(nums + --numsSize); 
        for (i = x; i > 0; --i) { // 更新每一位掩码
            change = *(times + i - 1) & num; // 获得更新位
            *(times + i) |= change;  // 更新
            num &= ~change;          // 清空更新位
            *(times + i - 1) &= ~change;
        }
    }
    num = *(times + y);
    free(times);
    return num;
}
```
有了这个方法以后，我们在 [Leetcode 136 Single Number 仅出现一次的数字](http://blog.csdn.net/smile_watermelon/article/details/47733979) 中的方法就可以如下实现：
```
/**
 * 返回仅出现一次的数字
 * 特殊数字仅出现1次，其余数字均出现2次
 * @param nums 数字集合
 * @param numsSize 集合大小
 */
int singleNumber(int* nums, int numsSize) {
    int specialNumber(int*, int, int, int);
    return specialNumber(nums, numsSize, 2, 1);
}
```
同样， 在[Leetcode 137 Single Number II 仅出现一次的数字](http://blog.csdn.net/smile_watermelon/article/details/47748227)  中的方法就可以如下实现：
```
/**
 * 返回仅出现一次的数字
 * 特殊数字仅出现1次，其余数字均出现3次
 * @param nums 数字集合
 * @param numsSize 集合大小
 */
int singleNumber(int* nums, int numsSize) {
    int specialNumber(int*, int, int, int);
    return specialNumber(nums, numsSize, 3, 1);
}
```
在leetcode上进行了验证，136和137均Accept。

> 完整代码 [https://github.com/Orange1991/leetcode/blob/master/137/c/more.c](https://github.com/Orange1991/leetcode/blob/master/137/c/more.c)

##测试数据

    [1,2,3,4,1,2,3,1,2,3] : each number appears 3 times expect for the special one appears 1 times, the special number is 4
    [1,1,2,2,3,4,4,5,5,66,66] : each number appears 2 times expect for the special one appears 1 times, the special number is 3
    [1,1,1,3,3,3,44,44,55,55,55,111,111,111] : each number appears 3 times expect for the special one appears 2 times, the special number is 44
    [1] : each number appears 3 times expect for the special one appears 1 times, the special number is 1

---
2015/8/18

