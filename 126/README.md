#Word Ladder II
##原题地址
https://leetcode.com/problems/word-ladder-ii/

##题目描述
Given two words (start and end), and a dictionary, find all shortest transformation sequence(s) from start to end, such that:
给出两个单词（开始单词和结束单词）和一个字典，找出从开始单词到结束单词的最短转换序列，转换规则：

1.Only one letter can be changed at a time
每次只能改变其中一个字母
2.Each intermediate word must exist in the dictionary
每个中间单词必须是字典中的单词

For example, Given:
例如，给出：

    start = "hit"
    end = "cog"
    dict = ["hot","dot","dog","lot","log"]

Return，
返回

    [
        ["hit","hot","dot","dog","cog"],
        ["hit","hot","lot","log","cog"]
    ]

Note:
注意：

All words have the same length.
所有的单词长度相同。

All words contain only lowercase alphabetic characters.
所有的单词仅含小写字母。

##解题思路

##代码 cpp

在`g++`环境下编译时需要加入参数`-std=c++0x`

    g++ main.cpp -std=c++0x -o main

> https://github.com/Orange1991/leetcode/blob/master/126/cpp/solution2.cpp

##解决情况
| Language | Name | Time |
| :------- | : -- | :--- |
| cpp      | solution2.cpp | 1248ms |

##测试数据
    start: hit
    end: cog
    dictionary: [hot,log,dot,dog,lot]
    path: 
    [
        [hit,hot,dot,dog,cog],
        [hit,hot,lot,log,cog]
    ]

    start: a
    end: b
    dictionary: [b,a,c]
    path:
    [
        [a,b]
    ]

    start: aaa
    end: cbb
    dictionary: [aab,aba,abb]
    path:
    [
        [aaa,aab,abb,cbb],
        [aaa,aba,abb,cbb]
    ]

    start: hot
    end: dog
    dictionary: [dog,hot]
    path:[]


---
2015/7/22
