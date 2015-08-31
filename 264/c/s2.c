#include <stdio.h>
#include <stdlib.h>

int nthUglyNumber(int n) {
    void mergeToUgly(long long*, int*, int, long long*, int*, long long*, int*, long long*, int*);
    if (n <= 6) return n;
    long long* ugly = (long long*)malloc(sizeof(long long) * n * 5);
    long long* l2 = (long long*)malloc(sizeof(long long) * n);
    long long* l3 = (long long*)malloc(sizeof(long long) * n);
    long long* l5 = (long long*)malloc(sizeof(long long) * n);

    *ugly = 1;
    int count = 1, p2 = 0, p3 = 0, p5 = 0, cur = 0, l2max;
int last = 0;
    while (count < n) {
        for (; cur < count; ++cur) {
            *(l2 + cur) = *(ugly + cur) * 2;
            *(l3 + cur) = *(ugly + cur) * 3;
            *(l5 + cur) = *(ugly + cur) * 5;
        }
        l2max = *(l2 + count - 1);
        mergeToUgly(ugly, &count, l2max, l2, &p2, l3, &p3, l5, &p5);
    if (last == count) break;
    last = count;
    }
int i;
for (i = 0; i <= 1407; ++i) {
    //printf("%lld  ", *(l2 + i));
}
    printf("%lld  ", *(l2 + 1406));
    printf("%lld  ", *(l2 + 1407));
    printf("%lld  ", *(l2 + 1408));
    printf("%lld  ", *(l2 + 1409));
for (i = 0; i <= 1328; ++i) {
//    printf("%lld  ", *(l3 + i));
}
    int ans = *(ugly + n - 1);
    free(ugly);
    free(l2);
    free(l3);
    free(l5);

    return ans;
}

void mergeToUgly(long long* ugly, int* count, int max, long long* l2, int* p2, long long* l3, int* p3, long long* l5, int* p5) {
    int end = *count;
    while (*p2 < end && *(l2 + *p2) <= max) {
        if (*(l2 + *p2) <= *(l3 + *p3) && *(l2 + *p2) <= *(l5 + *p5)) { // l2[p2] is the minimum.
            if (*(l2 + *p2) == *(ugly + *count - 1)) {
                ++(*p2);
                continue;
            }
if (*count == 1544) {
    printf("1545))()(+++++---%d,%lld, %d,%lld, %d,%lld\n",*p2, *(l2 + *p2), *p3,*(l3 + *p3),*p5, *(l5 + *p5));
}
            *(ugly + (*count)++) = *(l2 + (*p2)++);    // add the count-th ugly number.
if (*count == 1545) {
    printf("1545))()(+++++---%d,%lld, %d,%lld, %d,%lld\n",*p2, *(l2 + *p2), *p3,*(l3 + *p3),*p5, *(l5 + *p5));
}
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
    printf("%d : %d\n", 15, nthUglyNumber(15));
    printf("%d : %d\n", 1600, nthUglyNumber(1600));
    return 0;
}
