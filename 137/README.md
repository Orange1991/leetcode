#Leetcode 137 Single Number II 仅出现一次的数字
##原题地址
https://leetcode.com/problems/single-number-ii/

##题目描述
Given an array of integers, every element appears three times except for one. Find that single one.
给出一个整数数组，除了某个元素外所有元素都出现三次。找出仅出现一次的数字。

Note:
注意：

Your algorithm should have a linear runtime complexity. Could you implement it without using extra memory?
你的算法需要在线性时间复杂度内运行。你可以在常数空间复杂度内实现吗？要求：**时间复杂度O(n)**，**空间复杂度O(1)**。

**Tags** `Bit Manipulation`

##解题思路
Single Number系列的第二题，第一题请看 [Leetcode 136 Single Number 仅出现一次的数字](http://blog.csdn.net/smile_watermelon/article/details/47733979) 。

实际上136题是137题都是一个特例，更抽象的题目是，**有一个数组，其中有一个元素出现了x次，其余所有元素都出现了y次(x<y)，找出这个出现了x次的元素**。关于这个问题，我们在另一篇文章里进行讨论。这里我们只讨论137这个题目。

由于除去目标元素target之外，所有元素都出现3次，假设出现3次的元素有n个，这样的话假如我们统计所有元素的某一位（比如最后一位），其一共有3n+1个二进制位。因为对与同一个元素来说，其所有的二进制位一定是相同的，所以对这些元素的某一位来说一定是以3个1或3个0为单位出现的，即3n+1个二进制位中一定是3x个1和3y个0，其中x+y=n，再外加一个target对应的二进制位（1或0都有可能）。综上所述，我们可以**统计所有数字每一位上1的个数，对3取模，如果为1就说明target对应位为1，否则为0**。

下面问题就是如何统计每一位上1的个数，一个比较好的方法就是采用位运算来处理，当个数满3时就清零（当然这是参考的网上大神们的思路）。

我们用三个整数one，two， three的二进制位来分别表示32位整数某一位上1出现次数是否为1次、2次、3次，举例，假如：

    one = 1 --- 0x00000001 --- 00000000 00000000 00000000 00000001
    则表示当前统计情况下最低位出现1的次数为1次
    two = 3 --- 0x00000003 --- 00000000 00000000 00000000 00000011
    则表示当前统计情况下最低位出现1的次数为2次，倒数第二位出现1的次数为2次
    three = 4 --- 0x00000004 --- 00000000 00000000 00000000 00000100
    则表示当前统计情况下最倒数第三位出现1的次数为3次
    
大神们说one two three可以称之为掩码。

有了如上逻辑后，我们可以遍历所有的数字，对于每个数字，操作其所有的二进制位，来更新one two three三个数字。当我们遍历完所有数字时，由于除去target只出现一次外，其余元素都是以3为单位出现的，所以可以知道one中存储的二进制位代表的数字就是target。

对于实际代码中，one two three三者的更新，有以下两个版本，版本一是我自己想出来的，更通用，而且更接近于上面提出的更一般的问题的解决思路（代码一）；版本二是网上大神们的代码，只能说更巧妙一些，但是实际上都一样（代码二）。详细请看代码部分中的注释。

##代码

###代码一
```
int singleNumber(int* nums, int numsSize) {
    int one = 0, two = 0, three = 0, tmp;
    while (numsSize) {
        // 获取当前要统计的数字
        tmp = *(nums + --numsSize); 
        // 之前已经出现2次1的位且当前数字中又为1，则更新为出现3次
        three = two & tmp; 
        // 清空上一步操作中出现3次1的位
        two &= ~three;  // 在two中清空
        tmp &= ~three;  // 当前数字也要清空，以防重复统计
        // 之前已经出现1次1的位且当前数字中又为1，则更新为出现2次
        two |= one & tmp;
        // 之前没有出现且当前数字中为1，更新为出现1次
        // 或者之前出现次数为1次，且当前数字中没有出现，仍旧为1次
        one ^= tmp;
    }
    return one;
}
```
其中需要注意的主要有两点，**第一是使用tmp更新three之后，需要对two和tmp进行满3次的位的清零，否则会有重复统计的情况出现**；**第二是two和one的更新方式非常巧妙**，加入one和tmp某一位都为1，我们可以直到two的对应位应该置1，one的对应位应该置0，而如果one和tmp不同时为1，则two应该为0，one应该为1，&操作和^操作的结果刚好与上述规则契合。

代码二中也有类似情况。

> 完整代码 [https://github.com/Orange1991/leetcode/blob/master/137/c/solution2.c](https://github.com/Orange1991/leetcode/blob/master/137/c/solution2.c)

###代码二
```
int singleNumber(int* nums, int numsSize) {
    int one = 0, two = 0, three = 0;
    while (numsSize) {
        // 之前已经出现1次1的位且当前数字中又为1，则更新为出现2次
        two |= one & *(nums + --numsSize);
        // 之前没有出现且当前数字中为1，更新为出现1次
        // 或者之前出现次数为1次，且当前数字中没有出现，仍旧为1次
        one ^= *(nums + numsSize);
        // 既出现了一次又出现了两次的位即出现了3次
        three = two & one;
        // 清空出现了三次的位
        two &= ~three;
        one &= ~three;
    }
    return one;
}
```

> 完整代码 [https://github.com/Orange1991/leetcode/blob/master/137/c/main.c](https://github.com/Orange1991/leetcode/blob/master/137/c/main.c)

---
2015/8/18
