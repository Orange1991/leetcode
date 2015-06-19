#ifndef BINARY_TREE_H
#define BINARY_TREE_H

#include <stdio.h>
#include <stdlib.h>

/**
 * 二叉树结点定义
 */
struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

void inorderTraversal(struct TreeNode *);  // 中序遍历
struct TreeNode* genBinaryTree(char *str); // 创建二叉树
void freeBinaryTree(struct TreeNode *);    // 回收二叉树内存

/**
 * 根据字符串构造二叉树
 * 除了数字/正负号/null/[]/逗号之外，不能有其他字符
 * 字符串可以以‘[’开始，以‘]’结束，且这两个字符只能出现在开头和结尾，也可以没有[]
 * 正负号不能连续出现，正负号之后必须跟一个数字
 * 多个数字之间用逗号分隔
 * 如果违反以上规则，返回NULL，否则返回一个树
 */
struct TreeNode* genBinaryTree(char *str) {
    if (str == NULL || *str == '\0') return NULL;
    if (*str == '[') ++str;
    int total = 128, cur = 0;
    struct TreeNode** nodes = (struct TreeNode**)malloc(sizeof(struct TreeNode*) * total);
		
    while (*str != '\0' && *str != ']') {
        int val = 0;
        int symbol = 1;
        int symbolFound = 0;
        int success = 0;
        int start = 0;
        int end = 0;
        while (!success) {
            switch (*str) {
                case '+':
                    if (symbolFound) return NULL; // 重复的正负号
                    symbolFound = 1;
                    break;
                case '-':
                    if (symbolFound) return NULL; // 重复的正负号
                    symbolFound = 1;
                    symbol = -1;
                    break;
                case '0':
                case '1':
                case '2':
                case '3':
                case '4':
                case '5':
                case '6':
                case '7':
                case '8':
                case '9':
                    val *= 10;
                    val += *str - '0';
                    if (!start) start = 1;
                    break;
                case 'n':
                   if (symbolFound || start
                           || *(str + 1) == '\0' || *(str + 1) == ']' 
                           || *(str + 2) == '\0' || *(str + 2) == ']'
                           || *(str + 3) == '\0' || *(str + 3) == ']')
                        return NULL;
                    if (*(str + 1) == 'u' && *(str + 2) == 'l' && *(str + 3) == 'l') {
                        if (cur >= total) {
                            total *= 2;
                            nodes = (struct TreeNode**)realloc(nodes, sizeof(struct TreeNode*) * total);    
                        }
                        *(nodes + cur++) = NULL;
                    } else return NULL;
                    if (*(str + 4) == ',') str += 4;
                    else str += 3;
                    break;
                case ',': // 一个新的数字构造结束
                    success = 1;
                    val *= symbol;
                    if (cur >= total) {
                        total *= 2;
                        nodes = (struct TreeNode**)realloc(nodes, sizeof(struct TreeNode*) * total);    
                    }
                    struct TreeNode* tmp1 = (struct TreeNode*)malloc(sizeof(struct TreeNode));
                    *(nodes + cur++) = tmp1;
                    tmp1->val = val;
                    break;
                case '\0':
                case ']': // 整个数据都构造结束
                    if (symbolFound && !start) return NULL; // 发现了正负号，但是没有数字就结束
                    if (start) {
                        val *= symbol;
                        if (cur >= total) {
                            total *= 2;
                            nodes = (struct TreeNode**)realloc(nodes, sizeof(struct TreeNode*) * total);    
                        }
                        struct TreeNode* tmp2 = (struct TreeNode*)malloc(sizeof(struct TreeNode));
                        *(nodes + cur++) = tmp2;
                        tmp2->val = val;
                    }
                    end = 1;
                    success = 1;
                    break;
                default: return NULL; // 非法字符
            }
            ++str;
        }	

        if (end) break;
    }

    total = cur;
    if (total == 0) {
        free(nodes);
        return NULL;
    }
    int left = 1, right = 2;
    for (cur = 0, left = 1, right = 2; cur < total;) {
        (*(nodes + cur))->left = left < total ? *(nodes + left) : NULL;
        (*(nodes + cur))->right = right < total ? *(nodes + right) : NULL;
        left += 2; right += 2; ++cur;
        while (cur < total && *(nodes + cur) == NULL) ++cur;
    }
   
    struct TreeNode *ret = *nodes;
    free(nodes);
    return ret;
}

/** 中序遍历 */
void inorderTraversal(struct TreeNode* root) {
    if (root == NULL) return;
    inorderTraversal(root->left);
    printf("%d, ", root->val);
    inorderTraversal(root->right);
}

/** 回收二叉树内存 */
void freeBinaryTree(struct TreeNode *root) {
    if (root == NULL) return;
    freeBinaryTree(root->left);
    freeBinaryTree(root->right);
    free(root);
}

#endif
