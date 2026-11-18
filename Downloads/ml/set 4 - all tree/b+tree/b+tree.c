#include <stdio.h>
#include <stdlib.h>

#define MAX_KEYS 3

typedef struct BPlusNode {
    int n;
    int keys[MAX_KEYS];
    struct BPlusNode* C[MAX_KEYS + 1];
    struct BPlusNode* next;
    int leaf;
} BPlusNode;

BPlusNode* createTree() {
    BPlusNode* root = (BPlusNode*)malloc(sizeof(BPlusNode));
    root->leaf = 1;
    root->n = 0;
    root->next = NULL;
    return root;
}

void insertNonFull(BPlusNode* x, int k);
void splitChild(BPlusNode* x, int i);

void splitChild(BPlusNode* x, int i) {
    BPlusNode* z = (BPlusNode*)malloc(sizeof(BPlusNode));
    BPlusNode* y = x->C[i];
    z->leaf = y->leaf;
    z->n = MAX_KEYS/2;

    for (int j = 0; j < MAX_KEYS/2; j++)
        z->keys[j] = y->keys[j + MAX_KEYS/2 + 1];

    if (!y->leaf) {
        for (int j = 0; j <= MAX_KEYS/2; j++)
            z->C[j] = y->C[j + MAX_KEYS/2 + 1];
    } else {
        z->next = y->next;
        y->next = z;
    }

    for (int j = x->n; j >= i + 1; j--)
        x->C[j + 1] = x->C[j];

    x->C[i + 1] = z;

    for (int j = x->n - 1; j >= i; j--)
        x->keys[j + 1] = x->keys[j];

    x->keys[i] = y->keys[MAX_KEYS/2];
    x->n = x->n + 1;
    y->n = MAX_KEYS/2;
}

void insertNonFull(BPlusNode* x, int k) {
    int i = x->n - 1;
    if (x->leaf) {
        while (i >= 0 && k < x->keys[i])
            x->keys[i + 1] = x->keys[i--];
        x->keys[i + 1] = k;
        x->n = x->n + 1;
    } else {
        while (i >= 0 && k < x->keys[i])
            i--;
        i++;
        if (x->C[i]->n == MAX_KEYS)
            splitChild(x, i);
        insertNonFull(x->C[i], k);
    }
}

void insertItem(BPlusNode** root, int k) {
    BPlusNode* r = *root;
    if (r->n == MAX_KEYS) {
        BPlusNode* s = createTree();
        s->leaf = 0;
        s->C[0] = r;
        splitChild(s, 0);
        insertNonFull(s, k);
        *root = s;
    } else {
        insertNonFull(r, k);
    }
}

int searchItem(BPlusNode* x, int k) {
    int i = 0;
    while (i < x->n && k > x->keys[i])
        i++;
    if (i < x->n && k == x->keys[i])
        return 1;
    if (x->leaf)
        return 0;
    return searchItem(x->C[i], k);
}

void deleteTree(BPlusNode* node) {
    if (!node) return;
    if (!node->leaf) {
        for (int i = 0; i <= node->n; i++)
            deleteTree(node->C[i]);
    }
    free(node);
}

void inorderTraversal(BPlusNode* node, FILE* outputFile) {
    if (node) {
        int i;
        for (i = 0; i < node->n; i++) {
            if (!node->leaf)
                inorderTraversal(node->C[i], outputFile);
            fprintf(outputFile, "%d ", node->keys[i]);
        }
        if (!node->leaf)
            inorderTraversal(node->C[i], outputFile);
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

    BPlusNode* root = createTree();

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
        int found = searchItem(root, key);
        fprintf(outputFile, "Key %d %s found\n", key, found ? "is" : "is not");
    }

    deleteTree(root);
    fclose(inputFile);
    fclose(outputFile);
    return 0;
}
