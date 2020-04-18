// Added by Bo
#include <stdio.h>
#include <stdlib.h>
// For INFTY in Prim()
#include <limits.h>
#define INFTY INT_MAX

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

// Program 9.16, p.173
Status Prim(int k, int *closeVex, ElemType *lowWeight, LGraph g)
{
    ENode *p;
    
    int i, j;
    
    ElemType min;
    
    int *isMark = (int*)malloc(sizeof(int) * g.n);
    
    if(k < 0 || k > g.n - 1)
        return ERROR;
    
    for(i = 0; i < g.n; i++)
    {
        closeVex[i] = -1;
        
        lowWeight[i] = INFTY;
        
        isMark[i] = 0;
    }
    
    lowWeight[k] = 0;
    closeVex[k] = k;
    isMark[k] = 1;
    
    for(i = 1; i < g.n; i++)
    {
        for(p = g.a[k]; p; p = p->nextArc)
        {
            j = p->adjVex;
            
            if( (!isMark[j]) && (lowWeight[j] > p->w) )
            {
                lowWeight[j] = p->w;
                
                closeVex[j] = k;
            }
        }
        
        min = INFTY;
        
        for(j = 0; j < g.n; j++)
        {
            if( (!isMark[j]) && (lowWeight[j] < min) )
            {
                min = lowWeight[j];
                
                k = j;
            }
        }
        
        isMark[k] = 1;
    }
    
    for(i = 0; i < g.n; i++)
    {
        printf("%d ", closeVex[i]);
        printf("%d ", i);
        printf("%d ", lowWeight[i]);
        printf("\n");
    }
    
    return OK;
}

// Added by Bo
int main(void)
{
    LGraph lg;
    
    // Minimum Cost Spanning Tree - Prime (LGraph) on Figure 9.17, p.172
    
    Init(&lg, 6);
    
    Insert(&lg, 0, 1, 10);
    Insert(&lg, 0, 2, 7);
    Insert(&lg, 0, 5, 4);
    Insert(&lg, 1, 0, 10);
    Insert(&lg, 1, 4, 2);
    Insert(&lg, 2, 0, 7);
    Insert(&lg, 2, 3, 8);
    Insert(&lg, 2, 5, 6);
    Insert(&lg, 3, 2, 8);
    Insert(&lg, 3, 4, 9);
    Insert(&lg, 3, 5, 5);
    Insert(&lg, 4, 1, 2);
    Insert(&lg, 4, 3, 9);
    Insert(&lg, 4, 5, 7);
    Insert(&lg, 5, 0, 4);
    Insert(&lg, 5, 2, 6);
    Insert(&lg, 5, 3, 5);
    Insert(&lg, 5, 4, 7);
    
    // Start vertex
    int k;
    
    int *closeVex = (int*)malloc(sizeof(int) * lg.n);
    ElemType *lowWeight = (ElemType*)malloc(sizeof(ElemType) * lg.n);
    
    // Start vertex = 0
    k = 0;
    Prim(k, closeVex, lowWeight, lg);
    
    printf("\n");
    
    // Start vertex = 5
    k = 5;
    Prim(k, closeVex, lowWeight, lg);
    
    Destroy(&lg);
    
    return 0;
}
