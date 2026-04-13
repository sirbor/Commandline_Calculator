#include "data_structs/bst.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// CONCEPT: malloc() for dynamic node allocation
BSTNode* bst_create_node(const char *name, double data) {
    BSTNode *node = (BSTNode*)malloc(sizeof(BSTNode));
    if (node == NULL) {
        perror("Failed to allocate BST node");
        return NULL;
    }
    strncpy(node->name, name, 63);
    node->name[63] = '\0';
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    return node;
}

// CONCEPT: Double pointer to modify root pointer (Day 22)
void bst_insert(BSTNode **root, const char *name, double data) {
    if (*root == NULL) {
        *root = bst_create_node(name, data);
        return;
    }

    // CONCEPT: Recursive tree traversal using string comparison
    int cmp = strcmp(name, (*root)->name);
    if (cmp < 0) {
        bst_insert(&(*root)->left, name, data);
    } else if (cmp > 0) {
        bst_insert(&(*root)->right, name, data);
    } else {
        // Update existing variable
        (*root)->data = data;
    }
}

// CONCEPT: Recursive search in BST using string comparison
BSTNode* bst_search(BSTNode *root, const char *name) {
    if (root == NULL) return NULL;

    int cmp = strcmp(name, root->name);
    if (cmp == 0) return root;

    if (cmp < 0) {
        return bst_search(root->left, name);
    }
    return bst_search(root->right, name);
}

// CONCEPT: Function pointers for callback-based traversal (Day 23)
void bst_inorder(BSTNode *root, void (*callback)(const char*, double)) {
    if (root == NULL) return;

    bst_inorder(root->left, callback);
    callback(root->name, root->data);
    bst_inorder(root->right, callback);
}

// CONCEPT: Post-order traversal for safe memory deallocation
void bst_free(BSTNode *root) {
    if (root == NULL) return;
    
    bst_free(root->left);
    bst_free(root->right);
    free(root);
}
