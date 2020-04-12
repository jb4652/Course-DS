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

// Program 10.3, p.190
void InsertSort(List* list)
{
    int i, j;
    
    Entry insertItem;
    
    for(i = 1; i < list->n; i++)
    {
        insertItem = list->D[i];
        
        for(j = i - 1; j >= 0; j--)
        {
            if(insertItem.key < list->D[j].key)
                list->D[j + 1] = list->D[j];
            else
                break;
        }
        
        list->D[j + 1] = insertItem;
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
    
    // I want to show the results of Table 10.2, p.189-190
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
    
    InsertSort(&list);
    
    OutputList(&list, list.n);
    
    return 0;
}
