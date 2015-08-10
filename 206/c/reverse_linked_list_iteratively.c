#include <stdio.h>

/** Definition for singly-linked list. */
struct ListNode {
    int val;
    struct ListNode *next;
};

struct ListNode* reverseList(struct ListNode* head) {
    if (head == NULL || head->next == NULL) return head;
    struct ListNode *pre = head, *center = head->next, *next;
    pre->next = NULL;
    while (center != NULL) {
        next = center->next; 
        center->next = pre;
        pre = center;
        center = next;
    }
    return pre;
}

int main() {
    struct ListNode n1, n2, n3, n4, n5;
    n1.val = 1; n1.next = &n2;
    n2.val = 2; n2.next = &n3;
    n3.val = 3; n3.next = &n4;
    n4.val = 4; n4.next = &n5;
    n5.val = 5; n5.next = NULL;
    struct ListNode* tmp = &n1;
    while (tmp) {
        printf("%d->", tmp->val);
        tmp = tmp->next;
    }
    printf("NULL\n");

    tmp = reverseList(&n1);
    while (tmp) {
        printf("%d->", tmp->val);
        tmp = tmp->next;
    }
    printf("NULL\n");
    return 0;
}
