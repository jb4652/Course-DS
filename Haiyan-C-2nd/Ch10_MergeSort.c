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

// Program 10.7, p.199
void Merge(List *list, Entry *temp, int low, int n1, int n2)
{
    int i = low, j = low + n1;
    
    while(i <= low + n1 - 1 && j <= low + n1 + n2 - 1)
    {
        if(list->D[i].key <= list->D[j].key)
            *temp++ = list->D[i++];
        else
            *temp++ = list->D[j++];
    }
    
    while(i <= low + n1 - 1)
        *temp++ = list->D[i++];
    
    while(j <= low + n1 + n2 - 1)
        *temp++ = list->D[j++];
}

// Program 10.8, p.200
void MergeSort(List *list)
{
    Entry temp[MaxSize];
    
    int low, n1, n2, i, size = 1;
    
    while(size < list->n)
    {
        low = 0;
        
        while(low + size < list->n)
        {
            n1 = size;
            
            if(low + size * 2 < list->n)
                n2 = size;
            else
                n2 = list->n - low - size;
            
            Merge(list, temp + low, low, n1, n2);
            
            low += n1 + n2;
        }
        
        for(i = 0; i < low; i++)
            list->D[i] = temp[i];
        
        size *= 2;
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
    
    // I want to show the results of Table 10.6, p.199
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
    
    MergeSort(&list);
    
    OutputList(&list, list.n);
    
    return 0;
}
