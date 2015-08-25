#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

/** 最大方形区域 */
int maximalSquare(char** matrix, int matrixRowSize, int matrixColSize) {
    int i, j, k, max = 0, maxPossible, edge, edgeEnd;
    bool detectZero = false;
    // 尝试以matrix[i][j]为左上角构造方形区域
    for (i = 0; i < matrixRowSize; ++i) {
        for (j = 0; j < matrixColSize; ++j) {
            // 如果matrix[i][j]为0，不能构成方形区域
            if (*(*(matrix + i) + j) == '0') continue;

            // 计算以matrix[i][j]为左上角的方形区域的最大可能大小
            maxPossible = bigger(matrixRowSize - i, matrixColSize - j);
            // 如果此时最大可能值不会超过当前已经计算得到的最大值，则跳过
            if (maxPossible <= max) continue;
    
            // 尝试扩展边（一周）
            detectZero = false;
            for (edge = 1; edge < maxPossible; ++i) {
                edgeEnd = i + edge;
                // 验证右边是否全为1（不包含右下角结点）
                for (k = i; k < edgeEnd; ++k)
                    if (*(*(matrix + k) + edgeEnd) == '0') {
                        detectZero = true; // 右边检测到0，扩展失败
                        break;    
                    }
                if (detectZero) break; // 右边验证失败，扩展失败
                // 验证下边是否全为1（包含右下角结点）
                for (k = i; k <= edgeEnd; ++k)
                    if (*(*(matrix + edgeEnd) + k) == '0') {
                        detectZero = true; // 下边检测到0，扩展失败
                        break;    
                    }
                if (detectZero) break; // 下边验证失败，扩展失败
            }

            // 尝试更新最大值
            if (!detectZero) max = bigger(max, edge);
            else max = bigger(max, edge - 1);
        }
    }
    
    return max;
}

/** 返回较大值 */
int bigger(int x, int y) { return x > y ? x : y; }

void test(char** matrix, int rows, int cols) {
    if (rows <= 0 || cols <= 0) return;
    printf("[\n");
    int i, j;
    for (i = 0; i < rows - 1; ++i) {
        printf("    [");
        for (j = 0; j < cols - 1; ++j)
            printf("%c, ", *(*(matrix + i) + j));
        printf("%c],\n", *(*(matrix + i) + cols - 1));
    }
    printf("    [");
    for (j = 0; j < cols - 1; ++j)
        printf("%c, ", *(*(matrix + rows - 1) + j));
    printf("%c]\n]\n", *(*(matrix + rows - 1) + cols - 1));
    
    printf("Maximal Square Size is : %d", maximalSquare(matrix, rows, cols));
    printf("\n----------------------------------\n");
}

int main() {
    char** matrix = (char**)malloc(sizeof(char*) * 4);
    char row1[] = {'1', '0', '1', '0', '0'}; 
    char row2[] = {'1', '0', '1', '1', '1'}; 
    char row3[] = {'1', '1', '1', '1', '1'}; 
    char row4[] = {'1', '0', '0', '1', '0'}; 
    *matrix = row1;
    *(matrix + 1) = row2;
    *(matrix + 2) = row3;
    *(matrix + 3) = row4;
    test(matrix, 4, 5);
    return 0;
}
