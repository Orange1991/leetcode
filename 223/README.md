#Leetcode 223 Rectangle Area 矩形区域面积

##原题地址
https://leetcode.com/problems/rectangle-area/

##题目描述
Find the total area covered by two rectilinear rectangles in a 2D plane.
计算两个矩形所在2D空间内覆盖的区域面积。

Each rectangle is defined by its bottom left corner and top right corner as shown in the figure.
每个矩形在图中由其左下角的顶点和右上角的顶点来定义。如下图：
![这里写图片描述](http://img.blog.csdn.net/20150828170905227)

Assume that the total area is never beyond the maximum possible value of int.
假设计算结果不超过int的最大值。

##解题思路
解题思路还是很简单的，先**分别计算两个矩形的面积并求和，然后减去矩形重合部分的面积**即可，因为重合部分被计算了两次。对于计算单个矩形的面积非常简单 `dx * dy`，剩下的问题就是求重合部分的面积了。

如何判断两个矩形有重合？如何计算重合部分面积？

**1. 判定重合**

对于以下四种情况，肯定无重合：
![这里写图片描述](http://img.blog.csdn.net/20150828172742196)
> - （1）如果矩形A的右上顶点的横坐标小于矩形B的左下角的横坐标
> - （2）如果矩形A的左下顶点的横坐标大于矩形B的右上角下角的横坐标
> - （3）如果矩形A的左下顶点的纵坐标大于矩形B的右上角的纵坐标
> - （4）如果矩形A的右上顶点的纵坐标小于矩形B的左下角的纵坐标

判定无重合的方法非常简单，无重合时直接返回重合部分面积为0。

**2. 有重合时求重合部分面积**

有重合时，大概如下：
![这里写图片描述](http://img.blog.csdn.net/20150828174427936)

简单描述就是：**在两个矩形的四个顶点中，分别把横纵坐标排序，然后分别取横纵坐标的中间两个数，其构成的矩形区域就是重合区域**。

有了如上两步，这个问题的解决就比较轻松了。

##代码

```
/**
 * 计算两个矩形覆盖的总面积
 */
int computeArea(int A, int B, int C, int D, int E, int F, int G, int H) {
    return (D - B) * (C - A) + (H - F) * (G - E) -
            computeRetainArea(A, B, C, D, E, F, G, H);
}

/**
 * 计算两个矩形重合区域面积
 */
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
```

> 完整代码 [https://github.com/Orange1991/leetcode/blob/master/223/c/main.c](https://github.com/Orange1991/leetcode/blob/master/223/c/main.c)

##测试数据

    -3,0,3,4,0,-1,9,2 : 45
    -2,-2,2,2,-2,-2,2,2 : 16
    0,0,0,0,-1,-1,1,1 : 4

##博文地址
http://blog.csdn.net/smile_watermelon/article/details/48055759

---
2015/8/28
