#Leetcode 260 Single Number III 仅出现一次的数字
##原题地址
https://leetcode.com/problems/single-number-iii/

##题目描述
Given an array of numbers nums, in which exactly two elements appear only once and all the other elements appear exactly twice. Find the two elements that appear only once.
给出一个数组，其中只有两个元素仅出现一次，其余元素均出现两次。找出只出现一次的两个元素。

For example:
例如：

Given `nums = [1, 2, 1, 3, 2, 5]`, return `[3, 5]`.
给出`nums = [1, 2, 1, 3, 2, 5]`，返回`[3, 5]`。

Note:
注意：

The order of the result is not important. So in the above example, `[5, 3]` is also correct.
结果的顺序无关紧要。所以上述例子中`[5, 3]`也是正确的。

Your algorithm should run in linear runtime complexity. Could you implement it using only constant space complexity?
你的算法需要在线性时间复杂度内运行。你可以在常数空间复杂度内实现吗？要求：**时间复杂度O(n)**，**空间复杂度O(1)**。

##解题思路
这个题目是SingleNumber系列的第三题，同系列的题目请看如下博文：

> 1. [Leetcode 136 Single Number](http://blog.csdn.net/smile_watermelon/article/details/47733979)
> 2. [Leetcode 137 Single Number II](http://blog.csdn.net/smile_watermelon/article/details/47748227)
> 3. [有一个数组data[n-1]存储了1~n中的n-1个数，问data中缺少的数字是多少【每日一题】](http://blog.csdn.net/smile_watermelon/article/details/45194901)
> 4. [Leetcode Single Number 扩展](http://blog.csdn.net/smile_watermelon/article/details/47749857)

具体说来，这个题是136题的引申。我们所要考虑的是，如何把这个问题转化为136题中的问题。如果我们简单描述这个题的话，数组是2n+x+y，其中2n是值出现两次的数字，x和y是只出现一次的两个数字，那么我们的问题就是如何将数组分成两部分即2a+x和2b+y其中a+b=n。

网上大神们的思路还是很赞的，对于两个不同的数x和y，求异或x^y=z的结果一定不为0，那么我们根据z即可把x和y分开，同时，我们可以根据z把重复出现2次的n个数也分到两组里，而且一定是成对分开的。这样分开后，就会出现2a+x和2b+y两组数。

##算法描述
> 1. 求z=x^y
> 2. 根据z把所有的数分为两组numsA[], numsB[]
> 3. 对numsA[]循环异或求得目标x，对numsB[]循环异或求得目标y

在实际求解中，不必使用numsA和numsB来存储分组结果，直接求异或操作即可，因此只使用常数空间，空间复杂度为O(1)满足要求，时间上需要遍历数组两遍，时间复杂度O(n)也满足要求。

###**1. z=x^y**

对于x^y，我们无法直接求得，因为我们不知道x和y到底是什么（知道的话还求啥）。但是由于源数据中除xy外成对出现，因此可以把所有数字都求异或，由于a^a=0，因此2n个重复的数异或结果为n个0，然后n个0异或结果还是0；再有0^a=a，因此(2n个数求异或)^x^y=(n个0求异或)^x^y==0^x^y=x^y。所以，我们把**所有的数字都循环求异或**即可得到z=x^y。

###**2. 分组**

上一步得到z之后，如何根据z把所有数字分开呢？由于z是x和y异或所得，所以z中任意一个为1的二进制位都可以把x和y区分开，因为z中为1的二进制位意味者x和y的对应位上一个为0一个为1，我们可以跟据求逻辑与的结果来把x和y区分开。举例：

    假设x=0x1，y=0x11
    x --- 0x1  --- 00000000 00000000 00000000 00000001
    y --- 0x11 --- 00000000 00000000 00000000 00001011
    z --- 0x10 --- 00000000 00000000 00000000 00001010

    假设我们取z中最后一个为1的位，既倒数第2位，code=2，则
      x    --- 0x1  --- 00000000 00000000 00000000 00000001
      y    --- 0x11 --- 00000000 00000000 00000000 00001011
     code  --- 0x2  --- 00000000 00000000 00000000 00000010
    &操作  ----------------------------------------------------------- 结果
    x&code --- 0x0  --- 00000000 00000000 00000000 00000000 --- 0 -> false
    y&code --- 0x0  --- 00000000 00000000 00000000 00000010 --- 2 -> false  

当然，我们用z中任意一个为1的二进制位都可以把x和y区分开，但是在易操作性上来说，使用最后一个1比较容易一些。

**先使用z生成掩码code，然后将源数组中的每一个数字都与code求逻辑与，如果结果为真则放入numsA[]，否则放入numsB[]**，这样就把源数据分为两个数组了，numsA[]中为2a+x，nums[]中为2b+y。

###**3. 求x和y**

接下来就是 [Leetcode 136 Single Number](http://blog.csdn.net/smile_watermelon/article/details/47733979) 中的问题了，**对numsA[]循环求异或得到x，对numsB[]循环求异或得到y**

##代码
```
/**
 * 找出仅出现一次的两个数字
 * @param nums 数组，其中只有两个元素仅出现一次，其余元素均出现两次
 * @param numsSize 数组大小
 * @param returnSize 返回数组大小
 * @return 仅出现一次的两个数字
 */
int* singleNumber(int* nums, int numsSize, int* returnSize) {
    int* ret = (int*)malloc(sizeof(int) * 2);
    *returnSize = 2;
    
    // a: 目标结果a
    // b: 目标结果b
    // tmp: a^b的结果
    // one: a和b最低的不相同的位
    int tmp = 0, a = 0, b = 0, i, one = 1;
    for (i = 0; i < numsSize; ++i) // 计算a^b
        tmp ^= *(nums + i);
        one <<= 1;
        tmp >>= 1;
    }
    // 按a和b最低的不相同的位把所有数据分为两组
    // a和b分别分在两个组里，问题转化为两个2n+1的问题
    // 两组分别异或即可得到两个目标结果
    for (i = 0; i < numsSize; ++i) 
        if (one & *(nums + i))
            a ^= *(nums + i);
        else
            b ^= *(nums + i);
    *ret = a;
    *(ret + 1) = b;
    return ret;
}
```

##测试数据

    [1,2,1,3,5,2] : [3,5]

##博文地址
http://blog.csdn.net/smile_watermelon/article/details/47750249

---
2015/8/18
