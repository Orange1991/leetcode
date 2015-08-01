#include <stdio.h>

struct ListNode {
    int val;
    struct ListNode *next;
};

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

int main() {
    struct ListNode n1, n2, n3, n4, n5, n6, n7, n8;
    n1.val = 2; n1.next = &n2;
    n2.val = 4; n2.next = &n3;
    n3.val = 5; n3.next = &n4;
    n4.val = 24; n4.next = &n5;
    n5.val = 45; n5.next = &n6;
    n6.val = 16; n6.next = &n7;
    n7.val = 7; n7.next = &n8;
    n8.val = -8; n8.next = NULL;
    
    struct ListNode* ret = sortList(&n1);
    while (ret) {
        printf("%d->", ret->val);
        ret = ret->next;
    }
    printf("\n");

    return 0;
}
