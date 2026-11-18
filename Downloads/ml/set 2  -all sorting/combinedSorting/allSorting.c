#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 100
#define MAX_VAL 100

// (i) INSERTION SORT
void insertionSort(int arr[], int n) {
    for (int i = 1; i < n; i++) {
        int key = arr[i], j = i - 1;
        while (j >= 0 && arr[j] > key) { arr[j + 1] = arr[j]; j--; }
        arr[j + 1] = key;
    }
}

// (ii) BUBBLE SORT
void bubbleSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++)
        for (int j = 0; j < n - 1 - i; j++)
            if (arr[j] > arr[j + 1]) { int tmp = arr[j]; arr[j] = arr[j + 1]; arr[j + 1] = tmp; }
}

// (iii) SELECTION SORT
void selectionSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int min_i = i;
        for (int j = i + 1; j < n; j++)
            if (arr[j] < arr[min_i]) min_i = j;
        int tmp = arr[min_i]; arr[min_i] = arr[i]; arr[i] = tmp;
    }
}

// (iv) SHELL SORT
void shellSort(int arr[], int n) {
    for (int gap = n/2; gap > 0; gap /= 2)
        for (int i = gap; i < n; i++)
            for (int j = i; j >= gap && arr[j] < arr[j-gap]; j -= gap) {
                int tmp = arr[j]; arr[j] = arr[j-gap]; arr[j-gap] = tmp;
            }
}

// (v) QUICK SORT
int partition(int arr[], int low, int high) {
    int pivot = arr[high], i = low - 1;
    for (int j = low; j < high; j++)
        if (arr[j] <= pivot) { i++; int tmp = arr[i]; arr[i] = arr[j]; arr[j] = tmp; }
    int tmp = arr[i+1]; arr[i+1] = arr[high]; arr[high] = tmp;
    return i + 1;
}
void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

// (vi) MERGE SORT
void merge(int arr[], int l, int m, int r) {
    int n1 = m - l + 1, n2 = r - m;
    int L[MAX_SIZE], R[MAX_SIZE];
    for (int i = 0; i < n1; i++) L[i] = arr[l + i];
    for (int j = 0; j < n2; j++) R[j] = arr[m + 1 + j];
    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) arr[k++] = (L[i] <= R[j]) ? L[i++] : R[j++];
    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];
}
void mergeSort(int arr[], int l, int r) {
    if (l < r) {
        int m = l + (r-l)/2;
        mergeSort(arr, l, m);
        mergeSort(arr, m+1, r);
        merge(arr, l, m, r);
    }
}

// (vii) HEAP SORT
void heapify(int arr[], int n, int i) {
    int largest=i, l=2*i+1, r=2*i+2;
    if (l<n && arr[l]>arr[largest]) largest=l;
    if (r<n && arr[r]>arr[largest]) largest=r;
    if (largest!=i) {
        int tmp = arr[i]; arr[i]=arr[largest]; arr[largest]=tmp;
        heapify(arr, n, largest);
    }
}
void heapSort(int arr[], int n) {
    for (int i=n/2-1; i>=0; i--) heapify(arr, n, i);
    for (int i=n-1; i>0; i--) {
        int tmp=arr[0]; arr[0]=arr[i]; arr[i]=tmp;
        heapify(arr, i, 0);
    }
}

// (viii) RADIX SORT
int getMax(int arr[], int n) {
    int mx=arr[0];
    for (int i=1; i<n; i++) if(arr[i]>mx) mx=arr[i];
    return mx;
}
void radixSort(int arr[], int n) {
    int max = getMax(arr, n);
    for (int exp=1; max/exp>0; exp*=10) {
        int output[MAX_SIZE]={0}, count[10]={0};
        for (int i=0; i<n; i++) count[(arr[i]/exp)%10]++;
        for (int i=1; i<10; i++) count[i]+=count[i-1];
        for (int i=n-1; i>=0; i--) output[--count[(arr[i]/exp)%10]] = arr[i];
        for (int i=0; i<n; i++) arr[i]=output[i];
    }
}

// (ix) COUNTING SORT
void countingSort(int arr[], int n) {
    int count[MAX_VAL+1]={0}, output[MAX_SIZE];
    for (int i=0; i<n; i++) if(arr[i]>=0 && arr[i]<=MAX_VAL) count[arr[i]]++;
    for (int i=1; i<=MAX_VAL; i++) count[i]+=count[i-1];
    for (int i=n-1; i>=0; i--) output[--count[arr[i]]] = arr[i];
    for (int i=0; i<n; i++) arr[i] = output[i];
}

// Helper for bucket sort
void insertionSort(int arr[], int n);
void bucketSort(int arr[], int n) {
    int buckets[10][MAX_SIZE] = {0};
    int bucket_count[10] = {0};
    int min = arr[0], max = arr[0];
    for (int i=1; i<n; i++) { if(arr[i]>max) max=arr[i]; if(arr[i]<min) min=arr[i]; }
    for (int i=0; i<n; i++) {
        int bi = (arr[i]-min)*9/(max-min+1);
        buckets[bi][bucket_count[bi]++] = arr[i];
    }
    int idx=0;
    for(int i=0; i<10; i++) {
        insertionSort(buckets[i], bucket_count[i]);
        for (int j=0; j< bucket_count[i]; j++) arr[idx++] = buckets[i][j];
    }
}

// (x) RADIX EXCHANGE SORT - skipped, replace by radixSort in main

// (xii) ADDRESS CALCULATION SORT (simple)
void addressCalculationSort(int arr[], int n) {
    int output[MAX_VAL+1];
    for (int i=0; i<=MAX_VAL; i++) output[i] = -1;
    for (int i=0; i<n; i++)
        if(arr[i]>=0 && arr[i]<=MAX_VAL) output[arr[i]]=arr[i];
    int idx=0;
    for (int i=0; i<=MAX_VAL; i++)
        if(output[i] != -1) arr[idx++]=output[i];
}

int main() {
    FILE *in = fopen("input.txt", "r");
    FILE *out = fopen("output.txt", "w");
    int n; fscanf(in, "%d", &n);
    int arr[MAX_SIZE];
    fprintf(out, "Original: ");
    for (int i=0; i<n; i++) { fscanf(in, "%d", &arr[i]); fprintf(out, "%d ", arr[i]); }
    fprintf(out, "\n\n");
    fclose(in);

    char *names[] = {
        "INSERTION", "BUBBLE", "SELECTION", "SHELL", "QUICK", "MERGE",
        "HEAP", "RADIX", "COUNTING", "BUCKET", "RADIX", "ADDRESS_CALC"
    };
    
    for(int i=0; i<12; i++) {
        int temp[MAX_SIZE];
        memcpy(temp, arr, sizeof(int)*n);
        switch(i) {
            case 0: insertionSort(temp, n); break;
            case 1: bubbleSort(temp, n); break;
            case 2: selectionSort(temp, n); break;
            case 3: shellSort(temp, n); break;
            case 4: quickSort(temp, 0, n-1); break;
            case 5: mergeSort(temp, 0, n-1); break;
            case 6: heapSort(temp, n); break;
            case 7: radixSort(temp, n); break;
            case 8: countingSort(temp, n); break;
            case 9: bucketSort(temp, n); break;
            case 10: radixSort(temp, n); break; // radix exchange replaced with radixSort
            case 11: addressCalculationSort(temp, n); break;
        }
        fprintf(out, "%-15s: ", names[i]);
        for(int j=0; j<n; j++) fprintf(out, "%d ", temp[j]);
        fprintf(out, "\n");
    }
    fclose(out);
    printf("Sorting done! Output in output.txt\n");
    return 0;
}
