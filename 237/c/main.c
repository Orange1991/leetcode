#include <stdio.h>
#include <stdlib.h>

/**
 * Definition for singly-linked list.
 */
struct ListNode {
    int val;
    struct ListNode *next;
};

void deleteNode(struct ListNode* node) {
    struct ListNode* nextNode = node->next;
    node->val = nextNode->val;
    node->next = nextNode->next;
    free(nextNode);
}

void print(struct ListNode* node) {
    while (node) {
        printf("%d->", node->val);
        node = node->next;
    }
    printf("NULL\n");
}

void freeTree(struct ListNode* node) {
    struct ListNode* tmp;
    while (node) {
        tmp = node->next;
        free(node);
        node = tmp;
    }
}

int main() {
    struct ListNode* n1, *n2, *n3, *n4;
    n1 = (struct ListNode*)malloc(sizeof(struct ListNode));
    n2 = (struct ListNode*)malloc(sizeof(struct ListNode));
    n3 = (struct ListNode*)malloc(sizeof(struct ListNode));
    n4 = (struct ListNode*)malloc(sizeof(struct ListNode));
    n1->val = 1; n1->next = n2;
    n2->val = 2; n2->next = n3;
    n3->val = 3; n3->next = n4;
    n4->val = 4; n4->next = NULL;
    print(n1);
    deleteNode(n3);
    print(n1);
    freeTree(n1);
    return 0;
}
