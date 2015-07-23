#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    /**
     * 把字符串s进行分解，每个子串都是回文串
     */
    vector<vector<string> > partition(string s) {
        int len = s.size();

        /* isPalindrome[i][j]表示i,j之间的字符串是否是一个回文串 
         * 对于s来说，如果s[i]==s[j]且isPalindrome[i+1][j-1]==true，则isPalindrome[i][j]=true */
        vector<vector<bool> > isPalindrome = vector<vector<bool> >(len, vector<bool>(len, false));

        /* 计算并记录子串是否为回文串  */
        // 单字符肯定是回文串
        for (int i = 0; i < len; ++i) isPalindrome[i][i] = true; 
        // 计算并记录长度为2的子串是否为回文串
        for (int i = 0; i < len - 1; ++i) isPalindrome[i][i + 1] = s[i] == s[i + 1]; 
        // 计算并记录长度为3-s.size()的子串是否为回文串
        for (int i = 2; i <= len; ++i)
            for (int j = 0; j < len - i; ++j)
                isPalindrome[j][j + i] = s[j] == s[j + i] && isPalindrome[j + 1][j + i - 1];

        /* store用于存储子串的partition结果  */
        vector<vector<vector<vector<string> > > > store 
                = vector<vector<vector<vector<string> > > >(len, vector<vector<vector<string> > >(len));
        /* done用于标记一个子串是否已经求得partition结果 */
        vector<vector<bool> > done = vector<vector<bool> >(len, vector<bool>(len, false));

        /* 计算s的0-s.size()-1之间（即字符串s）的partition结果 */
        return subPartition(s, 0, len - 1, isPalindrome, store, done);
    }

private:
    /**
     * 计算字符串s的子串s[start]-s[end]的partition结果
     * partition的结果中，每个子串都是回文串
     * @param s 字符串
     * @param start 子串的起始位置（包含）
     * @param end 子串的结束位置（包含）
     * @param isPalindrome 记录子串是否为回文串的二维数组
     * @param store 用于记录已经求得的partitiion结果
     * @param done 用于标记是否已求得partition结果
     * @return 字符串s的子串s[start]-s[end]的partition操作的结果
     */
    vector<vector<string> > subPartition(string &s, int start, int end, vector<vector<bool> > &isPalindrome,
            vector<vector<vector<vector<string> > > > &store, vector<vector<bool> > &done) {
        /* 操作结果集 */
        vector<vector<string> > ret;

        if (start > end) return ret; // 验证数据有效性，start>end，直接返回空集
        if (done[start][end]) return store[start][end]; // 如果已经求过，直接返回存储好的记录

        /* 第一次求s[start]-s[end]的partition结果 */
        for (int i = start; i < end; ++i) {
            /* 将s[start]-s[end]分为s[start]-s[i]和s[i+1]-s[end]两部分
             * 1.如果s[start]-s[i]是一个回文串，那么获取s[i+1]-s[end]的partition结果集tmp
             *   tmp中的每一个结果都把s[start]-s[i]加进去就是s[start]-s[end]的partition结果集的一个解
             * 2.如果s[start]-s[i]不是回文串，那么这种分割情况下没有可行解
             * 3.另外，如果s[start]-s[i]是回文串，但是s[i+1]-s[end]的partition结果集为空
             *   则说明此种分割情况没有可行解*/
            if (isPalindrome[start][i]) { // 仅当s[start][i]是回文串时才有可能有解
                // 获取后面子串的partition结果
                vector<vector<string> > tmp = subPartition(s, i + 1, end, isPalindrome, store, done);
                string tmpStr = s.substr(start, i - start + 1);
                // 遍历后面子串的partition结果，添加s[start]-s[i]之后添加到结果集中
                for (int j = 0; j < tmp.size(); ++j) { 
                    vector<string> tmpVec;
                    tmpVec.push_back(tmpStr);
                    tmpVec.insert(tmpVec.end(), tmp[j].begin(), tmp[j].end());
                    ret.push_back(tmpVec);
                }
            }
        }

        /* 特殊情况，判断整个字符串是否是回文串，如果是则加入结果集中 */
        if (isPalindrome[start][end]) {
            vector<string> tmp;
            tmp.push_back(s.substr(start, end - start + 1));
            ret.push_back(tmp);
        }

        /* 修改是否已求解的标志为 */
        done[start][end] = true;
        /* 存储已经求得的partition结果 */
        store[start][end] = ret;

        return ret;
    }
};

void out(string str, vector<vector<string> > data) {
    cout << endl << str << endl;
    int i, j, lenI = data.size(), lenJ;
    cout << "[" << endl;
    for (i = 0; i < lenI - 1; ++i) {
        lenJ = data[i].size();
        cout << "    [";
        for (j = 0; j < lenJ - 1; ++j)
            cout << data[i][j] << ",";
        cout << data[i][j] << "]," << endl;
    }
    lenJ = data[i].size();
    cout << "    [";
    for (j = 0; j < lenJ - 1; ++j)
        cout << data[i][j] << ",";
    cout << data[i][j] << "]" << endl;
    cout << "]" << endl;
}

int main() {
    
    Solution s;
    string str = "aab";
    vector<vector<string> > ret = s.partition(str);
    out(str, ret);

    str = "bb";
    ret = s.partition(str);
    out(str, ret);

    return 0;
}
