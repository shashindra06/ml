#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

typedef struct {
    int arr[MAX];
    int front, rear, count;
} Queue;

void init(Queue *q) { q->front = 0; q->rear = -1; q->count = 0; }
int isEmpty(Queue *q) { return q->count == 0; }
int isFull(Queue *q) { return q->count == MAX; }
void enqueue(Queue *q, int x) {
    if (isFull(q)) return;
    q->rear = (q->rear + 1) % MAX;
    q->arr[q->rear] = x;
    q->count++;
}
int dequeue(Queue *q) {
    if (isEmpty(q)) return -1;
    int x = q->arr[q->front];
    q->front = (q->front + 1) % MAX;
    q->count--;
    return x;
}

typedef struct {
    Queue q1, q2;
} Stack;

void initStack(Stack *s) {
    init(&s->q1);
    init(&s->q2);
}

void push(Stack *s, int x, FILE* out) {
    // Move all from q1 to q2
    while (!isEmpty(&s->q1))
        enqueue(&s->q2, dequeue(&s->q1));
    
    enqueue(&s->q1, x);
    
    while (!isEmpty(&s->q2))
        enqueue(&s->q1, dequeue(&s->q2));
    
    fprintf(out, "Pushed %d\n", x);
}

int pop(Stack *s, FILE* out) {
    if (isEmpty(&s->q1)) {
        fprintf(out, "Stack empty\n");
        return -1;
    }
    int x = dequeue(&s->q1);
    fprintf(out, "Popped %d\n", x);
    return x;
}

int main() {
    Stack s; initStack(&s);
    FILE *in = fopen("input.txt", "r"), *out = fopen("output.txt", "w");
    char op[10];
    int val;
    while (fscanf(in, "%s", op) != EOF) {
        if (strcmp(op, "PUSH") == 0) {
            fscanf(in, "%d", &val);
            push(&s, val, out);
        } else if (strcmp(op, "POP") == 0) {
            pop(&s, out);
        }
    }
    fclose(in); fclose(out);
    return 0;
}
