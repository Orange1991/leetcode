#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

/**
 * 二维数组中查找某元素
 * 查找成功返回ture，失败返回false
 * 二维数组每一行的数据递增，每一列的数据递增
 * @param matrix 二维数组
 * @param matrixRowSize 行数
 * @param matrixColSize 列数
 * @param target 查找对象
 */
bool searchMatrix(int** matrix, int matrixRowSize, int matrixColSize, int target) {
    // 从右上角开始查找
    int x = 0, y = matrixColSize - 1, diff;

    while (x < matrixRowSize && y > -1) {
        diff = *(*(matrix + x) + y) - target;
        if (diff == 0) return true; // 如果查找成功，直接返回true
        else if (diff > 0) --y;     // 如果当前元素比target大，在其左侧区域查找
        else ++x;                   // 如果当前元素比target小，在其下方区域查找
    }

    // 执行至此，说明查找失败
    return false;
}

int main() {
    int **matrix = (int **)malloc(sizeof(int *) * 5);
    int *line1 = (int *)malloc(sizeof(int) * 5);
    int *line2 = (int *)malloc(sizeof(int) * 5);
    int *line3 = (int *)malloc(sizeof(int) * 5);
    int *line4 = (int *)malloc(sizeof(int) * 5);
    int *line5 = (int *)malloc(sizeof(int) * 5);

    *line1 = 1; *(line1 + 1) = 4; *(line1 + 2) = 7; *(line1 + 3) = 11; *(line1 + 4) = 15;
    *line2 = 2; *(line2 + 1) = 5; *(line2 + 2) = 8; *(line2 + 3) = 12; *(line2 + 4) = 19;
    *line3 = 3; *(line3 + 1) = 6; *(line3 + 2) = 9; *(line3 + 3) = 16; *(line3 + 4) = 22;
    *line4 = 10; *(line4 + 1) = 13; *(line4 + 2) = 14; *(line4 + 3) = 17; *(line4 + 4) = 24;
    *line5 = 18; *(line5 + 1) = 21; *(line5 + 2) = 23; *(line5 + 3) = 26; *(line5 + 4) = 30;

    *matrix = line1; 
    *(matrix + 1) = line2; 
    *(matrix + 2) = line3;
    *(matrix + 3) = line4;
    *(matrix + 4) = line5;

    if (searchMatrix(matrix, 5, 5, 0)) 
        printf("Find 0.\n");
    else
        printf("Can't find 0.\n");

    if (searchMatrix(matrix, 5, 5, 18)) 
        printf("Find 18.\n");
    else
        printf("Can't find 18.\n");

    free(matrix);
    free(line1);
    free(line2);
    free(line3);
    free(line4);
    free(line5);
    return 0;
}
