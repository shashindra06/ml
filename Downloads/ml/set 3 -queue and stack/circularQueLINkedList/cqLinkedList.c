#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    int data; struct Node *next;
} Node;

typedef struct { Node *front, *rear; } CircularQueue;

void init(CircularQueue *q) { q->front=q->rear=NULL; }
int isEmpty(CircularQueue *q) { return q->front==NULL; }

void enqueue(CircularQueue *q, int x, FILE *out) {
    Node *n = (Node*)malloc(sizeof(Node)); n->data = x;
    if (isEmpty(q)) { n->next=n; q->front=q->rear=n; }
    else { n->next=q->front; q->rear->next=n; q->rear=n; }
    fprintf(out, "Enqueued %d\n", x);
}

int dequeue(CircularQueue *q, FILE *out) {
    if (isEmpty(q)) { fprintf(out, "Queue EMPTY\n"); return -1; }
    int x = q->front->data;
    if (q->front == q->rear) { free(q->front); q->front=q->rear=NULL; }
    else { Node *t=q->front; q->front=q->front->next; q->rear->next=q->front; free(t); }
    fprintf(out, "Dequeued %d\n", x); return x;
}

void display(CircularQueue *q, FILE *out) {
    if (isEmpty(q)) { fprintf(out, "Queue EMPTY\n"); return; }
    Node *t = q->front; fprintf(out, "Queue: ");
    do { fprintf(out, "%d ", t->data); t=t->next; } while (t != q->front);
    fprintf(out, "\n");
}

int main() {
    FILE *in = fopen("input.txt", "r");
    FILE *out = fopen("output.txt", "w");
    CircularQueue q; init(&q);
    
    char op[10]; int x;
    while (fscanf(in, "%s", op) == 1) {  // Fixed: ==1 instead of !=EOF
        if (!strcmp(op, "ENQUEUE")) { fscanf(in, "%d", &x); enqueue(&q, x, out); }
        else if (!strcmp(op, "DEQUEUE")) { dequeue(&q, out); }
        else if (!strcmp(op, "DISPLAY")) { display(&q, out); }
    }
    fclose(in); fclose(out);
    return 0;
}
