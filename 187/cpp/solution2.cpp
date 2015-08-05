#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

class Solution {
public:
    vector<string> findRepeatedDnaSequences(string s) {
        vector<string> strs;
        if (s.size() <= 10) return strs;
        unordered_map<int, int> map;
        int key = 0, i = 0; 
        /* (s[i] - 64) % 5完成映射
         * A : ('A' - 64) % 5 = 1  (mod 5) = 1 = 01
         * B : ('C' - 64) % 5 = 3  (mod 5) = 3 = 11
         * C : ('G' - 64) % 5 = 7  (mod 5) = 2 = 10
         * D : ('T' - 64) % 5 = 20 (mod 5) = 0 = 00 */
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
