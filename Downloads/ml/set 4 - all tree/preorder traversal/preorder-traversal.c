#include <stdio.h>
#include <stdlib.h>

#define MAX_N 100

typedef struct Node{
    int data;
    int left;
    int right; 
} Node;

typedef struct Stack {
    int data[MAX_N];
    int top;
} Stack;

void push(Stack *s, int val) {
    if (s->top < MAX_N - 1)
        s->data[++s->top] = val;
}

int pop(Stack *s) {
    if (s->top >= 0)
        return s->data[s->top--];
    return -1;
}

int isEmpty(Stack *s) {
    return s->top == -1;
}

int main() {
    FILE *inputFile = fopen("input.txt", "r");
    if (!inputFile) return 1;

    FILE *outputFile = fopen("output.txt", "w");
    if (!outputFile) {
        fclose(inputFile);
        return 1;
    }

    int n; // number of nodes
    fscanf(inputFile, "%d", &n);

    Node tree[MAX_N];

    // Read node data: node_value left_index right_index (-1 if none)
    for (int i = 0; i < n; i++) {
        fscanf(inputFile, "%d %d %d", &tree[i].data, &tree[i].left, &tree[i].right);
    }
    fclose(inputFile);

    Stack stack;
    stack.top = -1;

    // Assume root is node 0
    push(&stack, 0);

    fprintf(outputFile, "Preorder traversal:\n");

    while (!isEmpty(&stack)) {
        int curr = pop(&stack);
        fprintf(outputFile, "%d ", tree[curr].data);

        // Push right child first, then left child to the stack
        if (tree[curr].right != -1)
            push(&stack, tree[curr].right);
        if (tree[curr].left != -1)
            push(&stack, tree[curr].left);
    }

    fprintf(outputFile, "\n");
    fclose(outputFile);
    return 0;
}
