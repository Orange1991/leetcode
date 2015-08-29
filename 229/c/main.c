#include <stdio.h>
#include <stdlib.h>

int* majorityElement(int* nums, int numsSize, int* returnSize) {
    int n1, n2, count1 = 0, count2 = 0, i;
    for (i = 0; i < numsSize; ++i) {
        if (count1 == 0) {
            n1 = *(nums + i);
            count1 = 1;
        } else if (n1 == *(nums + i)) {
            ++count1;
        } else if (count2 == 0) {
            n2 = *(nums + i);
            count2 = 1;
        } else if (n2 == *(nums + i)) {
            ++count2;
        } else {
            --count1;
            --count2;
        }
    }
    int* ret = (int*)malloc(sizeof(int) * 2);
    *returnSize = 0;
    count1 = 0;
    count2 = 0;
    for (i = 0; i < numsSize; ++i)
        if (*(nums + i) == n1)
            ++count1;
        else if (*(nums + i) == n2)
            ++count2;
    if (count1 > numsSize / 3)
        *(ret + (*returnSize)++) = n1;
    if (count2 > numsSize / 3)
        *(ret + (*returnSize)++) = n2;
    return ret;
}

void test(int* nums, int numsSize) {
    int size, i;
    printf("[");
    for (i = 0; i < numsSize - 1; ++i)
        printf("%d,", *(nums + i));
    printf("%d] : ", *(nums + numsSize - 1));
    int* ret = majorityElement(nums, 14, &size);
    if (size == 1)
        printf("%d\n", *ret);
    else if (size == 2)
        printf("%d,%d\n", *ret, *(ret + 1));
    free(ret);
}

int main() {
    int nums1[] = {1,2,3,1,2,3,1,2,3,1,2,3,2,3};
    test(nums1, 14);
    return 0;
}
