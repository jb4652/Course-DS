#include <stdio.h>// printf()

////////////////////////////////////////////////////////////////////////////////
// I extended the code in Program 5.5 to support both max/min heap
// If you want to adjust to a max heap, leave this line uncomment
// if min heap, comment this line out
//#define MAX_HEAP

////////////////////////////////////////////////////////////////////////////////
// Program 5.5
// P.84
void AdjustHeap(int Heap[], int s, int m)
{
    int Temp = Heap[s];
    
    // Two errors in textbook:
    // 1. j is undefined so I added "int j = "
    // 2. To get the index of left child of s, j should be 2*s+1, 
    // rather than 2*s
    for(int j = 2*s+1; j<=m; j*=2)
    {
        
#ifdef MAX_HEAP// I want a max heap

        if(j<m && Heap[j]<Heap[j+1])
            j++;
        if(Temp > Heap[j])
            break;
            
#else// I want a min heap

        if(j<m && Heap[j+1]<Heap[j])
            j++;
        if(Temp < Heap[j])
            break;
            
#endif
        
        Heap[s] = Heap[j];
        s = j;
    }
    
    Heap[s] = Temp;
}

////////////////////////////////////////////////////////////////////////////////
// Program 5.6
// P.84 - 85
void CreateHeap(int heap[], int n)
{
    for(int i=(n-2)/2; i>=0; i--)
    {
        AdjustHeap(heap, i, n);
    }
}

////////////////////////////////////////////////////////////////////////////////
// main()
int main(int argc, char **argv)
{
    
#ifdef MAX_HEAP

    // Example in Fig 5.24 (P.83)
    int heap_fig524_max[100] = {42, 57, 87, 100, 50, 53, 43, 60, 58};
    CreateHeap(heap_fig524_max, 9);
    printf("Max heap in Fig 5.24: ");
    for(int i=0; i<9; i++)
        printf("%d ", heap_fig524_max[i]);
    printf("\n");
    
    // Example in Fig 5.25 (P.84)
    int heap_fig525_max[100] = {20, 18, 40, 60, 100};
    CreateHeap(heap_fig525_max, 5);
    printf("Max heap in Fig 5.25: ");
    for(int i=0; i<5; i++)
        printf("%d ", heap_fig525_max[i]);
    printf("\n");
    
#else
    
    // Example in Fig 5.24 (P.83)
    int heap_fig524_min[100] = {68, 57, 29, 27, 79, 53, 67, 44, 58};
    CreateHeap(heap_fig524_min, 9);
    printf("Min heap in Fig 5.24: ");
    for(int i=0; i<9; i++)
        printf("%d ", heap_fig524_min[i]);
    printf("\n");

#endif
	
	return 0;
}
