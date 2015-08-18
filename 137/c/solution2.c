#include <stdio.h>

int singleNumber(int* nums, int numsSize) {
    int one = 0, two = 0, three = 0, tmp;
    while (numsSize) {
        // 获取当前要统计的数字
        tmp = *(nums + --numsSize); 
        // 之前已经出现2次1的位且当前数字中又为1，则更新为出现3次
        three = two & tmp; 
        // 清空上一步操作中出现3次1的位
        two &= ~three;  // 在two中清空
        tmp &= ~three;  // 当前数字也要清空，以防重复统计
        // 之前已经出现1次1的位且当前数字中又为1，则更新为出现2次
        two |= one & tmp;
        // 之前没有出现且当前数字中为1，更新为出现1次
        // 或者之前出现次数为1次，且当前数字中没有出现，仍旧为1次
        one ^= tmp;
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
