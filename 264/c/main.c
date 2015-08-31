#include <stdio.h>
#include <stdlib.h>

int nthUglyNumber(int n) {
    void mergeToUgly(int*, int*, int, int*, int*, int*, int*, int*, int*);
    if (n <= 6) return n;
    int* ugly = (int*)malloc(sizeof(int) * n * 5);
    int* l2 = (int*)malloc(sizeof(int) * n);
    int* l3 = (int*)malloc(sizeof(int) * n);
    int* l5 = (int*)malloc(sizeof(int) * n);

    *ugly = 1;
    int count = 1, p2 = 0, p3 = 0, p5 = 0, cur = 0, l2max;
    while (count < n) {
        for (; cur < count; ++cur) {
            *(l2 + cur) = *(ugly + cur) * 2;
            *(l3 + cur) = *(ugly + cur) * 3;
            *(l5 + cur) = *(ugly + cur) * 5;
        }
        l2max = *(l2 + cur - 1);
        mergeToUgly(ugly, &count, l2max, l2, &p2, l3, &p3, l5, &p5);
printf("%d %d\n", count, *(ugly + count - 1));
    }

    int ans = *(ugly + n - 1);
    free(ugly);
    free(l2);
    free(l3);
    free(l5);

    return ans;
}

void mergeToUgly(int* ugly, int* count, int max, int* l2, int* p2, int* l3, int* p3, int* l5, int* p5) {
    int end = *count;
if (*count == 1545)
    printf("%lld, %lld, %lld\n", *(l2 + *p2), *(l3 + *p3), *(l5 + *p5));
    while (*p2 < end && *(l2 + *p2) <= max) {
        if (*(l2 + *p2) <= *(l3 + *p3) && *(l2 + *p2) <= *(l5 + *p5)) { // l2[p2] is the minimum.
            if (*(l2 + *p2) == *(ugly + *count - 1)) {
                ++(*p2);
                continue;
            }
            *(ugly + (*count)++) = *(l2 + (*p2)++);    // add the count-th ugly number.
        } else if (*(l3 + *p3) <= *(l5 + *p5)) {    // l3[p3] is the minimum.
            if (*(l3 + *p3) == *(ugly + *count - 1)) {
                ++(*p3);
                continue;
            }
            *(ugly + (*count)++) = *(l3 + (*p3)++);    // add the count-th ugly number.
        } else {    // l5[p5] is the minimum.
            if (*(l5 + *p5) == *(ugly + *count - 1)) {
                ++(*p5);
                continue;
            }
            *(ugly + (*count)++) = *(l5 + (*p5)++);    // add the count-th ugly number.
        }
    }
}

int main() {
    printf("%d : %d\n", 20, nthUglyNumber(20));
    printf("%d : %d\n", 1600, nthUglyNumber(1600));
    return 0;
}
