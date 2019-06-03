#include <stdio.h>// printf()

// I made them...
typedef int KeyType;
typedef int DataType;
#define MaxSize 100

////////////////////////////////////////////////////////////////////////////////
// Program 10.1
// P.169
typedef struct entry{
    KeyType key;
    DataType data;
}Entry;

typedef struct list{
    int n;
    Entry D[MaxSize];
}List;
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// P.171
void Swap(Entry* D, int i, int j)
{
    if(i == j)
        return;
    
    Entry temp = *(D + i);
    *(D + i) = *(D + j);
    *(D + j) = temp;
}
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Program 10.5
// P.178
int Partition(List* list, int low, int high)
{
    int i = low, j = high + 1;
    
    Entry pivot = list->D[low];
    
    do{
        do i++; while(list->D[i].key < pivot.key);
        do j--; while(list->D[j].key > pivot.key);
        
        if(i < j)
            Swap(list->D, i, j);
    }while(i < j);
    
    Swap(list->D, low, j);
    
    return j;
}

// Program 10.6
// P.179-180
// I renamed this function...
void _QuickSort(List *list, int low, int high)
{
    int k;
    
    if(low < high)
    {
        k = Partition(list, low, high);
        
        _QuickSort(list, low, k-1);
        _QuickSort(list, k+1, high);
    }
}

void QuickSort(List *list)
{
    _QuickSort(list, 0, list->n - 1);
}
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// main
int main(int argc, char **argv)
{
	List list;
    list.n = 0;
    for(int i=0; i<10; i++)
    {
        list.D[i].key = 10 - i;
        list.n++;
    }
    
    QuickSort(&list);
    
    for(int i=0; i<list.n; i++)
        printf("%d ", list.D[i].key);
    printf("\n");
    
	return 0;
}
