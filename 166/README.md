#Leetcode 166 Fraction to Recurring Decimal 分数化小数

##原题地址
https://leetcode.com/problems/fraction-to-recurring-decimal/

##题目描述
Given two integers representing the numerator and denominator of a fraction, return the fraction in string format.
给出两个整数，一个分子一个分母，将该分数转化为小数并返回字符串。

If the fractional part is repeating, enclose the repeating part in parentheses.
如果小数部分有循环，将其规约在括号内。

For example,
例如，

Given numerator = 1, denominator = 2, return "0.5".
给出 numerator = 1, denominator = 2, 返回 "0.5" `1/2=0.5`.

Given numerator = 2, denominator = 1, return "2".
给出 numerator = 2, denominator = 1, 返回 "2" `2/1=2`.

Given numerator = 2, denominator = 3, return "0.(6)".
给出 numerator = 2, denominator = 3, return "0.(6)" `1/3=0.(6)`.

##解题思路
解题思路比较简单，就是简单的除法运算，每次运算获取商和余数，直到商为0或者发现出现循环小数的情况。这里需要注意的有以下几点：

> 1. 符号问题，输入有可能是正数或负数，结果有正有负
> 2. -0问题，分子为0分母为负数时，结果是0而不是-0
> 3. 溢出问题，**INT_MIN**，可以使用[-1/-2147483648]和[-2147483648/-1]两组数据来验证是否解决了这个问题
> 4. 循环小数，只把循环的部分放在括号内，可以使用[1/6]验证是否解决了这个问题

**计算过程**

        0.16  
      |------
    6 / 1.00
        0
       ---- 
        1 0       <-- 被除数=10, 在dividendCache[0]中记录10.
        - 6
        ----  
          40      <-- 被除数=40, 在dividendCache[1]中记录40.
        - 36 
         ----
           40      <-- 被除数=40, dividendCache[1]中已经记录过40，因此从第1位小数开始是循环部分.
    
    第1位小数是6，从dividendCache[1]起直到dividendCache[dividendCache.size()-1]的小数是循环部分，应当返回0.1(6)。


总体来说，这个题目并不难，只是各种边界值可能搞疯你，oj的平台也有问题，同样的代码在c下过不了，说[-1/-2147483648 = 0.0000000004656612873077392578125]有错，然而cpp可以通过。另外gcc环境下使用`math.h`时，编译命令需要加入`-lm`，例如`gcc main.c -o main -lm`。

##代码cpp

```
class Solution {
public:
    const static int CACHE_SIZE = 1000;
    /**
     * 分数转换为小数
     * @param numerator 分子
     * @param denominator 分母
     * @return 字符串
     * 如果小数部分是循环小数，用括号把循环部分包括起来
     */
    string fractionToDecimal(int numerator, int denominator) {
        if (numerator == 0) return "0";
        
        bool isNegative = numerator < 0 ^ denominator < 0; // 结果是否为负数
        /* 处理为正数 */
        double doubleNumerator = fabs(numerator);
        double doubleDenominator = fabs(denominator);
        double integral = floor(doubleNumerator / doubleDenominator); // 结果的整数部分
        doubleNumerator -= doubleDenominator * integral; // 余数部分
    
        /* 计算并缓存计算结果 */
        int len = 0; // 小数部分长度
        string cache;// 小数部分缓存
        vector<double> dividendCache;
        bool isRecurring = false; // 是否是循环小数
        int recurringStart = 0; // 循环开始位
        int i = 0;
        while (doubleNumerator) { // 分子（余数）不为0时继续计算
            doubleNumerator *= 10; // 被除数乘10
            len = dividendCache.size();
            for (i = 0; i < len; ++i) // 查询是否构成循环（被除数是否已经存在过）
                if (dividendCache[i] == doubleNumerator) {
                    isRecurring = true; 
                    recurringStart = i;
                    break;
                }
            if (isRecurring) break; // 如果构成循环，结束计算
            i = (int)(floor(doubleNumerator / doubleDenominator)); // 商
            cache += '0' + i; // 记录商
            dividendCache.push_back(doubleNumerator); // 记录被除数
            doubleNumerator -= doubleDenominator * i; // 被除数取余，作为下次计算的被除数
        }
    
        /* 根据缓存数据生成返回数据 */
        /* 符号部分 */
        string ret = isNegative ? "-" : "";
        /* 整数部分 */
        string tmp;
        char c;
        if (integral == 0) ret += "0";
        else {
            while (integral) {
                c = (int)(integral - 10 * floor(integral / 10))+ '0';
                tmp = c + tmp;
                integral = floor(integral / 10);
            }
            ret += tmp;
        }
        /* 小数部分 */
        if (dividendCache.size() > 0) ret += '.';
        i = 0;
        if (isRecurring) {
            ret += cache.substr(0, recurringStart);
            ret += '(';
            ret += cache.substr(recurringStart);
            ret += ')';
        } else
            ret += cache;
    
        return ret;
    }
};
```
> 完整代码[https://github.com/Orange1991/leetcode/blob/master/166/cpp/main.cpp](https://github.com/Orange1991/leetcode/blob/master/166/cpp/main.cpp)

##测试数据

    2 / 1 = 2
    -2 / 1 = -2
    1 / 2 = 0.5
    1 / -2 = -0.5
    1 / 3 = 0.(3)
    -1 / 3 = -0.(3)
    2 / 7 = 0.(285714)
    -2 / 7 = -0.(285714)
    1 / 11 = 0.(09)
    -1 / -11 = 0.(09)
    2147483647 / 27 = 79536431.(370)
    -2147483647 / 27 = -79536431.(370)
    2147483647 / 37 = 58040098.(567)
    2147483647 / -37 = -58040098.(567)
    1000 / 10 = 100
    1000 / -10 = -100
    1001 / 10 = 100.1
    -1001 / 10 = -100.1
    -2147483648 / 1 = -2147483648
    -2147483648 / -1 = 2147483648
    1 / 214748364 = 0.00(000000465661289042462740251655654056577585848337359161441621040707904997124914069194026549138227660723878669455195477065427143370461252966751355553982241280310754777158628319049732085502639731402098131932683780538602845887105337854867197032523144157689601770377165713821223802198558308923834223016478952081795603341592860749337303449725)
    -1 / -2147483648 = 0.0000000004656612873077392578125
    1 / -2147483648 = -0.0000000004656612873077392578125
    -1 / -2147483648 = 0.0000000004656612873077392578125
    1 / 6 = 0.1(6)

##博文地址
http://blog.csdn.net/smile_watermelon/article/details/47278579

---
2015/8/4
