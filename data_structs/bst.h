#ifndef BST_H
#define BST_H

// CONCEPT: Binary Search Tree - efficient ordered data storage (Day 22/27)

typedef struct BSTNode {
    double data;
    struct BSTNode *left;
    struct BSTNode *right;
} BSTNode;

// CONCEPT: Double pointers for tree modification
BSTNode* bst_create_node(double data);
void bst_insert(BSTNode **root, double data);
BSTNode* bst_search(BSTNode *root, double data);
void bst_inorder(BSTNode *root, void (*callback)(double));
void bst_free(BSTNode *root);

#endif // BST_H
