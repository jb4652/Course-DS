// Program 2.14, partially, p.19
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

// Program 2.14, partially, p.19
typedef int ElemType;

// Program 2.14, partially, p.19-20
typedef struct node
{
    ElemType element;
    struct node *link;
}Node;

// Program 2.14, partially, p.20
typedef struct singleList
{
    Node *first;
    int n;
}SingleList;

// Program 2.8, p.16
Status Init(SingleList *L)
{
    L->first = NULL;
    L->n = 0;
    
    return OK;
}

// Program 2.13, p.19
void Destroy(SingleList *L)
{
    Node *p;
    while(L->first)
    {
        p = L->first->link;
        free(L->first);
        L->first = p;
    }
}

// Program 2.9, p.16
Status Find(SingleList L, int i, ElemType *x)
{
    Node *p;
    
    int j;
    
    if(i<0 || i>L.n-1)
        return ERROR;
    
    p = L.first;
    for(j = 0; j < i; j++)
        p = p->link;
    
    *x = p->element;
    
    return OK;
}

// Program 2.10, p.17
Status Insert(SingleList *L, int i, ElemType x)
{
    Node *p, *q;
    
    int j;
    
    if(i<-1 || i>L->n-1)
        return ERROR;
    
    p = L->first;
    for(j = 0; j < i; j++)
        p = p->link;
    
    q = (Node*)malloc(sizeof(Node));
    q->element = x;
    
    if(i > -1)
    {
        q->link = p->link;
        p->link = q;
    }
    else
    {
        q->link = L->first;
        L->first = q;
    }
    
    L->n++;
    
    return OK;
}

// Program 2.11, p.18-19
Status Delete(SingleList *L, int i)
{
    int j;
    
    Node *p, *q;
    
    if(!L->n)
        return ERROR;
    
    if(i<0 || i>L->n-1)
        return ERROR;
    
    q = L->first;
    p = L->first;
    
    for(j = 0; j < i - 1; j++)
        q = q->link;
    
    if(i == 0)
    {
        L->first = L->first->link;
    }
    else
    {
        p = q->link;
        q->link = p->link;
    }
    
    free(p);
    
    L->n--;
    
    return OK;
}

// Program 2.12, p.19
Status Output(SingleList *L)
{
    Node *p;
    
    if(!L->n)
        return ERROR;
    
    p = L->first;
    while(p)
    {
        printf("%d ", p->element);
        p = p->link;
    }
    
    return OK;
}

// Program 2.14, partially, p.20
int main(int argc, char **argv)
{
    int i;
    int x;
    
    SingleList list;
    
    Init(&list);
    
    for(i = 0; i < 9; i++)
        Insert(&list, i-1, i);
        
    printf("The linklist is:");
    Output(&list);
    
    Delete(&list, 0);
    
    printf("\nThe linklist is:");
    Output(&list);
    
    Find(list, 0, &x);
    printf("\nThe first value is:");
    printf("%d \n", x);
    
    Destroy(&list);
	
	return 0;
}
