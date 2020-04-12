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

// Program 10.2, p.187-188
int FindMin(List list, int startIndex)
{
    int i, minIndex = startIndex;
    
    for(i = startIndex + 1; i < list.n; i++)
    {
        if(list.D[i].key < list.D[minIndex].key)
        {
            minIndex = i;
        }
    }
    
    return minIndex;
}

void Swap(Entry *D, int i, int j)
{
    Entry temp;
    
    if(i == j)
        return;
    
    temp = *(D + i);
    *(D + i) = *(D + j);
    *(D + j) = temp;
}

void SelectSort(List* list)
{
    int minIndex, startIndex = 0;
    
    while(startIndex < list->n - 1)
    {
        minIndex = FindMin(*list, startIndex);
        
        Swap(list->D, startIndex, minIndex);
        
        startIndex++;
    }
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
    
    // I want to show the results of Table 10.1, p.187
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
    
    SelectSort(&list);
    
    OutputList(&list, list.n);
    
    return 0;
}
