#include <stdio.h>
#include <stdbool.h>

/**
 * Definition for singly-linked list.
 */
struct ListNode {
    int val;
    struct ListNode *next;
};

bool isPalindrome(struct ListNode* head) {
    // 空链表或者仅有一个结点
    if (head == NULL || head->next == NULL) return true;

    struct ListNode *slow = head, *fast = head->next, *cur;
    
    // 找到中间结点
    while (fast != NULL && fast->next != NULL) {
        slow = slow->next;
        fast = fast->next->next;
    }
    
    // 后半部分逆置
    cur = slow->next;
    slow = NULL;
    do {
        fast = cur->next;
        cur->next = slow;
        slow = cur;
        cur = fast;
    } while (cur != NULL);
    
    // 判断是否为回文
    fast = head;
    while (slow != NULL && fast != NULL) {
        if (slow->val != fast->val)
            return false;
        slow = slow->next;
        fast = fast->next;
    }
    return true;
}

void test(struct ListNode* list) {
    struct ListNode* tmp = list;
    while (tmp) {
        printf("%d->", tmp->val);
        tmp = tmp->next;
    }
    printf("NULL : ");
    if (isPalindrome(list))
        printf("is palindrome.\n");
    else
        printf("is not palindrome.\n");
}

int main() {
    struct ListNode n1, n2, n3, n4, n5;
    n1.val = 1; n2.val = 2; n3.val = 3; n4.val = 2; n5.val = 1;
    n1.next = &n2; n2.next = &n3; n3.next = &n4; n4.next = &n5; n5.next = NULL;
    test(&n1);
    n1.val = 1; n2.val = 2; n3.val = 3; n4.val = 3; n5.val = 1;
    n1.next = &n2; n2.next = &n3; n3.next = &n4; n4.next = &n5; n5.next = NULL;
    test(&n1);
    n1.val = 1; n2.val = 2; n3.val = 3; n4.val = 2; n5.val = 1;
    n1.next = &n2; n2.next = &n4; n4.next = &n5; n5.next = NULL;
    test(&n1);
    test(NULL);
    n1.next = NULL;
    test(&n1);
    n1.val = 1; n2.val = 1;
    n1.next = &n2; n2.next = NULL;
    test(&n1);
    n1.val = 1; n2.val = 2;
    n1.next = &n2; n2.next = NULL;
    test(&n1);
    return 0;
}
