#include <stdio.h>
#include <stdlib.h>

typedef struct AVLNode {
    int key;
    struct AVLNode *left, *right;
    int height;
} AVLNode;

int height(AVLNode *N) {
    return N ? N->height : 0;
}

int max(int a, int b) {
    return (a > b) ? a : b;
}

AVLNode* createNode(int key) {
    AVLNode* node = (AVLNode*)malloc(sizeof(AVLNode));
    node->key = key;
    node->left = node->right = NULL;
    node->height = 1;
    return node;
}

AVLNode* rightRotate(AVLNode* y) {
    AVLNode* x = y->left;
    AVLNode* T2 = x->right;
    x->right = y;
    y->left = T2;
    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;
    return x;
}

AVLNode* leftRotate(AVLNode* x) {
    AVLNode* y = x->right;
    AVLNode* T2 = y->left;
    y->left = x;
    x->right = T2;
    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;
    return y;
}

int getBalance(AVLNode *N) {
    return N ? height(N->left) - height(N->right) : 0;
}

AVLNode* insertItem(AVLNode* node, int key) {
    if (!node) return createNode(key);

    if (key < node->key)
        node->left = insertItem(node->left, key);
    else if (key > node->key)
        node->right = insertItem(node->right, key);
    else return node;

    node->height = 1 + max(height(node->left), height(node->right));
    int balance = getBalance(node);

    if (balance > 1 && key < node->left->key)
        return rightRotate(node);

    if (balance < -1 && key > node->right->key)
        return leftRotate(node);

    if (balance > 1 && key > node->left->key) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    if (balance < -1 && key < node->right->key) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

AVLNode* minValueNode(AVLNode* node) {
    AVLNode* current = node;
    while (current && current->left)
        current = current->left;
    return current;
}

AVLNode* deleteItem(AVLNode* root, int key) {
    if (!root) return root;

    if (key < root->key)
        root->left = deleteItem(root->left, key);
    else if (key > root->key)
        root->right = deleteItem(root->right, key);
    else {
        if (!root->left || !root->right) {
            AVLNode* temp = root->left ? root->left : root->right;
            if (!temp) {
                temp = root;
                root = NULL;
            } else
                *root = *temp;
            free(temp);
        } else {
            AVLNode* temp = minValueNode(root->right);
            root->key = temp->key;
            root->right = deleteItem(root->right, temp->key);
        }
    }

    if (!root) return root;

    root->height = 1 + max(height(root->left), height(root->right));
    int balance = getBalance(root);

    if (balance > 1 && getBalance(root->left) >= 0)
        return rightRotate(root);

    if (balance > 1 && getBalance(root->left) < 0) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    if (balance < -1 && getBalance(root->right) <= 0)
        return leftRotate(root);

    if (balance < -1 && getBalance(root->right) > 0) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

int searchItem(AVLNode* root, int key) {
    if (!root) return 0;
    if (key == root->key) return 1;
    else if (key < root->key) return searchItem(root->left, key);
    else return searchItem(root->right, key);
}

void deleteTree(AVLNode* root) {
    if (!root) return;
    deleteTree(root->left);
    deleteTree(root->right);
    free(root);
}

AVLNode* createTree() {
    return NULL;
}

void inorderTraversal(AVLNode* root, FILE* outputFile) {
    if (root) {
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

    AVLNode* root = createTree();

    int n;
    fscanf(inputFile, "%d", &n);
    
    // Insert keys
    for (int i = 0; i < n; i++) {
        int key;
        fscanf(inputFile, "%d", &key);
        root = insertItem(root, key);
    }

    fprintf(outputFile, "Inorder traversal after insertions:\n");
    inorderTraversal(root, outputFile);
    fprintf(outputFile, "\n\n");

    // Search operations
    int num_search;
    fscanf(inputFile, "%d", &num_search);
    for (int i = 0; i < num_search; i++) {
        int key;
        fscanf(inputFile, "%d", &key);
        int found = searchItem(root, key);
        fprintf(outputFile, "Key %d %s found\n", key, found ? "is" : "is not");
    }

    // Delete operations
    int num_delete;
    fscanf(inputFile, "%d", &num_delete);
    for (int i = 0; i < num_delete; i++) {
        int key;
        fscanf(inputFile, "%d", &key);
        root = deleteItem(root, key);
    }

    fprintf(outputFile, "\nInorder traversal after deletions:\n");
    inorderTraversal(root, outputFile);
    fprintf(outputFile, "\n");

    deleteTree(root);
    fclose(inputFile);
    fclose(outputFile);
    return 0;
}
