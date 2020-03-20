// Added by Bo
#include <stdio.h>

// Added by Bo
typedef int ElemType;

// Added by Bo
void Output(ElemType heap[], int n)
{
    int i;
    
    for(i = 0; i < n; i++)
        printf("%d ", heap[i]);
    
    printf("\n");
}

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

// Here I made a little bit modifications inside the loop to output intermediate heap results
void CreateHeap(ElemType heap[], int n)
{
    int i;
    
    for(i = (n-2)/2; i > -1; i--)
    {
        AdjustDown(heap, i, n-1);
        
        Output(heap, n);
    }
}

// Added by Bo
int main(void)
{
    // Example for Table 5.1, p.95
    int h[] = {61, 28, 81, 43, 36, 47, 83, 5};
    int n = 8;
    
    Output(h, n);
    
    printf("\n");
    
    CreateHeap(h, n);
}
