#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 5

typedef struct {
    int arr[MAX_SIZE];
    int front, rear, count;
} CircularQueue;

void init(CircularQueue *q) { q->front=0; q->rear=-1; q->count=0; }
int isFull(CircularQueue *q) { return q->count==MAX_SIZE; }
int isEmpty(CircularQueue *q) { return q->count==0; }

void enqueue(CircularQueue *q, int x, FILE *out) {
    if (isFull(q)) { fprintf(out, "Queue FULL\n"); return; }
    q->rear = (q->rear+1)%MAX_SIZE;
    q->arr[q->rear] = x; q->count++;
    fprintf(out, "Enqueued %d\n", x);
}

int dequeue(CircularQueue *q, FILE *out) {
    if (isEmpty(q)) { fprintf(out, "Queue EMPTY\n"); return -1; }
    int x = q->arr[q->front];
    q->front = (q->front+1)%MAX_SIZE; q->count--;
    fprintf(out, "Dequeued %d\n", x);
    return x;
}

void display(CircularQueue *q, FILE *out) {
    if (isEmpty(q)) { fprintf(out, "Queue EMPTY\n"); return; }
    fprintf(out, "Queue: ");
    for (int i=0; i<q->count; i++) {
        int idx = (q->front+i)%MAX_SIZE;
        fprintf(out, "%d ", q->arr[idx]);
    }
    fprintf(out, "\n");
}

int main() {
    FILE *in = fopen("input.txt", "r");
    FILE *out = fopen("output.txt", "w");
    
    CircularQueue q; init(&q);
    
    char op[10]; int x;
    while (fscanf(in, "%s", op) != EOF) {
        if (!strcmp(op, "ENQUEUE")) {
            fscanf(in, "%d", &x);
            enqueue(&q, x, out);
        } else if (!strcmp(op, "DEQUEUE")) {
            dequeue(&q, out);
        } else if (!strcmp(op, "DISPLAY")) {
            display(&q, out);
        }
    }
    
    fclose(in); fclose(out);
    return 0;
}
