#include <stdio.h>
#include <stdlib.h>

#define MAX_STACK 1000
#define MAX_SIZE 1000

typedef struct {
    int low, high;
} Segment;

void merge(int arr[], int left, int mid, int right, FILE *out) {
    int n1 = mid - left + 1, n2 = right - mid;
    int L[n1], R[n2];
    
    for (int i = 0; i < n1; i++) L[i] = arr[left + i];
    for (int j = 0; j < n2; j++) R[j] = arr[mid + 1 + j];
    
    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) arr[k++] = L[i++];
        else arr[k++] = R[j++];
    }
    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];
}

void iterativeMergeSort(int arr[], int n, FILE *out) {
    Segment stack[MAX_STACK];
    int top = -1;
    
    stack[++top] = (Segment){0, n - 1};
    
    while (top >= 0) {
        Segment curr = stack[top--];
        int low = curr.low, high = curr.high;
        
        if (low >= high) continue;
        
        int mid = low + (high - low) / 2;
        stack[++top] = (Segment){mid + 1, high};
        stack[++top] = (Segment){low, mid};
    }
    
    fprintf(out, "Sorted array: ");
    for (int i = 0; i < n; i++) fprintf(out, "%d ", arr[i]);
    fprintf(out, "\n");
}

int main() {
    FILE *in = fopen("input.txt", "r");
    FILE *out = fopen("output.txt", "w");
    
    int n;
    fscanf(in, "%d", &n);
    int arr[MAX_SIZE];
    
    fprintf(out, "Original: ");
    for (int i = 0; i < n; i++) {
        fscanf(in, "%d", &arr[i]);
        fprintf(out, "%d ", arr[i]);
    }
    fprintf(out, "\n");
    
    iterativeMergeSort(arr, n, out);
    
    fclose(in); fclose(out);
    return 0;
}
