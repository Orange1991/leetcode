#Leetcode 241 Different Ways to Add Parentheses

##原题地址
https://leetcode.com/problems/different-ways-to-add-parentheses/

> 1. main.cpp
> 有错误，重复解，不是指结果重复，而是有些加括号的情况重复了，比如：2*3+4*5
> - 先2*3再4*5最后加法，加括号就是：((2 * 3)+(4 * 5))
> - 先4*5再2*3最后加法，加括号就是：((2 * 3)+(4 * 5))
> 实际上两者是一样的加括号方式。
> 
> 2. s2.cpp
> 使用分治法，将字符串拆分为子串，用子串的结果来构造原问题结果。
> Accept.
