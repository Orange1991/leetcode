#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

/** 最大方形区域 */
int maximalSquare(char** matrix, int matrixRowSize, int matrixColSize) {
    int smaller(int, int);
    int i, j, k, max = 0, maxPossible, edge, edgeEnd;
    bool detectZero = false;
    // 尝试以matrix[i][j]为左上角构造方形区域
    for (i = 0; i < matrixRowSize - max; ++i) {
        for (j = 0; j < matrixColSize - max; ++j) {
            // 如果matrix[i][j]为0，不能构成方形区域
            if (*(*(matrix + i) + j) == '0') continue;
            // 计算以matrix[i][j]为左上角的方形区域的最大可能大小
            maxPossible = smaller(matrixRowSize - i, matrixColSize - j);
            // 如果此时最大可能值不会超过当前已经计算得到的最大值，则跳过
            if (maxPossible <= max) continue;
    
            // 尝试扩展边（一周）
            detectZero = false;
            for (edge = 1; edge < maxPossible; ++edge) {
                // 验证右边是否全为1（不包含右下角结点）
                edgeEnd = i + edge;
                for (k = i; k < edgeEnd; ++k)
                    if (*(*(matrix + k) + j + edge) == '0') {
                        detectZero = true; // 右边检测到0，扩展失败
                        break;    
                    }
                if (detectZero) break; // 右边验证失败，扩展失败
                // 验证下边是否全为1（包含右下角结点）
                edgeEnd = j + edge;
                for (k = j; k <= edgeEnd; ++k) {
                    if (*(*(matrix + i + edge) + k) == '0') {
                        detectZero = true; // 下边检测到0，扩展失败
                        break;    
                    }
                }
                if (detectZero) break; // 下边验证失败，扩展失败
            }

            // 尝试更新最大值
            if (max < edge) { max = edge; 
};
        }
    }
    
    return max * max;
}

/** 返回较小值 */
int smaller(int x, int y) { return x < y ? x : y; }

void test(char** matrix, int rows, int cols) {
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
    char* row1 = (char*)malloc(sizeof(char) * 5);
    char* row2 = (char*)malloc(sizeof(char) * 5);
    char* row3 = (char*)malloc(sizeof(char) * 5);
    char* row4 = (char*)malloc(sizeof(char) * 5);
    *row1 = '1'; *(row1 + 1) = '0'; *(row1 + 2) = '1';*(row1 + 3) = '0';*(row1 + 4) = '0';
    *row2 = '1'; *(row2 + 1) = '0'; *(row2 + 2) = '1';*(row2 + 3) = '1';*(row2 + 4) = '1';
    *row3 = '1'; *(row3 + 1) = '1'; *(row3 + 2) = '1';*(row3 + 3) = '1';*(row3 + 4) = '1';
    *row4 = '1'; *(row4 + 1) = '0'; *(row4 + 2) = '1';*(row4 + 3) = '1';*(row4 + 4) = '0';
    *matrix = row1;
    *(matrix + 1) = row2;
    *(matrix + 2) = row3;
    *(matrix + 3) = row4;
    test(matrix, 4, 5);

    *row1 = '1'; *(row1 + 1) = '1'; *(row1 + 2) = '0';*(row1 + 3) = '1';*(row1 + 4) = '0';
    *row2 = '0'; *(row2 + 1) = '1'; *(row2 + 2) = '1';*(row2 + 3) = '1';*(row2 + 4) = '1';
    *row3 = '1'; *(row3 + 1) = '1'; *(row3 + 2) = '1';*(row3 + 3) = '1';*(row3 + 4) = '0';
    *row4 = '1'; *(row4 + 1) = '1'; *(row4 + 2) = '1';*(row4 + 3) = '1';*(row4 + 4) = '1';
    test(matrix, 4, 5);

    char** matrix4 = (char**)malloc(sizeof(char *) * 6);
    char* row5 = (char*)malloc(sizeof(char) * 5);
    char* row6 = (char*)malloc(sizeof(char) * 5);
    *row5 = '0'; *(row5 + 1) = '0'; *(row5 + 2) = '0';*(row5 + 3) = '0';*(row5 + 4) = '0';
    *row6 = '0'; *(row6 + 1) = '1'; *(row6 + 2) = '1';*(row6 + 3) = '0';*(row6 + 4) = '1';
    *(matrix4 + 0) = row6;
    *(matrix4 + 1) = row1;
    *(matrix4 + 2) = row2;
    *(matrix4 + 3) = row3;
    *(matrix4 + 4) = row4;
    *(matrix4 + 5) = row5;
    test(matrix4, 6, 5);

    char** matrix2 = (char**)malloc(sizeof(char*) * 1); 
    char* row = (char*)malloc(sizeof(char) * 2);
    *row = '1';   
    *(row + 1) = '1';   
    *matrix2 = row;
    test(matrix2, 1, 2);

    char** matrix3 = (char**)malloc(sizeof(char*) * 2); 
    char *rows1 = (char*)malloc(sizeof(char) * 2);
    char *rows2 = (char*)malloc(sizeof(char) * 2);
    *rows1 = '0';
    *(rows1 + 1) = '1';
    *rows2 = '1';
    *(rows2 + 1) = '0';
    *matrix3 = rows1;
    *(matrix3 + 1) = rows2;
    test(matrix3, 2, 2);
    
    return 0;
}
