#Leetcode 205 Isomorphic Strings 同构字符串

##原题地址
https://leetcode.com/problems/isomorphic-strings/

##题目描述
Given two strings s and t, determine if they are isomorphic.
给出两个字符串s和t，判断它们是否是同构的。

Two strings are isomorphic if the characters in s can be replaced to get t.
如果可以通过替换s中的字符来得到t，则两个字符串是同构的。

All occurrences of a character must be replaced with another character while preserving the order of characters. No two characters may map to the same character but a character may map to itself.
同一个字符只能替换成另外一个字符，且两个字符不能映射成同一个字符，但是字符可以映射为自身（也就是没有替换）。

For example,
例如，

Given，
给出
 
    s = "egg", t = "add", return true.
    s = "foo", t = "bar", return false.
    s = "paper", t = "title", return true.

**Tags** `Hash Table` 

##解题思路
这个题比较简单，尝试将s[i]替换为t[i]，记录一些从s中的字符替换到t之后的映射以及t中字符对s中字符的映射，然后在尝试替换时看与之前的映射是否有冲突即可。详见代码。

另外需要注意的是，一个字符为8位，大小界于0~255之间。

##代码

```
/** 判断两个字符串是否同构 */
bool isIsomorphic(char* s, char* t) {   
    int len = strlen(s);
    if (len != strlen(t)) return false;

    // mapTo表示s中的某种字符替换到t之后的字符
    // mapFrom表示t中的某种字符替换到s之后字符
    int mapTo[256], mapFrom[256];
    // 初始化为-1
    int i = -1;
    while (++i < 256) mapTo[i] = mapFrom[i] = -1;

    i = 0;
    char from, to;
    while (i < len) {
        from = *(s + i);
        to = *(t + i);
        // 如果两个字符都没有做过替换
        if (mapTo[from] == -1 && mapFrom[to] == -1) { 
            mapTo[from] = to;  // 替换并记录两个字符的映射
            mapFrom[to] = from;
        } else {
            // 如果两个字符中有一个做过映射，且与当前映射情况不符，返回false
            if (mapTo[from] != -1 && mapTo[from] != to)
                return false;
            if (mapFrom[to] != -1 && mapFrom[to] != from)
                return false;
        }
        ++i;
    }

    return true;
}
```

> 完整代码　[https://github.com/Orange1991/leetcode/blob/master/205/c/main.c](https://github.com/Orange1991/leetcode/blob/master/205/c/main.c)

##测试数据


    s = egg,
    t = add,
    they are isomorphic.

    s = foo,
    t = bar,
    they are not isomorphic.
    
    s = paper,
    t = title,
    they are isomorphic.
    
    s = a,
    t = a,
    they are isomorphic.
    
    s = ab,
    t = ab,
    they are isomorphic.

    s = 13,
    t = 42,
    they are isomorphic.

##博文地址
http://blog.csdn.net/smile_watermelon/article/details/47343219

---
2015/8/7
