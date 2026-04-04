#include "data_structs/bst.h"
#include <stdlib.h>
#include <stdio.h>

// CONCEPT: malloc() for dynamic node allocation
BSTNode* bst_create_node(double data) {
    BSTNode *node = (BSTNode*)malloc(sizeof(BSTNode));
    if (node == NULL) {
        perror("Failed to allocate BST node");
        return NULL;
    }
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    return node;
}

// CONCEPT: Double pointer to modify root pointer (Day 22)
void bst_insert(BSTNode **root, double data) {
    if (*root == NULL) {
        *root = bst_create_node(data);
        return;
    }
    
    // CONCEPT: Recursive tree traversal
    if (data < (*root)->data) {
        bst_insert(&(*root)->left, data);
    } else if (data > (*root)->data) {
        bst_insert(&(*root)->right, data);
    }
    // Duplicates are ignored
}

// CONCEPT: Recursive search in BST - O(log n) average case
BSTNode* bst_search(BSTNode *root, double data) {
    if (root == NULL || root->data == data) {
        return root;
    }
    
    if (data < root->data) {
        return bst_search(root->left, data);
    }
    return bst_search(root->right, data);
}

// CONCEPT: Function pointers for callback-based traversal (Day 23)
void bst_inorder(BSTNode *root, void (*callback)(double)) {
    if (root == NULL) return;
    
    bst_inorder(root->left, callback);
    callback(root->data);
    bst_inorder(root->right, callback);
}

// CONCEPT: Post-order traversal for safe memory deallocation
void bst_free(BSTNode *root) {
    if (root == NULL) return;
    
    bst_free(root->left);
    bst_free(root->right);
    free(root);
}
