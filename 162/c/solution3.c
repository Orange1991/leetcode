#include <stdio.h>

int findPeakElement(int* nums, int numsSize) {
    int front = 0, back = numsSize - 1, center;
    while (front <= back) {
        if (front == back) return front;
        center = (front + back) / 2;
        if (*(nums + center) < *(nums + center + 1))
            front = center + 1;
        else
            back = center;
    }
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

