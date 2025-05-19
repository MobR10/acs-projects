#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *arr;
    int size;
    int capacity;
}MinHeap;

MinHeap* createHeap(int capacity){
    MinHeap* heap= (MinHeap*)malloc(sizeof(MinHeap));
    heap->capacity=capacity;
    heap->size=0;
    heap->arr=(int*)malloc((size_t)capacity*sizeof(int));
    return heap;
}

void heapify(MinHeap* heap, int idx){
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;
    int smallest = idx;

    if (left < heap->size && heap->arr[left] < heap->arr[smallest])
    {
        smallest = left;
    }
    if(right < heap->size && heap->arr[right] < heap->arr[smallest])
    {
        smallest = right;
    }
    if(smallest != idx)
    {
        int temp = heap->arr[idx];
        heap->arr[idx]=heap->arr[smallest];
        heap->arr[smallest]=temp;

        heapify(heap,smallest);
    }
}

int peek(MinHeap* heap)
{
    if(heap->size == 0)
    {
        printf("Heap-ul este gol!\n");
        return -1;
    }
    return heap->arr[0];
}

int extractMin(MinHeap* heap)
{
    if(heap->size == 0){
        printf("Heap-ul este gol!\n");
        return -1;
    }

    int root=heap->arr[0];

    heap->arr[0] = heap->arr[heap->size - 1];
    heap->size --;

    // se face heapify ca sa ramana heap-ul
    heapify(heap,0);
}

void insert(MinHeap* heap, int val){
    if(heap->size == heap->capacity){
        printf("Heap-ul este plin!\n");
        return;
    }

    heap->size++;
    int i=heap->size-1;

    heap->arr[i]=val;

    // aplicare heapify ca sa ramana proprietatea de heap
    while(i!=0 && heap->arr[i] < heap->arr[(i-1)/2])
    {
        int temp=heap->arr[i];
        heap->arr[i] = heap->arr[(i-1)/2];
        heap->arr[(i-1)/2] = temp;

        i=(i-1)/2;
    }
}

void freeHeap(MinHeap* heap)
{
    free(heap->arr);
    free(heap);
}

int main()
{

    MinHeap* heap=createHeap(10);
    int vector[10]={11,10,9,8,7,6,5,4,3,2};
    for(int i=0;i<10;i++)
        {
            insert(heap,vector[i]);
        }

    for(int i=0;i<10;i++)
        {
            vector[i]=heap->arr[i];
            printf("%d ",vector[i]);
        }
}   