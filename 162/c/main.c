#include <stdio.h>

int findPeakElement(int* nums, int numsSize) {
    if (numsSize == 1) return 0;
    if (*nums > *(nums + 1)) return 0;
    int i = 1;
    for (; i < numsSize - 1; ++i) {
        if (*(nums + i) > *(nums + i - 1) && *(nums + i) > *(nums + i + 1))
            return i;
    }
    return numsSize - 1;
}

void test(int* nums, int numsSize) {
    int i = 0;
    printf("[");
    for (i = 0; i < numsSize - 1; ++i)
        printf("%d, ", *(nums + i));
    printf("%d] : %d\n", *(nums + i), findPeakElement(nums, numsSize));
}

int main() {
    int nums1[] = {1, 2, 3, 1};
    test(nums1, 4);
    return 0;
}

