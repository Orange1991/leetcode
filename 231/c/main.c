#include <stdio.h>
#include <stdbool.h>

bool isPowerOfTwo(int n) {
    return n > 0 && !(n & n - 1);
}

int main() {
    int n = 1, i;
    for (i = 0; i < 32; ++i) {
        printf("%d : ", n);
        if (isPowerOfTwo(n)) printf("is power of two.\n");
        else printf("is not power of two.\n");
        printf("%d : ", n + 1);
        if (isPowerOfTwo(n + 1)) printf("is power of two.\n");
        else printf("is not power of two.\n");
        printf("%d : ", n - 1);
        if (isPowerOfTwo(n - 1)) printf("is power of two.\n");
        else printf("is not power of two.\n");
        n <<= 1;
    }
    return 0;
}
