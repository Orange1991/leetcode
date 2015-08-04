#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#define CACHE_SIZE 1000
/**
 * 分数转换为小数
 * @param numerator 分子
 * @param denominator 分母
 * @return 字符串
 * 如果小数部分是循环小数，用括号把循环部分包括起来
 */
char* fractionToDecimal(int numerator, int denominator) {
    bool isNegative = numerator < 0 ^ denominator < 0; // 结果是否为负数
    /* 处理为正数 */
    double doubleNumerator = fabs(numerator);
    double doubleDenominator = fabs(denominator);
    double integral = floor(doubleNumerator / doubleDenominator); // 结果的整数部分
    doubleNumerator -= doubleDenominator * integral; // 余数部分

    /* 计算并缓存计算结果 */
    int len = 0; // 小数部分长度
    int cache[CACHE_SIZE];
    double dividendCache[CACHE_SIZE];
    bool isRecurring = false; // 是否是循环小数
    int recurringStart = 0; // 循环开始位
    int i = 0;
    while (doubleNumerator) { // 分子（余数）不为0时继续计算
        doubleNumerator *= 10; // 被除数乘10
        for (i = 0; i < len; ++i) // 查询是否构成循环（被除数是否已经存在过）
            if (*(dividendCache + i) == doubleNumerator) {
                isRecurring = true; 
                recurringStart = i;
                break;
            }
        if (isRecurring) break; // 如果构成循环，结束计算

        *(cache + len) = (int)(floor(doubleNumerator / doubleDenominator)); // 记录商
        *(dividendCache + len) = doubleNumerator; // 记录被除数
        doubleNumerator -= doubleDenominator * *(cache + len); // 被除数取余，作为下次计算的被除数
        ++len;
    }

    /* 根据缓存数据生成返回数据 */
    char* ret = NULL;
    int symbolLen = isNegative ? 1 : 0; // 符号位长度
    int integralLen = 1; // 整数部分长度
    i = integral / 10;
    while (i) { // 计算整数部分长度
        ++integralLen;
        i /= 10;
    }
    /* 内存分配 */
    ret = (char*)malloc(sizeof(char) * (symbolLen + integralLen + (len == 0 ? 0 : 1) + (isRecurring ? 2 : 0 + 1)));
    int index = 0;
    /* 符号部分 */
    if (isNegative) *(ret + index++) = '-';
    /* 整数部分 */
    for (i = integralLen - 1; i > -1; --i) {
        *(ret + symbolLen + i) = (integral - 10 * floor(integral / 10)) + '0';
        integral = floor(integral / 10);
    }
    index = symbolLen + integralLen;
    /* 小数部分 */
    if (len > 0) *(ret + index++) = '.';
    i = 0;
    if (isRecurring) {
        for (; i < recurringStart; ++i) *(ret + index++) = *(cache + i) + '0';
        *(ret + index++) = '(';
    }
    for (; i < len; ++i) *(ret + index++) = *(cache + i) + '0';
    if (isRecurring) *(ret + index++) = ')';
    *(ret + index++) = '\0';

    return ret;
}

void test(int numerator, int denominator) {
    char *ret = fractionToDecimal(numerator, denominator);
    printf("%d/%d = %s\n", numerator, denominator, ret);
//    free(ret);
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
