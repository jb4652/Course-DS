// Added by Bo
#include <stdio.h>

// Added by Bo
typedef int KeyType;
// Useless though...
typedef char DataType;

// Added by Bo
#define MaxSize 20

// Added by Bo
#define TRUE 1
#define FALSE 0
typedef int BOOL;

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

// Program 10.4, p.192-193
typedef int BOOL;
void BubbleSort(List* list)
{
    int i, j;
    
    for(i = list->n - 1; i > 0; i--)
    {
        BOOL isSwap = FALSE;
        
        for(j = 0; j < i; j++)
        {
            if(list->D[j].key > list->D[j + 1].key)
            {
                Swap(list->D, j, j + 1);
                
                isSwap = TRUE;
            }
        }
        
        if(!isSwap)
            break;
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
    
    // I want to show the results of Table 10.3, p.192
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
    
    BubbleSort(&list);
    
    OutputList(&list, list.n);
    
    return 0;
}
