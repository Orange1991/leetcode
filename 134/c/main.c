#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int canCompleteCircuit(int* gas, int gasSize, int* cost, int costSize) {
    if (gasSize <= 0) return -1;

    int *diff = (int *)malloc(sizeof(int) * gasSize), i;
    for (i = 0; i < gasSize; ++i) *(diff + i) = *(gas + i) - *(cost + i);
   
    if (gasSize == 1) return *diff >= 0 ? 0 : -1;

    int start = 0, end = 1, sum = *diff;
    bool overloop = false;
    while (start != end) {
        if (sum < 0) {
            if (overloop) return -1;
            start = end;
            end = end + 1;
            if (end >= gasSize) { 
                overloop = true;
                end %= gasSize;
            }
            sum = *(diff + start);
        } else {
            sum += *(diff + end);
            ++end;
            if (end == gasSize) overloop = true;
            end %= gasSize;
        }
    }

    return sum >= 0 ? start : -1;
}

int main() {
    int dataGas[] = {31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30}, 
        dataCost[] = {36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35};
//    int dataGas[] = {1, 2};
//    int dataCost[] = {2, 1};
    int n = sizeof(dataGas) / sizeof(int);

    int *gas = (int *)malloc(sizeof(int) * n);
    int *cost = (int *)malloc(sizeof(int) * n);
    int i;
    for (i = 0; i < n; ++i) {
        *(gas + i) = dataGas[i];
        *(cost + i) = dataCost[i];
    }

    printf("%d\n", canCompleteCircuit(gas, n, cost, n));
}
