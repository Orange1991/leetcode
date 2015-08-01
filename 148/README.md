#Leetcode 148 Sort List 单链表排序

##原题链接
https://leetcode.com/problems/sort-list/

##题目描述
Sort a linked list in O(nlogn) time using constant space complexity.
在O(nlogn)时间复杂度和常数空间复杂度内对单链表进行排序。

##解题思路
在对数组的排序中，具有O(nlogn)时间复杂度的排序方式是**归并排序**和**快速排序**，这里也尝试使用此两种方式。在快速排序时，需要有两个指针分别从数据首尾向中间结点移动，这对单链表来说不很方便。因此这里首要考虑使用归并排序的方法。

在归并排序时，有一个比较关键的步骤是找到中间结点，在数组中找中间元素是很容易的，但是链表不具有随机访问的特性，为了找到中间结点不得不遍历整个链表，这里我们使用**快慢指针**的方法来获取中间结点，并把链表分为左右均等的两部分。

##算法描述
> 1. 找到单链表的中间结点，将链表分为两部分listA/listB
> 2. 对listA和listB分别调用归并排序
> 3. 对排序之后的listA和listB进行归并

##代码　c

```
/**
 * 单链表归并排序
 */
struct ListNode* sortList(struct ListNode* head) {
    struct ListNode* merge(struct ListNode*, struct ListNode*);

    if (head == NULL || head->next == NULL) return head;

    /* 将链表平分为两个链表 */
    struct ListNode first, *fast = &first, *slow = &first;
    first.next = head;
    while (fast->next && fast->next->next) {
        fast = fast->next->next;
        slow = slow->next;
    }
    struct ListNode* next = slow->next;
    slow->next = NULL;

    /* 对两个子链表分别调用归并排序 */
    struct ListNode* partOne = sortList(head);
    struct ListNode* partTwo = sortList(next);

    /* 对排好序的子链表进行归并 */
    return merge(partOne, partTwo);
}

/* 归并 */
struct ListNode* merge(struct ListNode* partOne, struct ListNode* partTwo) {
    struct ListNode *curOne = partOne, *curTwo = partTwo;
    struct ListNode head, *cur = &head;

    while (curOne && curTwo) {
        if (curOne->val < curTwo->val) {
            cur->next = curOne;
            cur = curOne;
            curOne = curOne->next;
        } else {
            cur->next = curTwo;
            cur = curTwo;
            curTwo = curTwo->next;
        }
    }
    while (curOne) {
        cur->next = curOne;
        cur = curOne;
        curOne = curOne->next;
    }
    while (curTwo) {
        cur->next = curTwo;
        cur = curTwo;
        curTwo = curTwo->next;
    }
    cur->next = NULL;

    return head.next;
}
```
> 完整代码[https://github.com/Orange1991/leetcode/blob/master/148/c/main.c](https://github.com/Orange1991/leetcode/blob/master/148/c/main.c)

##运行情况
| Language | Status | Time |
| :------- | : ---- | :--- |
| c        | Accept | 24ms |

##博文地址
http://blog.csdn.net/smile_watermelon/article/details/47187937

---
2015/8/1
