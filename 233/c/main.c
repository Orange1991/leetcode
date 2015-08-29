#include <stdio.h>

int countDigitOne(int n) {
    if (n < 1) return 0;
    if (n < 10) return 1;
    long long nl = n, m = 1, rest = n;
    int offset = 0, count = 0;
    while (nl >= 10) {
        ++offset;
        nl /= 10;
        m *= 10;
    }
    count += (int)nl * offset * m / 10;
    rest -= m * nl;
    if (nl > 1) count += m;
    else count += rest + 1;
    count += countDigitOne(rest);

    return count;
}

void test(int n) {
    printf("%d : %d\n", n, countDigitOne(n));
}

int main() {
    test(10);
    test(13);
    test(999);
    test(4564);
    test(1564);
    test(564);
    test(824883294);
}
