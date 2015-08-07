#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int countPrimes(int n) {
    bool* isPrime = (bool*)malloc(sizeof(bool) * n);

    // 初始化为true
    int i, j;
    for (i = 0; i < n; ++i) *(isPrime + i) = true;

    // 标记非质数
    for (i = 2; i * i < n; ++i) {
        if (!*(isPrime + i)) continue;
        for (j = i * i; j < n; j += i)
            *(isPrime + j) = false;
    }
    
    // 统计
    int count = 0;
    for (i = 2; i < n; ++i)
        if (*(isPrime + i)) ++count;

    free(isPrime);
    return count;
}

void test(int n) {
    printf("%d : %d\n", n, countPrimes(n));
}

int main() {
    test(0);
    test(1);
    test(2);
    test(3);
    test(4);
    test(5);
    test(6);
    test(10);
    test(100);

    return 0;
}
