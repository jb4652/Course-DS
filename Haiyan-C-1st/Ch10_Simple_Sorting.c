#include <stdio.h>// printf()

// I made it...
typedef int KeyType;
typedef int DataType;
#define MaxSize 100

// I made it...
typedef int BOOL;
#define TRUE 1
#define FALSE 0

////////////////////////////////////////////////////////////////////////////////
// Program 10.1
// P.169
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
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Select Sort
// Program 10.2
// P.170 - 171
int FindMin(List list, int startIndex)
{
    int i, minIndex = startIndex;
    for(i = startIndex + 1; i<list.n; i++)
    {
        if(list.D[i].key < list.D[minIndex].key)
            minIndex = i;
    }
    
    return minIndex;
}

void Swap(Entry* D, int i, int j)
{
    if(i == j) return;
    
    Entry temp = *(D + i);
    *(D + i) = *(D + j);
    *(D + j) = temp;
}

void SelectSort(List *list)
{
    int minIndex, startIndex = 0;
    while(startIndex < list->n - 1)
    {
        minIndex = FindMin(*list, startIndex);
        Swap(list->D, startIndex, minIndex);// Using Swap() in Program 10.2
        startIndex++;
    }
}
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Insert Sort
// Program 10.3
// P.173
void InsertSort(List *list)
{
    int i, j;
    for(i=1; i<list->n; i++)
    {
        Entry insertItem = list->D[i];
        for(j=i-1; j>=0; j--)
        {
            if(insertItem.key < list->D[j].key)
                list->D[j+1] = list->D[j];
            else
                break;
        }
        
        list->D[j+1] = insertItem;
    }
}
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Bubble Sort
// Program 10.4
// P.176
// I think the code in the textbook made a mistake for the position of: 
// BOOL isSwap = FALSE;
// So I move it to the inner loop...
void BubbleSort(List *list)
{
    int i, j;
    
    for(i=list->n - 1; i>0; i--)
    {
        BOOL isSwap = FALSE;
        
        for(j=0; j<i; j++)
        {
            if(list->D[j].key > list->D[j+1].key)
            {
                Swap(list->D, j, j+1);
                isSwap = TRUE;
            }
        }
        
        if(!isSwap) break;
    }
}
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Main
int main(int argc, char **argv)
{
    // Three lists for three simple sorting methods
    // list_1, list_2, list_3 are all {9, 8, 7, 6, 5, 4, 3, 2, 1, 0}
    List list_1, list_2, list_3;
    list_1.n = 10; list_2.n = 10; list_3.n = 10;
    for(int i=0; i<10; i++)
    {
        list_1.D[i].key = 10-i;
        list_2.D[i].key = 10-i;
        list_3.D[i].key = 10-i;
    }
    
    // Select Sort
    SelectSort(&list_1);
    printf("Select Sort: ");
    for(int i=0; i<10; i++)
    {
        printf("%d ", list_1.D[i].key);
    }
    printf("\n");
    
    // Insert Sort
    InsertSort(&list_2);
    printf("Insert Sort: ");
    for(int i=0; i<10; i++)
    {
        printf("%d ", list_2.D[i].key);
    }
    printf("\n");
    
    // Bubble Sort
    BubbleSort(&list_3);
    printf("Bubble Sort: ");
    for(int i=0; i<10; i++)
    {
        printf("%d ", list_3.D[i].key);
    }
    printf("\n");

	return 0;
}
