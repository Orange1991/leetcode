#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

class Solution {
public:
    const static int CACHE_SIZE = 1000;
    /**
     * 分数转换为小数
     * @param numerator 分子
     * @param denominator 分母
     * @return 字符串
     * 如果小数部分是循环小数，用括号把循环部分包括起来
     */
    string fractionToDecimal(int numerator, int denominator) {
        if (numerator == 0) return "0";
        
        bool isNegative = numerator < 0 ^ denominator < 0; // 结果是否为负数
        /* 处理为正数 */
        double doubleNumerator = fabs(numerator);
        double doubleDenominator = fabs(denominator);
        double integral = floor(doubleNumerator / doubleDenominator); // 结果的整数部分
        doubleNumerator -= doubleDenominator * integral; // 余数部分
    
        /* 计算并缓存计算结果 */
        int len = 0; // 小数部分长度
        string cache;// 小数部分缓存
        vector<double> dividendCache;
        bool isRecurring = false; // 是否是循环小数
        int recurringStart = 0; // 循环开始位
        int i = 0;
        while (doubleNumerator) { // 分子（余数）不为0时继续计算
            doubleNumerator *= 10; // 被除数乘10
            len = dividendCache.size();
            for (i = 0; i < len; ++i) // 查询是否构成循环（被除数是否已经存在过）
                if (dividendCache[i] == doubleNumerator) {
                    isRecurring = true; 
                    recurringStart = i;
                    break;
                }
            if (isRecurring) break; // 如果构成循环，结束计算
            i = (int)(floor(doubleNumerator / doubleDenominator)); // 商
            cache += '0' + i; // 记录商
            dividendCache.push_back(doubleNumerator); // 记录被除数
            doubleNumerator -= doubleDenominator * i; // 被除数取余，作为下次计算的被除数
        }
    
        /* 根据缓存数据生成返回数据 */
        /* 符号部分 */
        string ret = isNegative ? "-" : "";
        /* 整数部分 */
        string tmp;
        char c;
        if (integral == 0) ret += "0";
        else {
            while (integral) {
                c = (int)(integral - 10 * floor(integral / 10))+ '0';
                tmp = c + tmp;
                integral = floor(integral / 10);
            }
            ret += tmp;
        }
        /* 小数部分 */
        if (dividendCache.size() > 0) ret += '.';
        i = 0;
        if (isRecurring) {
            ret += cache.substr(0, recurringStart);
            ret += '(';
            ret += cache.substr(recurringStart);
            ret += ')';
        } else
            ret += cache;
    
        return ret;
    }
};

void test(int numerator, int denominator) {
    Solution s;
    cout << "    " << numerator << " / " << denominator << " = " << s.fractionToDecimal(numerator, denominator) << endl;
}
int main() {
    test(2, 1);
    test(-2, 1);
    test(1, 2);
    test(1, -2);
    test(1, 3);
    test(-1, 3);
    test(2, 7);
    test(-2, 7);
    test(1, 11);
    test(-1, -11);
    test(2147483647, 27);
    test(-2147483647, 27);
    test(2147483647, 37);
    test(2147483647, -37);
    test(1000, 10);
    test(1000, -10);
    test(1001, 10);
    test(-1001, 10);
    test(-2147483648, 1);
    test(-2147483648, -1);
    test(1, 214748364);
    test(-1, -2147483648);
    test(1, 2147483648);
    test(-1, 2147483648);
    test(1, 6);
    return 0;
}
