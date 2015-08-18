#include <stdio.h>

int singleNumber(int* nums, int numsSize) {
    int one = 0, two = 0, three = 0;
    while (numsSize) {
        // 之前已经出现1次1的位且当前数字中又为1，则更新为出现2次
        two |= one & *(nums + --numsSize);
        // 之前没有出现且当前数字中为1，更新为出现1次
        // 或者之前出现次数为1次，且当前数字中没有出现，仍旧为1次
        one ^= *(nums + numsSize);
        // 既出现了一次又出现了两次的位即出现了3次
        three = two & one;
        // 清空出现了三次的位
        two &= ~three;
        one &= ~three;
    }
    return one;
}

void test(int* nums, int numsSize) {
    printf("    [");
    int i;
    for (i = 0; i < numsSize - 1; ++i)
        printf("%d,", *(nums + i));
    printf("%d] : %d\n", *(nums + numsSize - 1), singleNumber(nums, numsSize));

}

int main() {
    int nums[] = {1,2,3,4,1,2,3,1,2,3};
    test(nums, 10);
}
