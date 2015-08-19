##代码说明

s1.cpp 不使用Trie的startsWith和search，减少了重复查找，不使用额外数组来标记字符使用情况，AC

s2.cpp 不使用Trie的startsWith和search，减少了重复查找，但使用额外数组来标记字符使用情况，AC

s3.cpp 使用Trie的startsWith和search，有重复查找，AC

trie.cpp 使用board来构建字典树，构建过程超时，TLE
