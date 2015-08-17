#include <stdio.h>

int singleNumber(int* nums, int numsSize) {
    int tmp = 0, i;
    for (i = 0; i < numsSize; ++i)
        tmp ^= *(nums + i);
    return tmp;
}

void test(int* nums, int numsSize) {
    printf("    [");
    int i;
    for (i = 0; i < numsSize - 1; ++i)
        printf("%d,", *(nums + i));
    printf("%d] : %d\n", *(nums + numsSize - 1), singleNumber(nums, numsSize));

}

int main() {
    int nums[] = {1, 1, 2, 2, 3, 3, 4, 4, 5, 6, 6};
    test(nums, 11);
    return 0;
}
