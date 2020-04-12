// Added by Bo
#include <stdio.h>

// Added by Bo
typedef int KeyType;
// Useless though...
typedef char DataType;

// Added by Bo
#define MaxSize 20

// Program 10.1, p.186
typedef struct entry
{
    KeyType key;
    DataType data;
}Entry;

typedef struct list
{
    int n;
    Entry D[MaxSize];
}List;

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

// Program 10.5, p.195
int Partition(List *list, int low, int high)
{
    int i = low, j = high + 1;
    
    Entry pivot = list->D[low];
    
    do{
        do
        {
            i++;
        }while(i <= high && list->D[i].key < pivot.key);
        
        do
        {
            j--;
        }while(list->D[j].key > pivot.key);
        
        if(i < j)
            Swap(list->D, i, j);
    }while(i < j);
    
    Swap(list->D, low, j);
    
    return j;
}

// Program 10.6, p.196-197
void QuickSort2(List *list, int low, int high)
{
    int k;
    
    if(low < high)
    {
        k = Partition(list, low, high);
        
        QuickSort2(list, low, k - 1);
        
        QuickSort2(list, k + 1, high);
    }
}

void QuickSort(List *list)
{
    QuickSort2(list, 0, list->n - 1);
}

// Added by Bo
void OutputList(List *list, int n)
{
    for(int i = 0; i < n; i++)
        printf("%d\t", list->D[i].key);
    
    printf("\n");
}

// Added by Bo
int main(void)
{
    List list;
    
    // I want to show the results of Table 10.4, p.196
    list.n = 8;
    
    list.D[0].key = 24;
    list.D[1].key = 29;
    list.D[2].key = 45;
    list.D[3].key = 73;
    list.D[4].key = 24;
    list.D[5].key = 89;
    list.D[6].key = 90;
    list.D[7].key = 11;
    
    OutputList(&list, list.n);
    
    QuickSort(&list);
    
    OutputList(&list, list.n);
    
    return 0;
}
