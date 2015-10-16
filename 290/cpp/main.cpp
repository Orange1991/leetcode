#include <iostream>
#include <unordered_map>

using namespace std;

class Solution {
public:
    bool wordPattern(string pattern, string str) {
        string lastWord[26]; // 字符到单词的映射
	unordered_map<string, char> map; // 单词到字符的映射

        // 初始化字符到字符串的映射
        for (int i = 0; i < 26; ++i)
            lastWord[i] = "";
            
        int len = str.size(), patternLen = pattern.size();
        int start = 0, end = 0, patternIndex = 0;
        string sub;
        
	// 依次获取下一个单词
        while (patternIndex < patternLen && end < len) {
            while (end < len && str[end] != ' ') // 找到单词结尾
                ++end;
            // 截取单词
            sub = str.substr(start, end - start);
            
	    // 判断字符到单词的映射是否与之前的映射冲突
            if (lastWord[pattern[patternIndex] - 'a'] == "") // 之前没有保存过该字符的映射
                lastWord[pattern[patternIndex] - 'a'] = sub; // 存储新的映射
            else if (lastWord[pattern[patternIndex] - 'a'] != sub) // // 与之前的映射不符合
	        return false;
                
	    // 判断单词到字符的映射是否与之前的映射冲突
            if (map.find(sub) == map.end()) // 之前没有保存过该单词的映射
                map[sub] = pattern[patternIndex]; // 存储新的映射
            else if (map[sub] != pattern[patternIndex]) // 与之前的映射不符
                return false;
                
            ++patternIndex;  // 指向下一个字符
            start = end + 1; // 下一个单词开始位置
	    end = start;     // 下一个单词初始结束位置
        }

        // 如果pattern和str均已走到结尾了，则匹配成功
        return end >= len && patternIndex >= patternLen;
    }
};

int main() {
    Solution s;
    cout << s.wordPattern("abba", "dog cat cat dog") << endl;
    cout << s.wordPattern("abba", "dog cat cat fish") << endl;
    cout << s.wordPattern("aaaa", "dog cat cat dog") << endl;
    cout << s.wordPattern("aaaa", "dog dog dog dog") << endl;
    cout << s.wordPattern("aaa", "dog dog dog dog") << endl;
    cout << s.wordPattern("abba", "dog dog dog dog") << endl;
}
