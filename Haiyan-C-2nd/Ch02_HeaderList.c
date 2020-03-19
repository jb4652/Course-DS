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

// Program, p.20
typedef struct headerList
{
    Node *head;
    int n;
}HeaderList;

// Program 2.15, p.21
Status Init(HeaderList *h)
{
    h->head = (Node*)malloc(sizeof(Node));
    if(!h->head)
        return ERROR;
        
    h->head->link = NULL;
    h->n = 0;
    
    return OK;
}

// Program 2.13, p.19
// Modified by Bo
void Destroy(HeaderList *h)
{
    Node *p;
    while(h->head->link)
    {
        p = h->head->link->link;
        free(h->head->link);
        h->head->link = p;
    }
    
    // We don't need this head node neither...
    free(h->head);
}

// Program 2.9, p.16
// Modified by Bo
Status Find(HeaderList L, int i, ElemType *x)
{
    Node *p;
    
    int j;
    
    if(i<0 || i>L.n-1)
        return ERROR;
    
    p = L.head->link;
    for(j = 0; j < i; j++)
        p = p->link;
    
    *x = p->element;
    
    return OK;
}

// Program 2.16, p.21
Status Insert(HeaderList *h, int i, ElemType x)
{
    Node *p, *q;
    
    int j;
    
    if(i<-1 || i>h->n-1)
        return ERROR;
    
    p = h->head;
    for(j = 0; j <= i; j++)
        p = p->link;
    
    q = (Node*)malloc(sizeof(Node));
    q->element = x;
    
    q->link = p->link;
    p->link = q;
    
    h->n++;
    
    return OK;
}

// Program 2.17, p.21-22
Status Delete(HeaderList *h, int i)
{
    int j;
    
    Node *p, *q;
    
    if(!h->n)
        return ERROR;
    
    if(i<0 || i>h->n-1)
        return ERROR;
    
    q = h->head;
    
    for(j = 0; j < i; j++)
        q = q->link;
    
    p = q->link;
    q->link = p->link;
    
    free(p);
    
    h->n--;
    
    return OK;
}

// Program 2.12, p.19
// Modified by Bo
Status Output(HeaderList *h)
{
    Node *p;
    
    if(!h->n)
        return ERROR;
    
    p = h->head->link;
    while(p)
    {
        printf("%d ", p->element);
        p = p->link;
    }
    
    return OK;
}

// Program 2.14, partially, p.20
// Modified by Bo
int main(int argc, char **argv)
{
    int i;
    int x;
    
    HeaderList list;
    
    Init(&list);
    
    for(i = 0; i < 9; i++)
        Insert(&list, i-1, i);
        
    printf("The headerlist is:");
    Output(&list);
    
    Delete(&list, 0);
    
    printf("\nThe headerlist is:");
    Output(&list);
    
    Find(list, 0, &x);
    printf("\nThe first value is:");
    printf("%d \n", x);
    
    Destroy(&list);
	
	return 0;
}
