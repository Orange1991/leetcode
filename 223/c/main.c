#include <stdio.h>

int computeArea(int A, int B, int C, int D, int E, int F, int G, int H) {
    return (D - B) * (C - A) + (H - F) * (G - E) -
            computeRetainArea(A, B, C, D, E, F, G, H);
}

int computeRetainArea(int A, int B, int C, int D, int E, int F, int G, int H) {
    void sort(int*, int, int);
    if (E >= C || G <= A || H <= B || F >= D) return 0; // 不重合
    int nums[4];
    // 计算x坐标重合区域差值
    nums[0] = A;
    nums[1] = C;
    nums[2] = E;
    nums[3] = G;
    sort(nums, 0, 3);
    int diffX = nums[1] - nums[2];
    // 计算y坐标重合区域差值
    nums[0] = B;
    nums[1] = D;
    nums[2] = F;
    nums[3] = H;
    sort(nums, 0, 3);
    int diffY = nums[1] - nums[2];
    
    int ans = diffX * diffY;
    return ans < 0 ? -ans : ans;
}

/** 快排 */
void sort(int* nums, int start, int end) {
    if (start >= end) return;
    int tmp = *(nums + start), head = start, tail = end;
    while (head < tail) {
        while (head < tail && *(nums + tail) >= tmp) --tail;
        *(nums + head) = *(nums + tail);
        while (head < tail && *(nums + head) < tmp) ++head;
        *(nums + tail) = *(nums + head);
    }
    *(nums + head) = tmp;
    sort(nums, start, head - 1);
    sort(nums, head + 1, end);
}

int main() {
    printf("%d\n", computeArea(-3,0,3,4,0,-1,9,2));
    printf("%d\n", computeArea(-2,-2,2,2,-2,-2,2,2));
    printf("%d\n", computeArea(0,0,0,0,-1,-1,1,1));
    return 0;
}
