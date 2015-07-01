有一些公用的数据结构或者数据初始化算法，在这个文件夹里定义^_^

##TreeNode 二叉树
二叉树结点定义

    struct TreeNode {
        int val;
        struct TreeNode *left;
        struct TreeNode *right;
    };

###void inorderTraversal(struct TreeNode *) 中序遍历

###struct TreeNode* genBinaryTree(char *str) 创建二叉树
```
/**
 * 根据字符串构造二叉树
 * 除了数字/正负号/null/[]/逗号之外，不能有其他字符
 * 字符串可以以‘[’开始，以‘]’结束，且这两个字符只能出现在开头和结尾，也可以没有[]
 * 正负号不能连续出现，正负号之后必须跟一个数字
 * 多个数字之间用逗号分隔
 * 如果违反以上规则，返回NULL，否则返回一个树
 */
struct TreeNode* genBinaryTree(char *str);
```
###void freeBinaryTree(struct TreeNode *) 回收二叉树内存
