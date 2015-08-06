#include <stdio.h>

int rangeBitwiseAnd(int m, int n) {   
    int i = m + 1;
    while (m && i <= n)
        m &= i++;
    return m;
}

void test(int m, int n) {
    printf("m = %d, n = %d, result = %d\n", m, n, rangeBitwiseAnd(m, n));
}

int main() {
    test(5, 7);
    return 0;
}
