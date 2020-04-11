// Added by Bo
#include <stdio.h>
#include <stdlib.h>

// Program 9.1, partially, p.156
#define ERROR 0
#define OK 1
#define Overflow 2
#define Underflow 3
#define NotPresent 4
#define Duplicate 5

typedef int Status;

// Added by Bo
typedef int ElemType;

// Program, p.158-159
typedef struct eNode
{
    int adjVex;
    ElemType w;
    struct eNode* nextArc;
}ENode;

typedef struct lGraph
{
    int n;
    int e;
    ENode **a;
}LGraph;

// Program 9.6, p.159
Status Init(LGraph *lg, int nSize)
{
    int i;
    
    lg->n = nSize;
    lg->e = 0;
    lg->a = (ENode**)malloc(nSize * sizeof(ENode*));
    if(!lg->a)
        return ERROR;
    else
    {
        for(i = 0; i < lg->n; i++)
            lg->a[i] = NULL;
        
        return OK;
    }
}

// Program 9.7, p.159-160
void Destroy(LGraph *lg)
{
    int i;
    
    ENode *p, *q;
    
    for(i = 0; i < lg->n; i++)
    {
        p = lg->a[i];
        q = p;
        while(p)
        {
            p = p->nextArc;
            free(q);
            q = p;
        }
    }
    
    free(lg->a);
}

// Program 9.8, p.160
Status Exist(LGraph *lg, int u, int v)
{
    ENode *p;
    
    if(u < 0 || v < 0 || u > lg->n - 1 || v > lg->n - 1 || u == v)
        return ERROR;
    
    p = lg->a[u];
    
    while(p && p->adjVex != v)
        p = p->nextArc;
    
    if(!p)
        return ERROR;
    else
        return OK;
}

// Program 9.9, p.160-161
// Please note that all nodes inserted to a single list are
// inserted at the front of the single list...
Status Insert(LGraph *lg, int u, int v, ElemType w)
{
    ENode *p;
    
    if(u < 0 || v < 0 || u > lg->n - 1 || v > lg->n - 1 || u == v)
        return ERROR;
    
    if(Exist(lg, u, v))
        return Duplicate;
    
    p = (ENode*)malloc(sizeof(ENode));
    p->adjVex = v;
    p->w = w;
    p->nextArc = lg->a[u];
    lg->a[u] = p;
    lg->e++;
    
    return OK;
}

// Program 9.10, p.161
Status Remove(LGraph *lg, int u, int v)
{
    ENode *p, *q;
    
    if(u < 0 || v < 0 || u > lg->n - 1 || v > lg->n - 1 || u == v)
        return ERROR;
    
    p = lg->a[u], q = NULL;
    
    while(p && p->adjVex != v)
    {
        q = p;
        p = p->nextArc;
    }
    
    if(!p) return NotPresent;
    
    if(q)
        q->nextArc = p->nextArc;
    else
        lg->a[u] = p->nextArc;
    
    free(p);
    lg->e--;
    
    return OK;
}

////////////////////////////////////////////////////////////////////////////////
// This part of codes is extracted from Ch03_SeqStack.c
// Please note that to avoid the function name confliction,
// I changed Destroy() here to DestroyStack()...

// Added by Bo
#define FALSE 0
#define TRUE 1
typedef int BOOL;

// Added by Bo
typedef int ElemType;

// Program 3.1, p.30-31
typedef struct stack
{
    int top;
    int maxSize;
    ElemType *element;
}Stack;

void Create(Stack *S, int mSize)
{
    S->maxSize = mSize;
    S->element = (ElemType*)malloc(sizeof(ElemType) * mSize);
    S->top = -1;
}

void DestroyStack(Stack *S)
{
    S->maxSize = 0;
    free(S->element);
    S->top = -1;
}

void Clear(Stack *S)
{
    S->top = -1;
}

BOOL IsEmpty(Stack *S)
{
    return S->top == -1;
}

BOOL IsFull(Stack *S)
{
    return S->top == S->maxSize - 1;
}

BOOL Top(Stack *S, ElemType *x)
{
    if(IsEmpty(S))
        return FALSE;
    
    *x = S->element[S->top];
    
    return TRUE;
}

BOOL Push(Stack *S, ElemType x)
{
    if(IsFull(S))
        return FALSE;
    
    S->top++;
    S->element[S->top] = x;
    
    return TRUE;
}

BOOL Pop(Stack *S)
{
    if(IsEmpty(S))
        return FALSE;
    
    S->top--;
    
    return TRUE;
}
////////////////////////////////////////////////////////////////////////////////

// Program 9.13, p.166-167
void Degree(int *inDegree, LGraph *g)
{
    int i;
    
    ENode *p;
    
    for(i = 0; i < g->n; i++)
        inDegree[i] = 0;
    
    for(i = 0; i < g->n; i++)
    {
        for(p = g->a[i]; p; p = p->nextArc)
        {
            inDegree[p->adjVex]++;
        }
    }
}

Status TopoSort(int *topo, LGraph *g)
{
    int i, j, k;
    
    ENode *p;
    
    Stack s;
    
    int *inDegree = (int*)malloc(sizeof(int) * g->n);
    
    Create(&s, g->n);
    
    Degree(inDegree, g);
    
    for(i = 0; i < g->n; i++)
    {
        if(!inDegree[i])
        {
            Push(&s, i);
        }
    }
    
    for(i = 0; i < g->n; i++)
    {
        if(IsEmpty(&s))
            return ERROR;
        else
        {
            Top(&s, &j);
            Pop(&s);
            
            topo[i] = j;
            
            printf("%d ", j);
            
            for(p = g->a[j]; p; p = p->nextArc)
            {
                k = p->adjVex;
                
                inDegree[k]--;
                
                if(!inDegree[k])
                {
                    Push(&s, k);
                }
            }
        }
    }
    
    return OK;
}

// Added by Bo
int main(void)
{
    LGraph lg;
    
    // TopoSort(LGraph) on Figure 9.15, p.165
    Init(&lg, 9);
    
    Insert(&lg, 0, 2, 0);
    Insert(&lg, 0, 7, 0);
    Insert(&lg, 1, 2, 0);
    Insert(&lg, 1, 4, 0);
    Insert(&lg, 2, 3, 0);
    Insert(&lg, 3, 5, 0);
    Insert(&lg, 3, 6, 0);
    Insert(&lg, 4, 3, 0);
    Insert(&lg, 4, 5, 0);
    Insert(&lg, 7, 8, 0);
    Insert(&lg, 8, 6, 0);
    
    int topo[9];
    TopoSort(topo, &lg);
    
    Destroy(&lg);
    
    printf("\n");
    
    return 0;
}
