#include <stdio.h>
#include <stdlib.h>

/**
 * 获取第n个ugly数字
 */
int nthUglyNumber(int n) {
    void merge(long long*, int*, int, long long*, int*, long long*, int*, long long*, int*);
    if (n <= 6) return n;
    long long* ugly = (long long*)malloc(sizeof(long long) * 2 * n);
    long long* l2 = (long long*)malloc(sizeof(long long) * n);
    long long* l3 = (long long*)malloc(sizeof(long long) * n);
    long long* l5 = (long long*)malloc(sizeof(long long) * n);
    int count = 1, end = 0, p2 = 0, p3 = 0, p5 = 0;
    *ugly = 1;
    while (count < n) {
        while (end < count) {   // 尝试将已有的有序的ugly数字分别乘以2/3/5，来扩展ugly数字候选列表
            *(l2 + end) = *(ugly + end) * 2;    // 以*2的方式扩展
            *(l3 + end) = *(ugly + end) * 3;    // 以*3的方式扩展
            *(l5 + end) = *(ugly + end) * 5;    // 以*5的方式扩展
            ++end;
        }
        // 将备选列表中的数字进行有序归并
        merge(ugly, &count, end, l2, &p2, l3, &p3, l5, &p5);    
    }

    int ans = *(ugly + n - 1);
    free(ugly);
    free(l2);
    free(l3);
    free(l5);
    return ans;
}

/**
 * 将三个列表中的ugly数字有序的归并添加到ugly中
 */
void merge(long long* ugly, int* count, int end, long long* l2, int* p2, long long* l3, int* p3, long long* l5, int* p5) {
    long long max = *(l2 + end - 1);    // l2末尾元素，l2/l3/l5中小于此元素的均可以有序的添加到ugly中
    while (*p2 < end && *(l2 + *p2) <= max) 
        if (*(l2 + *p2) <= *(l3 + *p3) && *(l2 + *p2) <= *(l5 + *p5))  // l2中的当前结点最小
            if (*(l2 + *p2) == *(ugly + *count - 1)) (*p2)++;   // 略过重复元素
            else *(ugly + (*count)++) = *(l2 + (*p2)++);        // 从l2中添加下一个ugly数字
        else if (*(l3 + *p3) <= *(l5 + *p5))  // l3中的当前结点最小
            if (*(l3 + *p3) == *(ugly + *count - 1)) (*p3)++;   // 略过重复元素
            else *(ugly + (*count)++) = *(l3 + (*p3)++);        // 从l3中添加下一个ugly数字
        else     // l5中的当前结点最小
            if (*(l5 + *p5) == *(ugly + *count - 1)) (*p5)++;   // 略过重复元素
            else *(ugly + (*count)++) = *(l5 + (*p5)++);        // 从l5中添加下一个ugly数字
}

int main() {
    int i;
    for (i = 1; i < 101; ++i)
        printf("%d : %d\n", i, nthUglyNumber(i));
    printf("%d : %d\n", 1600, nthUglyNumber(1600));
    return 0;
}
