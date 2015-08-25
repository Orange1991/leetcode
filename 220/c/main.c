#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct Node {
    long long val;
    struct Node* pre;
    struct Node* next;
    struct Node* left;
    struct Node* right;
    struct Node* parent;
};

struct LinkedOrderedTree {
    int count;
    struct Node* head;
    struct Node* tail;
    struct Node* root;
};

bool containsNearbyAlmostDuplicate(int* nums, int numsSize, int k, int t) {
    void init(struct LinkedOrderedTree*, int);
    bool search(struct LinkedOrderedTree*, long long, long long);
    void pop(struct LinkedOrderedTree*);
    void add(struct LinkedOrderedTree*, long long);
    void freeLinkedOrderedTree(struct LinkedOrderedTree*);
    if (numsSize < 2 || k <= 0 || t < 0) return false;
    int i;
    bool contains = false;
    struct LinkedOrderedTree* tree = 
        (struct LinkedOrderedTree*)malloc(sizeof(struct LinkedOrderedTree));
    init(tree, *nums);
    long long from, to;
    for (i = 1; i < numsSize; ++i) {
        from = (long long)(*(nums + i)) - (long long)t;
        to = (long long)(*(nums + i)) + (long long)t + 1;
        // 查找有没有符合条件的值
        if (search(tree, from, to)) {
            contains = true;
            break;
        }
        if (tree->count >= k)  // 弹出超过范围k的值
            pop(tree);
        
        add(tree, (long long)*(nums + i)); // 添加新值
    }    
    // 释放内存
    freeLinkedOrderedTree(tree);
    return contains;
}

void init(struct LinkedOrderedTree* tree, int num) {
    tree->count = 1;
    tree->head = (struct Node*)malloc(sizeof(struct Node));
    tree->tail = (struct Node*)malloc(sizeof(struct Node));
    tree->root = (struct Node*)malloc(sizeof(struct Node));
    struct Node* tmp = (struct Node*)malloc(sizeof(struct Node));
    tree->root->left = tmp;
    tree->root->right = NULL; 
    tree->root->parent = NULL;
    tree->head->pre = NULL; 
    tree->head->next = tmp;
    tree->tail->pre = tmp;
    tree->tail->next = NULL;
    tmp->val = num;
    tmp->pre = tree->head;
    tmp->next = tree->tail;
    tmp->left = NULL;
    tmp->right = NULL;
    tmp->parent = tree->root;
}

bool search(struct LinkedOrderedTree* tree, long long from, long long to) {
    bool searchNode(struct Node*, long long, long long);
    if (tree->count <= 0) return false;
    return searchNode(tree->root->left, from, to);
}    

bool searchNode(struct Node* node, long long from, long long to) {
    if (node == NULL) return false;
    if (node->val >= from && node->val < to) {
        return true;
}
    if (node->val < from) return searchNode(node->right, from, to);
    else return searchNode(node->left, from, to);
}

void pop(struct LinkedOrderedTree* tree) {
    --tree->count;
    struct Node* tmp = tree->head->next;
    struct Node* parent = tmp->parent;
    if (tmp == NULL) return;
    tree->head->next = tmp->next;
    tmp->next->pre = tree->head;
    if (parent->left == tmp) {
        if (tmp->left == NULL) {
            parent->left = tmp->right;
            if (tmp->right != NULL) tmp->right->parent = parent;
        } else {
            parent->left = tmp->left;
            if (tmp->left != NULL)tmp->left->parent = parent;
            parent = parent->left;
            if (tmp->right != NULL) {
                // right 移至left的最右下角
                parent = parent->left;
                while (parent->right != NULL)
                    parent = parent->right;
                parent->right = tmp->right;
                tmp->right->parent = parent;
            }
        }
        free(tmp);
    } else if (parent->right == tmp) {
        if (tmp->right == NULL) {
            parent->right = tmp->left;
            if (tmp->left != NULL) tmp->left->parent = parent;
        } else {
            parent->right = tmp->right;
            if (tmp->right != NULL) tmp->right->parent = parent;
            if (tmp->left != NULL) {
                // left 移至right的最左下角
                parent = parent->right;
                while (parent->left != NULL)
                    parent = parent->left;
                parent->left = tmp->left;
                tmp->left->parent = parent;
            }
        }
        free(tmp);
    }
    
}
void add(struct LinkedOrderedTree* tree, long long num) {
    void addNode(struct LinkedOrderedTree*, struct Node*, long long);
    if (tree->count == 0) {
        tree->count = 1;
        struct Node* tmp = (struct Node*)malloc(sizeof(struct Node));
        tree->root->left = tmp;
        tree->head->next = tmp;
        tree->tail->pre = tmp;
        tmp->val = num;
        tmp->pre = tree->head;
        tmp->next = tree->tail;
        tmp->left = NULL;
        tmp->right = NULL;
        tmp->parent = tree->root;
    } else addNode(tree, tree->root->left, num);
}

void addNode(struct LinkedOrderedTree* tree, struct Node* node, long long num) {
    if (node->val > num)
        if (node->left == NULL) {
            struct Node* tmp = (struct Node*)malloc(sizeof(struct Node));
            node->left = tmp;
            tree->tail->pre->next = tmp;
            tmp->next = tree->tail;
            tmp->val = num;
            tmp->parent = node;
            tmp->pre = tree->tail->pre;
            tree->tail->pre = tmp;
            tmp->left = NULL;
            tmp->right = NULL;
            ++tree->count;
        } else addNode(tree, node->left, num);
    else
        if (node->right == NULL) {
            struct Node* tmp = (struct Node*)malloc(sizeof(struct Node));
            node->right = tmp;
            tree->tail->pre->next = tmp;
            tmp->next = tree->tail;
            tmp->val = num;
            tmp->parent = node;
            tmp->pre = tree->tail->pre;
            tree->tail->pre = tmp;
            tmp->left = NULL;
            tmp->right = NULL;
            ++tree->count;
        } else addNode(tree, node->right, num);
}

void freeLinkedOrderedTree(struct LinkedOrderedTree* tree) {
    struct Node* node = tree->head, *next = node->next;
    while (node != tree->tail) {
        free(node);
        node = next;
        next = node->next;
    }
    free(tree->tail);
    free(tree->root);
}

void test(int* nums, int numsSize, int k, int t) {
    if (numsSize < 1) return;
    printf("[");
    int i;
    for (i = 0; i < numsSize - 1; ++i)
        printf("%d,", nums[i]);
    printf("%d], k=%d, t=%d, ", nums[numsSize - 1], k, t);
    if (containsNearbyAlmostDuplicate(nums, numsSize, k, t))
        printf("there have nearby almost duplicate(s)\n");
    else
        printf("there have no nearby almost duplicate\n");
}

int main() {
    int nums[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    test(nums, 10, 3, 0);
    test(nums, 10, 3, 1);
    int nums1[] = {-1, -1};        
    test(nums1, 2, 1, 0);
    test(nums1, 2, 1, -1);
    int nums2[] = {-1, 2147483647};        
    test(nums2, 2, 1, 2147483647);
    int nums3[] = {1, 2};        
    test(nums3, 2, 0, 1);
    int nums4[] = {0,10,22,15,0,5,22,12,1,5}; 
    test(nums4, 10, 3, 3);
    test(nums4, 10, 3, 4);
    int nums5[] = {0,10,-1,15,-3,5,22,12,1,0}; 
    test(nums5, 10, 8, 0);
    return 0;
}
