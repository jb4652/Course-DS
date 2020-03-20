// Added by Bo
#include <stdlib.h>
#include <stdio.h>

// Added by Bo
#define TRUE 1
#define FALSE 0
// Program 5.14, partially, p.98
typedef int BOOL;

// Program 5.14, partially, p.98
typedef int ElemType;

// Program 5.11, p.94
void AdjustDown(ElemType heap[], int current, int border)
{
    int p = current;
    int minChild;
    ElemType temp;
    
    while(2*p+1 <= border)
    {
        if( (2*p+2 <= border) && (heap[2*p+1] > heap[2*p+2]) )
            minChild = 2*p+2;
        else
            minChild = 2*p+1;
        
        if(heap[p] <= heap[minChild])
            break;
        else
        {
            temp = heap[p];
            heap[p] = heap[minChild];
            heap[minChild] = temp;
            p = minChild;
        }
    } 
}

void CreateHeap(ElemType heap[], int n)
{
    int i;
    
    for(i = (n-2)/2; i > -1; i--)
        AdjustDown(heap, i, n-1);
}

// Program 5.13, p.97
void AdjustUp(ElemType heap[], int current)
{
    int p = current;
    ElemType temp;
    
    while(p > 0)
    {
        if(heap[p] < heap[(p-1)/2])
        {
            temp = heap[p];
            heap[p] = heap[(p-1)/2];
            heap[(p-1)/2] = temp;
            
            p = (p-1)/2;
        }
        else
            break;
    }
}

// Program 5.12, p.96
// Program 5.14, partially, p.98
typedef struct priorityQueue
{
    ElemType *elements;
    int n;
    int maxSize;
}PriorityQueue;

// Program 5.14, partially, p.98-99
void CreatePQ(PriorityQueue *PQ, int mSize)
{
    PQ->maxSize = mSize;
    PQ->n = 0;
    PQ->elements = (ElemType*)malloc(mSize * sizeof(ElemType));
}

void Destroy(PriorityQueue *PQ)
{
    free(PQ->elements);
    PQ->n = 0;
    PQ->maxSize = 0;
}

BOOL IsEmpty(PriorityQueue *PQ)
{
    if(PQ->n == 0)
        return TRUE;
    else
        return FALSE;
}

BOOL IsFull(PriorityQueue *PQ)
{
    if(PQ->n == PQ->maxSize)
        return TRUE;
    else
        return FALSE;
}

int Size(PriorityQueue *PQ)
{
    return PQ->n;
}

void Append(PriorityQueue *PQ, ElemType x)
{
    if(IsFull(PQ))
        return;
    
    PQ->elements[PQ->n] = x;
    PQ->n++;
    AdjustUp(PQ->elements, PQ->n - 1);
}

void Serve(PriorityQueue *PQ, ElemType *x)
{
    if(IsEmpty(PQ))
        return;
    
    *x = PQ->elements[0];
    PQ->n--;
    
    PQ->elements[0] = PQ->elements[PQ->n];
    AdjustDown(PQ->elements, 0, PQ->n - 1);
}

// Added by Bo
void Output(PriorityQueue *PQ)
{
    int i;
    
    for(i = 0; i < PQ->n; i++)
        printf("%d ", PQ->elements[i]);
        
    printf("\n");
}

// Added by Bo
int main(void)
{
    PriorityQueue pq;
    
    CreatePQ(&pq, 20);
    
    // Example for Table 5.2, p.99
    Append(&pq, 71); Output(&pq);
    Append(&pq, 74); Output(&pq);
    Append(&pq, 2); Output(&pq);
    Append(&pq, 72); Output(&pq);
    Append(&pq, 54); Output(&pq);
    Append(&pq, 93); Output(&pq);
    Append(&pq, 52); Output(&pq);
    Append(&pq, 28); Output(&pq);
    
    printf("\n");
    
    int x;
    Serve(&pq, &x); Output(&pq);
    Serve(&pq, &x); Output(&pq);
    
    Destroy(&pq);
}
