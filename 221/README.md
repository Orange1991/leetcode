#Leetcode 221 Maximal Square

##原题地址
http://leetcode.com/problems/maximal-square/

##题目描述
Given a 2D binary matrix filled with 0's and 1's, find the largest square containing all 1's and return its area.
给出一个2D的二进制矩阵，由0和1填充，找出最大的全部都是1的方形区域，并返回它的面积。

For example, given the following matrix:
例如，给出如下矩阵：

    1 0 1 0 0
    1 0 1 1 1
    1 1 1 1 1
    1 0 0 1 0

Return 
返回

    4
   
**Tag** `Dynamic Programming`

##解题思路
我们先来观察一个合法的区域有什么特点：

    1

    1  1
    1  1
    
    1  1  1
    1  1  1
    1  1  1

    1  1  1  1
    1  1  1  1
    1  1  1  1
    1  1  1  1

    ...

可以发现，假如我们以左上角为开始构造点，从第一个到第二个相当于在其右侧和下侧各加了一行`1`；从第二个到第三个相当于在其右侧和下侧各加了一行`1`；依次类推，因此，**当一个`n * n`的区域是合法区域时，要证明一个`(n+1) * (n+1)`的区域合法，只需要证明其右侧的边和下侧的边全由`1`构成即可**。

有了如上结论，我们只需遍历所有元素，以其为左上角的开始构造点，然后尝试构造最大合法区域即可。

详见代码。

##代码

```
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
```

需要说明的是，在遍历所有元素时，我们可以做一个优化。如果我们当前已经求得了临时的max，那么对于那些从matrix[i][j]到矩阵结尾的距离不够max的元素，以其为左上角元素能构造的最大合法区域肯定比max小，这时已经无需再计算，可以直接结束循环。即：

```
// 尝试以matrix[i][j]为左上角构造方形区域
for (i = 0; i < matrixRowSize - max; ++i) {
    for (j = 0; j < matrixColSize - max; ++j) {
        // ...
    }
}
```

> 完整代码 [https://github.com/Orange1991/leetcode/tree/master/221/c/s2.c](https://github.com/Orange1991/leetcode/tree/master/221/c/s2.c)

##测试数据

    [
        [1, 0, 1, 0, 0],
        [1, 0, 1, 1, 1],
        [1, 1, 1, 1, 1],
        [1, 0, 1, 1, 0]
    ]
    Maximal Square Size is : 4

    [
        [1, 1, 0, 1, 0],
        [0, 1, 1, 1, 1],
        [1, 1, 1, 1, 0],
        [1, 1, 1, 1, 1]
    ]    
    Maximal Square Size is : 9

    [
        [0, 1, 1, 0, 1],
        [1, 1, 0, 1, 0],
        [0, 1, 1, 1, 1],
        [1, 1, 1, 1, 0],
        [1, 1, 1, 1, 1],
        [0, 0, 0, 0, 0]
    ]
    Maximal Square Size is : 9

    [
        [1, 1]
    ]
    Maximal Square Size is : 1

    [
        [0, 1],
        [1, 0]
    ]
    Maximal Square Size is : 1

##博文地址
http://blog.csdn.net/smile_watermelon/article/details/48006593

---
2015/8/26
