#include <stdio.h>

void moveZeroes(int* nums, int numsSize) {
    int slow = 0, fast = 0;

    // 找到第一个0元素
    while (nums[fast] != 0)
        ++fast;
    slow = fast; // slow指向第一个0的位置
    ++fast;      // fast指向0之后的位置
    
    // 遍历剩余所有元素
    while (fast < numsSize) {
        if (nums[fast] == 0) { // 遇到0则跳过
            ++fast;
	    continue;
        } else { // 如果不是0元素，则向前复制
            nums[slow++] = nums[fast++];
        }
    }

    // 将slow之后的所有位置都赋值为0
    while (slow < numsSize)
        nums[slow++] = 0;
}

void print(int nums[], int n) {
    int i;
    for (i = 0; i < n; ++i) {
        printf("%d ", nums[i]);
    }
    printf("\n");
}

int main() {
    int nums[] = {0, 1, 0, 3, 12};
    print(nums, 5);
    moveZeroes(nums, 5);
    print(nums, 5);
}
