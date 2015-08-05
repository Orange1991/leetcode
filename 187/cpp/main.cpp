#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

class Solution {
public:
    vector<string> findRepeatedDnaSequences(string s) {
        vector<string> strs;
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

void test(string str) {
    Solution s;
    vector<string> strs = s.findRepeatedDnaSequences(str);
    cout << str << " : ";
    for (int i = 0, len = strs.size(); i < len; ++i)
        cout << strs[i] << " ";
    cout << endl;
}

int main() {
    test("AAAAACCCCCAAAAACCCCCCAAAAAGGGTTT");
    test("AAAAAAAAAAAA");
    return 0;
}
