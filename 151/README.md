#Leetcode 151 Reverse Words in a String

##原题地址
https://leetcode.com/problems/reverse-words-in-a-string/

##题目描述
Given an input string, reverse the string word by word.
给出一个字符串，将其中的字符串按单词顺序翻转．

For example,
例如，

Given s = `"the sky is blue"`,
给出 s = `"the sky is blue"`,

return `"blue is sky the"`.
返回 `"blue is sky the"`.

**Clarification:**
**说明：**

> - What constitutes a word?
>   单词由什么构成？
>   A sequence of non-space characters constitutes a word.
>   一个不包含空格的字符序列构成一个单词．
>
> - Could the input string contain leading or trailing spaces?
>   输入字符串的首尾是否会包含空格？
>   Yes. However, your reversed string should not contain leading or trailing spaces.
>   是．然而，在你逆置处理之后的字符串首尾不能包含空格．
>
> - How about multiple spaces between two words?
>   那两个单词之间包含多个空格的情况呢？
>   Reduce them to a single space in the reversed string.
>   在逆置处理时化简为一个空格．

##解题思路
在空间复杂度O(1)时间复杂度O(n)的要求下，基本思路就是先将整个字符串逆置，此时得到的字符串中每个单词的字符顺序是颠倒的，因此再进行一次处理将各单词内部字符进行逆置，最后在`说明`中还提到可能存在多余的空格，再进行一次处理，删去多余的空格．

需要注意的是，去除多余空格的操作既可以在逆置操作之前进行，也可以在逆置操作之后进行．

##算法描述
> 1. 字符串逆置
> 2. 单词逆置
> 3. 去除多余空格

##代码 c

```
void reverseWords(char *s) {
    int len = 0, formmer = 0, latter = 0;
    char *tmp = s, tmpChar;
    while (*tmp++ != '\0') ++len;

    /* 字符串逆置 */
    latter = len - 1;
    while (formmer < latter) {
        tmpChar = *(s + formmer);
        *(s + formmer) = *(s + latter);
        *(s + latter) = tmpChar;
        ++formmer;
        --latter;
    }

    /* 单词逆置 */
    formmer = 0;
    int end = 0;
    while (formmer < len) {
        end = formmer;
        while (end < len - 1 && *(s + end + 1) != ' ') ++end;
        latter = end;
        while (formmer < latter) {
            tmpChar = *(s + formmer);
            *(s + formmer) = *(s + latter);
            *(s + latter) = tmpChar;
            ++formmer;
            --latter;
        }
        formmer = end + 2;
    }

    /* 去除空格 */
    formmer = 0;
    latter = 0;
    while (latter < len) {
        while (latter < len && *(s + latter) == ' ') ++latter;
        while (latter < len && *(s + latter) != ' ') 
            *(s + formmer++) = *(s + latter++);
        *(s + formmer++) = ' ';
    }
    *(s + --formmer) = '\0';
    if (*(s + --formmer) == ' ') *(s + formmer) = '\0';
}
```
> 完整代码[https://github.com/Orange1991/leetcode/blob/master/151/c/main.c](https://github.com/Orange1991/leetcode/blob/master/151/c/main.c)

##运行情况
| Language | Status | Time |
| :------- | :----- | :--- |
| c        | Accept | 0ms  |
   　

##测试数据
    输入："the sky is blue"
    输出："blue is sky the"

    输入："  the  sky  is  blue   "
    输出："blue is sky the"

##博文地址
http://blog.csdn.net/smile_watermelon/article/details/47219855

---
2015/8/2
