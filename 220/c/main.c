#include <stdio.h>

bool containsNearbyAlmostDuplicate(int* nums, int numsSize, int k, int t) {
    if (numsSize < 2) return false;
    int min = max = *nums, i = 0;
    while (i++ < k) {
        if (*(nums + i) < min)
            min = *(nums + i);
        else if (*(nums + i) > max)
            max = *(nums + i);
    }

    

}
