#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int numSquares(int n) {
    int* nums = (int*)malloc(sizeof(int) * (n + 1));
    nums[0] = 0;
    int i, j, min, tmp;
    for (i = 1; i <= n; ++i) {
        min = i;
        for (j = 1; j * j <= i; ++j) {
            if (j * j == i) {
	        min = 1;
		break;
	    }
	    tmp = nums[i - j * j] + 1;
	    if (tmp < min)
	        min = tmp;
        }
        nums[i] = min;
    }
    min = nums[n];
    free(nums);
    return min;
}

int main() {
    int i = 0;
    for (i = 0; i < 101; ++i)
        printf("%d: %d\n", i, numSquares(i));
    printf("%d: %d\n", 4869, numSquares(4869));
    return 0;
}
