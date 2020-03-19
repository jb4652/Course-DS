// Program 2.7, partially, p.14
#include <stdlib.h>
#include <stdio.h>

// Program 2.1, partially, p.11
#define ERROR 0
#define OK 1
#define Overflow 2
#define Underflow 3
#define NotPresent 4
#define Duplicate 5

// Program 2.1, partially, p.11
typedef int Status;

// Program 2.7, partially, p.14
typedef int ElemType;

// Program 2.7, partially, p.14
typedef struct seqList
{
    int n;
    int maxLength;
    ElemType *element;
}SeqList;

// Program 2.1, partially, p.11
Status Init(SeqList *L, int mSize)
{
    L->maxLength = mSize;
    L->n = 0;
    L->element = (ElemType*)malloc(sizeof(ElemType) * mSize);
    if(!L->element)
        return ERROR;
    
    return OK;
}

// Program 2.6, p.14
void Destroy(SeqList *L)
{
    L->n = 0;
    L->maxLength = 0;
    free(L->element);
}

// Program 2.2, p.11
Status Find(SeqList L, int i, ElemType *x)
{
    if(i<0 || i>L.n-1)
        return ERROR;
    
    *x = L.element[i];
    
    return OK;
}

// Program 2.3, p.12
Status Insert(SeqList *L, int i, ElemType x)
{
    int j;
    
    if(i<-1 || i>L->n-1)
        return ERROR;
    
    if(L->n == L->maxLength)
        return ERROR;
    
    for(j = L->n-1; j > i; j--)
        L->element[j+1] = L->element[j];
    
    L->element[i+1] = x;
    L->n = L->n + 1;
    
    return OK;
}

// Program 2.4, p.13
Status Delete(SeqList *L, int i)
{
    int j;
    
    if(i<0 || i>L->n-1)
        return ERROR;
    
    if(!L->n)
        return ERROR;
    
    for(j = i+1; j < L->n; j++)
        L->element[j-1] = L->element[j];
    
    L->n--;
    
    return OK;
}

// Program 2.5, p.13-14
Status Output(SeqList *L)
{
    int i;
    
    if(L->n == 0)
        return ERROR;
    
    for(i = 0; i <= L->n - 1; i++)
        printf("%d ", L->element[i]);
    
    printf("\n");
    
    return OK;
}

// Program 2.7, partially, p.14
int main(int argc, char **argv)
{
    int i;
    
    SeqList list;
    Init(&list, 10);
    
    for(i = 0; i < 10; i++)
        Insert(&list, i-1, i);
    Output(&list);
    
    Delete(&list, 0);
    Output(&list);
    
    Destroy(&list);
	
	return 0;
}
