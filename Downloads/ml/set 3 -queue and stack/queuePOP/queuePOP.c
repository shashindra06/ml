#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

typedef struct {
    int arr[MAX];
    int top;
} Stack;

void init(Stack *s) { s->top = -1; }
int isEmpty(Stack *s) { return s->top == -1; }
void push(Stack *s, int x) { if (!isEmpty(s) || s->top < MAX -1) s->arr[++s->top] = x; }
int pop(Stack *s) { return isEmpty(s) ? -1 : s->arr[s->top--]; }

typedef struct {
    Stack s1, s2;
} Queue;

void initQueue(Queue *q) {
    init(&q->s1); init(&q->s2);
}

void enqueue(Queue *q, int x, FILE* out) {
    push(&q->s1, x);
    fprintf(out, "Enqueued %d\n", x);
}

void dequeue(Queue *q, FILE* out) {
    if (isEmpty(&q->s2)) {
        while (!isEmpty(&q->s1)) push(&q->s2, pop(&q->s1));
    }
    if (isEmpty(&q->s2)) {
        fprintf(out, "Queue is empty\n");
        return;
    }
    int x = pop(&q->s2);
    fprintf(out, "Dequeued %d\n", x);
}

int main() {
    Queue q; initQueue(&q);
    FILE *in = fopen("input.txt", "r"), *out = fopen("output.txt", "w");
    char op[10];
    int val;
    while (fscanf(in, "%s", op) != EOF) {
        if (strcmp(op, "ENQUEUE") == 0) {
            fscanf(in, "%d", &val);
            enqueue(&q, val, out);
        } else if (strcmp(op, "DEQUEUE") == 0) {
            dequeue(&q, out);
        }
    }
    fclose(in); fclose(out);
    return 0;
}
