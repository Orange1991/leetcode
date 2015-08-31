#include <stdio.h>
#include <math.h>
#include <stdbool.h>

bool isUgly(int num) {
    bool isPrime(int);
    if (num <= 0) return false;
    if (num <= 6) return true;

    int i = 1, root = sqrt(num);
    while (i <= root) {
        if (num % i == 0 && (isPrime(i) || isPrime(num / i)))
            return false;
        ++i;
    }
    return true;
}

bool isPrime(int num) {
    if (num <= 0) return false;
    int root = sqrt(num), i = 2;
    while (i <= root) {
        if (num % i == 0) return false;
        ++i;
    }
    return num != 1 && num != 2 && num != 3 && num != 5;
}

void test(int num) {
    if (isUgly(num)) printf("%d, is ugly.\n", num);
    else printf("%d, is not ugly.\n", num);
}

int main() {
    int i;
    for (i = 0; i < 100; ++i)
        test(i);
//test(8);
    return 0;
}
