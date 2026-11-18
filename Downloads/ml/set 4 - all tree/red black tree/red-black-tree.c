#include <stdio.h>
#include <stdlib.h>

typedef enum {RED, BLACK} Color;

typedef struct RBNode {
    int key;
    Color color;
    struct RBNode *left, *right, *parent;
} RBNode;

RBNode *NIL;

void initializeNIL() {
    NIL = malloc(sizeof(RBNode));
    NIL->color = BLACK;
    NIL->left = NIL->right = NIL->parent = NULL;
    NIL->key = 0;
}

RBNode* createNode(int key) {
    RBNode* node = malloc(sizeof(RBNode));
    node->key = key;
    node->color = RED;
    node->left = node->right = node->parent = NIL;
    return node;
}

RBNode* createTree() {
    initializeNIL();
    return NIL;
}

void leftRotate(RBNode **root, RBNode *x) {
    RBNode *y = x->right;
    x->right = y->left;
    if (y->left != NIL) y->left->parent = x;
    y->parent = x->parent;
    if (x->parent == NIL) *root = y;
    else if (x == x->parent->left) x->parent->left = y;
    else x->parent->right = y;
    y->left = x;
    x->parent = y;
}

void rightRotate(RBNode **root, RBNode *x) {
    RBNode *y = x->left;
    x->left = y->right;
    if (y->right != NIL) y->right->parent = x;
    y->parent = x->parent;
    if (x->parent == NIL) *root = y;
    else if (x == x->parent->right) x->parent->right = y;
    else x->parent->left = y;
    y->right = x;
    x->parent = y;
}

void fixInsert(RBNode **root, RBNode *z) {
    while (z->parent->color == RED) {
        if (z->parent == z->parent->parent->left) {
            RBNode *y = z->parent->parent->right;
            if (y->color == RED) {
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            } else {
                if (z == z->parent->right) {
                    z = z->parent;
                    leftRotate(root, z);
                }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                rightRotate(root, z->parent->parent);
            }
        } else {
            RBNode *y = z->parent->parent->left;
            if (y->color == RED) {
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            } else {
                if (z == z->parent->left) {
                    z = z->parent;
                    rightRotate(root, z);
                }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                leftRotate(root, z->parent->parent);
            }
        }
    }
    (*root)->color = BLACK;
}

void insertItem(RBNode **root, int key) {
    RBNode *z = createNode(key);
    RBNode *y = NIL;
    RBNode *x = *root;

    while (x != NIL) {
        y = x;
        if (z->key < x->key) x = x->left;
        else if (z->key > x->key) x = x->right;
        else { // Duplicate key, free node and return
            free(z);
            return;
        }
    }
    z->parent = y;

    if (y == NIL) *root = z;
    else if (z->key < y->key) y->left = z;
    else y->right = z;

    fixInsert(root, z);
}

RBNode* searchItem(RBNode *root, int key) {
    if (root == NIL || key == root->key)
        return (root == NIL) ? NULL : root;
    if (key < root->key) return searchItem(root->left, key);
    else return searchItem(root->right, key);
}

void deleteTreeHelper(RBNode *node) {
    if (node == NIL) return;
    deleteTreeHelper(node->left);
    deleteTreeHelper(node->right);
    free(node);
}

void deleteTree(RBNode *root) {
    if (root != NIL)
        deleteTreeHelper(root);
    free(NIL);
}

void inorderTraversal(RBNode* root, FILE* outputFile) {
    if (root != NIL) {
        inorderTraversal(root->left, outputFile);
        fprintf(outputFile, "%d ", root->key);
        inorderTraversal(root->right, outputFile);
    }
}

int main() {
    FILE *inputFile = fopen("input.txt", "r");
    if (!inputFile) return 1;

    FILE *outputFile = fopen("output.txt", "w");
    if (!outputFile) {
        fclose(inputFile);
        return 1;
    }

    RBNode *root = createTree();

    int n;
    fscanf(inputFile, "%d", &n);

    for (int i = 0; i < n; i++) {
        int key;
        fscanf(inputFile, "%d", &key);
        insertItem(&root, key);
    }

    fprintf(outputFile, "Inorder traversal after insertions:\n");
    inorderTraversal(root, outputFile);
    fprintf(outputFile, "\n\n");

    int num_search;
    fscanf(inputFile, "%d", &num_search);
    for (int i = 0; i < num_search; i++) {
        int key;
        fscanf(inputFile, "%d", &key);
        RBNode *res = searchItem(root, key);
        fprintf(outputFile, "Key %d %s found\n", key, res ? "is" : "is not");
    }

    // Delete operation not implemented here due to complexity; you can add if required

    deleteTree(root);
    fclose(inputFile);
    fclose(outputFile);
    return 0;
}
