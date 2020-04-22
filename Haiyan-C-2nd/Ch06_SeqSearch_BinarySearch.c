// Added by Bo
#include <stdio.h>
#include <stdlib.h>
// For MaxNum in Search4()
#include <limits.h>
#define MaxNum INT_MAX

// Added by Bo
typedef int ElemType;

// Program, p.109
typedef struct
{
    int n;
    int maxLength;
    ElemType *element;
}listSet;

// Added by Bo
// Can not be "listSet L", must be "listSet *L"
void Init(listSet *L, int mSize)
{
    L->n = 0;
    L->maxLength = mSize;
    L->element = (ElemType*)malloc(L->maxLength * sizeof(ElemType));
}

// Added by Bo
void Destroy(listSet L)
{
    L.n = 0;
    L.maxLength = -1;
    free(L.element);
}

// Program 6.1, p.110
// Program, Slides 6.2, p.8
// Sequential search on unordered list
int Search(listSet L, ElemType x)
{
    int i;
    
    for(i = 0; i < L.n; i++)
    {
        if(L.element[i] == x)
            return i;
    }
    
    return -1;
}

// Program 6.2, p.111
// Sequential search on ordered list
int Search2(listSet L, ElemType x)
{
    int i;
    
    for(i = 0; L.element[i] < x; i++);// Please note the ";" here...
    
    if(L.element[i] == x)
        return i;
    
    return -1;
}

// Program, Slides 6.2, p.8
// Sequential search on ordered list
int Search3(listSet L, ElemType x)
{
    int i;
    
    for(i = 0; i < L.n; i++)
    {
        if(L.element[i] == x)
            return i;
        else if(L.element[i] > x)
            return -1;
    }
    
    return -1;
}

// Program, Slides 6.2, p.9
// Sequential search on ordered list
int Search4(listSet L, ElemType x)
{
    int i;
    
    L.element[L.n] = MaxNum;
    
    for(i = 0; L.element[i] < x; i++);// Please note the ";" here...
    
    if(L.element[i] == x)
        return i;
    
    return -1;
}

// Program 6.3, p.113
int binSearch(listSet L, ElemType x, int low, int high)
{
    if(low <= high)
    {
        int m = (low + high) / 2;
        if(x < L.element[m])
            return binSearch(L, x, low, m - 1);
        else if(x > L.element[m])
            return binSearch(L, x, m + 1, high);
        else
            return m;
    }
    
    return -1;
}

// Program 6.4, p.113
int binSearch2(listSet L, ElemType x)
{
    int m, low = 0, high = L.n - 1;
    
    while(low <= high)
    {
        m = (low + high) / 2;
        
        if(x < L.element[m])
            high = m - 1;
        else if(x > L.element[m])
            low = m + 1;
        else
            return m;
    }
    
    return -1;
}

// Added by Bo
void Output(listSet L)
{
    for(int i = 0; i < L.n; i++)
    {
        printf("%d ", L.element[i]);
    }
    
    printf("\n");
}

// Added by Bo
int main(void)
{
    int x;
    
    listSet L;
    
    Init(&L, 10);
    L.n = 10;
    
    // An example of unordered list
    L.element[0] = 8;
    L.element[1] = 1;
    L.element[2] = 3;
    L.element[3] = 6;
    L.element[4] = 7;
    L.element[5] = 2;
    L.element[6] = 5;
    L.element[7] = 4;
    L.element[8] = 10;
    L.element[9] = 9;
    
    Output(L);
    
    x = 4;
    if(Search(L, x) != -1)
        printf("I find %d in the list\n", x);
    else
        printf("I can not find %d in the list\n", x);
    
    x = 11;
    if(Search(L, x) != -1)
        printf("I find %d in the list\n", x);
    else
        printf("I can not find %d in the list\n", x);
    
    printf("\n");
    
    // An example of ordered list
    L.element[0] = 1;
    L.element[1] = 2;
    L.element[2] = 3;
    L.element[3] = 4;
    L.element[4] = 5;
    L.element[5] = 6;
    L.element[6] = 7;
    L.element[7] = 8;
    L.element[8] = 9;
    L.element[9] = 10;
    
    Output(L);
    
    x = 8;
    if(Search2(L, x) != -1)
        printf("I find %d in the list\n", x);
    else
        printf("I can not find %d in the list\n", x);
    
    x = 11;
    if(Search2(L, x) != -1)
        printf("I find %d in the list\n", x);
    else
        printf("I can not find %d in the list\n", x);
    
    
    x = 8;
    if(Search3(L, x) != -1)
        printf("I find %d in the list\n", x);
    else
        printf("I can not find %d in the list\n", x);
    
    x = 11;
    if(Search3(L, x) != -1)
        printf("I find %d in the list\n", x);
    else
        printf("I can not find %d in the list\n", x);
        
    x = 8;
    if(Search4(L, x) != -1)
        printf("I find %d in the list\n", x);
    else
        printf("I can not find %d in the list\n", x);
    
    x = 11;
    if(Search4(L, x) != -1)
        printf("I find %d in the list\n", x);
    else
        printf("I can not find %d in the list\n", x);
    
    printf("\n");
    
    // Binary search on Figure 6.1, p.112-113
    L.element[0] = 10;
    L.element[1] = 31;
    L.element[2] = 36;
    L.element[3] = 41;
    L.element[4] = 54;
    L.element[5] = 55;
    L.element[6] = 65;
    L.element[7] = 72;
    L.element[8] = 83;
    L.element[9] = 99;
    
    Output(L);
    
    x = 65;
    if(binSearch(L, x, 0, L.n - 1) != -1)
        printf("I find %d in the list\n", x);
    else
        printf("I can not find %d in the list\n", x);
    
    x = 34;
    if(binSearch(L, x, 0, L.n - 1) != -1)
        printf("I find %d in the list\n", x);
    else
        printf("I can not find %d in the list\n", x);
        
    x = 65;
    if(binSearch2(L, x) != -1)
        printf("I find %d in the list\n", x);
    else
        printf("I can not find %d in the list\n", x);
    
    x = 34;
    if(binSearch2(L, x) != -1)
        printf("I find %d in the list\n", x);
    else
        printf("I can not find %d in the list\n", x);
    
    Destroy(L);
    
    return 0;
}
