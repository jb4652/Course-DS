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

// Program 9.11, p.163
void DFS(int v, int visited[], LGraph g)
{
    ENode *w;
    
    printf("%d ", v);
    
    visited[v] = 1;
    
    for(w = g.a[v]; w; w = w->nextArc)
    {
        if(!visited[w->adjVex])
        {
            DFS(w->adjVex, visited, g);
        }
    }
}

void DFSGraph(LGraph g)
{
    int i;
    
    int *visited = (int*)malloc(g.n * sizeof(int));
    
    for(i = 0; i < g.n; i++)
    {
        visited[i] = 0;
    }
    
    for(i = 0; i < g.n; i++)
    {
        if(!visited[i]) DFS(i, visited, g);
    }
    
    free(visited);
}

// Added by Bo
int main(void)
{
    LGraph lg;
    
    // DFS(LGraph) on Figure 9.1(b), p.151
    
    Init(&lg, 4);
    
    Insert(&lg, 0, 1, 0);
    Insert(&lg, 0, 2, 0);
    Insert(&lg, 1, 3, 0);
    Insert(&lg, 2, 1, 0);
    Insert(&lg, 3, 2, 0);
    
    DFSGraph(lg);
    
    Destroy(&lg);
    
    printf("\n");
    
    // DFS(LGraph) on Figure 9.13(a), p.162
    Init(&lg, 6);
    
    Insert(&lg, 0, 1, 0);
    Insert(&lg, 1, 2, 0);
    Insert(&lg, 1, 3, 0);
    Insert(&lg, 2, 0, 0);
    Insert(&lg, 3, 0, 0);
    Insert(&lg, 3, 2, 0);
    Insert(&lg, 4, 0, 0);
    Insert(&lg, 4, 2, 0);
    Insert(&lg, 5, 1, 0);
    Insert(&lg, 5, 3, 0);
    
    DFSGraph(lg);
    
    Destroy(&lg);
    
    printf("\n");
    
    return 0;
}
