#include <stdio.h>

int rangeBitwiseAnd(int m, int n) {   
    int offset = 0;
    while (m && n) {
        if (m == n) return m << offset;
        m >>= 1;
        n >>= 1;
        ++offset;
    }
    return 0;
}

void test(int m, int n) {
    printf("m = %d, n = %d, result = %d\n", m, n, rangeBitwiseAnd(m, n));
}

int main() {
    test(5, 7);
    test(0, 2147483645);
    test(600000000, 2147483645);
    return 0;
}
