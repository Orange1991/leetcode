#include <stdio.h>

int addDigits(int num) {
    if (num == 0) return 0;
    num %= 9;   
    return num == 0 ? 9 : num;
}

int main() {
    int i;
    for (i = 0; i < 110; ++i) {
        printf("%d : %d\n", i , addDigits(i));
    }
    return 0;
}
