// Added by Bo
#include <stdio.h>

// Added by Bo
typedef int KeyType;
// Useless though...
typedef char DataType;

// Added by Bo
#define MaxSize 20

// Program 10.1, partially, p.186
typedef struct entry
{
    KeyType key;
    DataType data;
}Entry;

// Program 10.9, partially, p.203
typedef struct maxheap
{
    int n;//, MaxSize;
    Entry D[MaxSize];
}MaxHeap;

// Program 5.11, partially, p.94
// This program is for MinHeap,
// and for MaxHeap, I made necessary modifications...
// Also modifications for data structure changes...
void AdjustDown(Entry heap[], int current, int border)
{
    int p = current;
    int maxChild;
    Entry temp;
    
    while(2*p+1 <= border)
    {
        if( (2*p+2 <= border) && (heap[2*p+1].key < heap[2*p+2].key) )
            maxChild = 2*p+2;
        else
            maxChild = 2*p+1;
        
        if(heap[p].key >= heap[maxChild].key)
            break;
        else
        {
            temp.key = heap[p].key; temp.data = heap[p].data;
            heap[p].key = heap[maxChild].key; heap[p].data = heap[maxChild].data;
            heap[maxChild].key = temp.key; heap[maxChild].data = temp.data;
            
            p = maxChild;
        }
    } 
}

// Program 10.2, p.188
void Swap(Entry *D, int i, int j)
{
    Entry temp;
    
    if(i == j)
        return;
    
    temp = *(D + i);
    *(D + i) = *(D + j);
    *(D + j) = temp;
}

// Program 10.9, partially, p.203
void HeapSort(MaxHeap *hp)
{
    int i;// Entry temp;
    
    for(i = (hp->n - 2) / 2; i >= 0; i--)
    {
        AdjustDown(hp->D, i, hp->n - 1);
    }
    
    for(i = hp->n - 1; i > 0; i--)
    {
        Swap(hp->D, 0, i);
        
        AdjustDown(hp->D, 0, i - 1);
    }
}

// Added by Bo
void OutputMaxHeap(MaxHeap *hp, int n)
{
    for(int i = 0; i < n; i++)
        printf("%d\t", hp->D[i].key);
    
    printf("\n");
}

// Added by Bo
int main(void)
{
    MaxHeap hp;
    
    // I want to show the results of Table 10.7, p.202-203
    hp.n = 8;
    
    hp.D[0].key = 24;
    hp.D[1].key = 29;
    hp.D[2].key = 45;
    hp.D[3].key = 73;
    hp.D[4].key = 24;
    hp.D[5].key = 89;
    hp.D[6].key = 90;
    hp.D[7].key = 11;
    
    OutputMaxHeap(&hp, hp.n);
    
    HeapSort(&hp);
    
    OutputMaxHeap(&hp, hp.n);
    
    printf("\n");
    
    // I want to show the results of Table 10.8, p.203-204
    hp.n = 5;
    
    hp.D[0].key = 24;
    hp.D[1].key = 29;
    hp.D[2].key = 45;
    hp.D[3].key = 24;
    hp.D[4].key = 73;
    
    OutputMaxHeap(&hp, hp.n);
    
    HeapSort(&hp);
    
    OutputMaxHeap(&hp, hp.n);
    
    return 0;
}
