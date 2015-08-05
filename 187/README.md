#Leetcode 187 Repeated DNA Sequences 重复出现的DNA序列

##原题地址
https://leetcode.com/problems/repeated-dna-sequences/

##题目描述
All DNA is composed of a series of nucleotides abbreviated as A, C, G, and T, for example: "ACGAATTCCG". When studying DNA, it is sometimes useful to identify repeated sequences within the DNA.
所有的DNA都是由简写为`A``C``G``T`的核苷酸构成的，例如`ACGAATTCCG`。在研究DNA时，辨别DNA中重复的序列在有些时候是很有用的。

Write a function to find all the 10-letter-long sequences (substrings) that occur more than once in a DNA molecule.
编写一个程序来找到一个DNA分子中出现次数超过一次的长度为10的子序列（子串）。

For example,
例如，

Given s = `"AAAAACCCCCAAAAACCCCCCAAAAAGGGTTT"`,
给出 s = `"AAAAACCCCCAAAAACCCCCCAAAAAGGGTTT"`,

Return:
返回：

    ["AAAAACCCCC", "CCCCCAAAAA"].

**Tags** `Hash Table` `Bit Manipulation`

##解题思路
嗯，这个题，如果时间上没有要求的话，用find和substr搞定是没问题的，然而在测试数据较大的时候这种方法必然会超时。

这个题的标签是Hash Table和Bit Manipulation，参考[https://leetcode.com/discuss/24478/i-did-it-in-10-lines-of-c](https://leetcode.com/discuss/24478/i-did-it-in-10-lines-of-c)中的方案，现做如下整理。

测试数据中只会出现4种字符'A','C','G','T'，其ASC值分别为65,67,71,84,对应的二进制位如下所示，这里仅列取32位情况下的低8位，前24位全部为0。

    A --- 65 --- 0100 0001
    C --- 67 --- 0100 0011
    G --- 71 --- 0100 0111
    T --- 84 --- 0101 0100

我们可以发现，仅通过**低3位**就能把4种字符区分开来，题目又要求了是`长度为10的子串`（`10-letter-long`），试想为什么不是11或者更大呢，因为10个字符每个用3位表示一个字符的话刚好是30位，而一个int是32位，刚好能放下，如果是11+就放不下了。因此，我们可以**把一个长度为10的字符串映射成一个int数**，用其低30位表示这个串，**作为这个串的key**，然后把**key存在Hash Table中**，当**key重复出现**时就代表子串重复出现了。

详细代码请见下文。

除了上述方法外，受其启发，我们其实只用**2个二进制位**就可以唯一区分4中字符，比如`A-00,C-01,G-10,T-11`，这样，我们只用int的低20位就可以表示一个字符串的key，这种方法甚至可以最多用于处理长度为16的子串。比上面一种方法略显复杂的是，需要手动将ACGT映射成2位二进制数，方法也是多种多样的。比如：

**方法一**
```
/** @return 字符到2位二进制数的映射 */
int function(char c) {
    int ret = 0;
    switch (c) {
        case 'A': break;
        case 'G': ret = 1; break;
        case 'C': ret = 2; break;
        case 'T': ret = 3; break;
    }
    return ret;
}
```
**方法二**
```
/* 数组映射，调用时使用nums[c - 65]即可得到字符c的映射码 */
int nums[20]; 
nums[0] = 0; 
nums[2] = 1; 
nums[6] = 2; 
nums[19] = 3;
```

除此外，在讨论贴中还看到了另外一种很巧妙的映射方法：

**方法三**
```
/** 
 * (s[i] - 64) % 5完成映射
 * A : ('A' - 64) % 5 = 1  (mod 5) = 1 = 01
 * B : ('C' - 64) % 5 = 3  (mod 5) = 3 = 11
 * C : ('G' - 64) % 5 = 7  (mod 5) = 2 = 10
 * D : ('T' - 64) % 5 = 20 (mod 5) = 0 = 00
 */
key = key << 2 & 0xfffff | (s[i] - 64) % 5;
```

##代码

###代码一

首先是用ACGT的**ASC码的后3位**来映射的解法。在代码编写中，对于最开始的9个字符是为了构造第一个key而做功，一般说来从第10个字符开始才开始判定key的重复出现情况。然而由于**AGCT的映射码均为三位且没有任何一个码是000**，因此在前面9个字符也是可以与其他字符**一致处理**的，不会出现误判。一致处理的代码大致如下：
```
class Solution {
public:
    vector<string> findRepeatedDnaSequences(string s) {
        vector<string> strs;
        unordered_map<int, int> map;
        int key = 0; 
        for (int i = 0, end = s.size(); i < end; ++i) {
            key = ((key << 3) | (s[i] & 0x7)) & 0x3fffffff;
            if (map[key]++ == 1)
                strs.push_back(s.substr(i - 9, 10));
        }
        return strs; 
    }
};
```
不一致处理的代码大概如下，先处理前9个字符，然后处理后面的：
```
class Solution {
public:
    vector<string> findRepeatedDnaSequences(string s) {
        vector<string> strs;
        if (s.size() <= 10) return strs;
        unordered_map<int, int> map;
        int key = 0, i = 0; 
        for (; i < 9; ++i)
            key = ((key << 3) | (s[i] & 0x7)) & 0x3fffffff;
        for (int end = s.size(); i < end; ++i) {
            key = ((key << 3) | (s[i] & 0x7)) & 0x3fffffff;
            if (map[key]++ == 1)
                strs.push_back(s.substr(i - 9, 10));
        }
        return strs; 
    }
};
```
> 完整代码[https://github.com/Orange1991/leetcode/blob/master/187/cpp/main.cpp](https://github.com/Orange1991/leetcode/blob/master/187/cpp/main.cpp)

很难说到底哪种代码更好。如果从代码精简的方面来看，**前面一个代码数量更少**；但是前面一种代码对于前9个字符也会把key放入map中且会判定是否key重复出现，这个**操作是多余的**，相比于后面的解法来说就多了一些无用的操作，在实际的运行中也证实了这一点，前一种时间为100ms，而后一种为96ms。另外，对于前面一种方案，是否可以将前9个字符与其他字符一致处理而不致于误判，还**要看AGCT映射码中是否有全0的码**，如果有则不能一致处理，就拿接下来马上要说的解法二来说，我们把A映射为00，假如我们的串是AA（你没看错，就是只有2位的串），那对于第一个字符，key计算后得到结果为0（你没看错，就是0），我们把0放入map并且其value为0，然后，在第二个字符，key计算后仍然为0，这时候根据规则，以第二个A为结尾的10个字符要放入结果集中，这时候程序一定会崩溃的（s.substr(-8, 10)）。因此，我们还是直接用后面一种解法就好，代码不过多了两行，而且不会出现误判，哪怕映射码中有全0码也没问题。

###代码二 自定义映射码

在前面**解题思路**中已经说的比较详细了，因此不再赘述，仅列出代码

```
class Solution {
public:
    vector<string> findRepeatedDnaSequences(string s) {
        vector<string> strs;
        if (s.size() <= 10) return strs;
        unordered_map<int, int> map;
        int key = 0, i = 0; 
        /* 映射逻辑: A-01, C-11, G-10, T-00  */
        for (; i < 9; ++i)
            key = ((key << 2) | ((s[i] - 64) % 5)) & 0xfffff;
        for (int end = s.size(); i < end; ++i) {
            key = ((key << 2) | ((s[i] - 64) % 5)) & 0xfffff;
            if (map[key]++ == 1)
                strs.push_back(s.substr(i - 9, 10));
        }
        return strs; 
    }
};
```
> 完整代码[https://github.com/Orange1991/leetcode/blob/master/187/cpp/solution2.cpp](https://github.com/Orange1991/leetcode/blob/master/187/cpp/solution2.cpp)

##博文地址
http://blog.csdn.net/smile_watermelon/article/details/47298637

##参考
https://leetcode.com/discuss/24478/i-did-it-in-10-lines-of-c
http://blog.csdn.net/ljiabin/article/details/44488619

---
2015/8/5
