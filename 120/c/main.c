#include <stdio.h>
#include <stdlib.h>

int minimumTotal(int **triangle, int numRows) {
    int *minNums = (int *)malloc(sizeof(int) * numRows);
    int i, j;

    for (i = 0; i < numRows; ++i)
        *(minNums + i) = *(*(triangle + numRows - 1) + i);

    for (i = numRows - 2; i > -1; --i) {
        for (j = 0; j <= i; ++j)
            if (*(minNums + j) < *(minNums + j + 1))
                *(minNums + j) = *(*(triangle + i) + j) + *(minNums + j);
            else
                *(minNums + j) = *(*(triangle + i) + j) + *(minNums + j + 1);
   }

    i = *minNums;
    free(minNums);

    return i;
}

int main() {
    int *data1 = (int *)malloc(sizeof(int)),
        *data2 = (int *)malloc(sizeof(int) * 2),
        *data3 = (int *)malloc(sizeof(int) * 3),
        *data4 = (int *)malloc(sizeof(int) * 4);
    *data1 = 2;
    *data2 = 3; *(data2 + 1) = 4;
    *data3 = 6; *(data3 + 1) = 5; *(data3 + 2) = 7;
    *data4 = 4; *(data4 + 1) = 1; *(data4 + 2) = 8; *(data4 + 3) = 3;
    int **triangle = (int **)malloc(sizeof(int *) * 4);
    *triangle = data1; *(triangle + 1) = data2; 
    *(triangle + 2) = data3; *(triangle + 3) = data4;

    int min = minimumTotal(triangle, 4);
    printf("%d\n", min);

    return 0;
}
