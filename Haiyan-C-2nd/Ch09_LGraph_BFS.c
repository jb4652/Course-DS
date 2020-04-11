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
// This part of codes is extracted from Ch03_SeqQueue.c
// Please note that to avoid the function name confliction,
// I changed Destroy() here to DestroyQueue()...

// Added by Bo
#define FALSE 0
#define TRUE 1
typedef int BOOL;

// Added by Bo
typedef int ElemType;

// Program 3.2, p.33-34
typedef struct queue
{
    int front;
    int rear;
    
    int maxSize;
    
    ElemType *element;
}Queue;

void Create(Queue *Q, int mSize)
{
    Q->maxSize = mSize;
    Q->element = (ElemType*)malloc(sizeof(ElemType) * mSize);
    Q->front = Q->rear = 0;
}

void DestroyQueue(Queue *Q)
{
    Q->maxSize = 0;
    free(Q->element);
    Q->front = Q->rear = -1;
}

void Clear(Queue *Q)
{
    Q->front = Q->rear = 0;
}

BOOL IsEmpty(Queue *Q)
{
    return Q->front == Q->rear;
}

BOOL IsFull(Queue *Q)
{
    return (Q->rear + 1) % Q->maxSize == Q->front;
}

BOOL Front(Queue *Q, ElemType *x)
{
    if(IsEmpty(Q))
        return FALSE;
    
    *x = Q->element[(Q->front + 1) % Q->maxSize];
    
    return TRUE;
}

BOOL EnQueue(Queue *Q, ElemType x)
{
    if(IsFull(Q))
        return FALSE;
    
    Q->rear = (Q->rear + 1) % Q->maxSize;
    Q->element[Q->rear] = x;
    
    return TRUE;
}

BOOL DeQueue(Queue *Q)
{
    if(IsEmpty(Q))
        return FALSE;
    
    Q->front = (Q->front + 1) % Q->maxSize;
    
    return TRUE;
}
////////////////////////////////////////////////////////////////////////////////

// Program 9.12, p.164
void BFS(int v, int visited[], LGraph g)
{
    ENode *w;
    
    Queue q;
    Create(&q, g.n);
    
    visited[v] = 1;
    
    printf("%d ", v);
    
    EnQueue(&q, v);
    
    while(!IsEmpty(&q))
    {
        Front(&q, &v);
        DeQueue(&q);
        
        for(w = g.a[v]; w; w = w->nextArc)
        {
            if(!visited[w->adjVex])
            {
                visited[w->adjVex] = 1;
                
                printf("%d ", w->adjVex);
                
                EnQueue(&q, w->adjVex);
            }
        }
    }
}

void BFSGraph(LGraph g)
{
    int i;
    
    int *visited = (int*)malloc(g.n * sizeof(int));
    
    for(i = 0; i < g.n; i++)
    {
        visited[i] = 0;
    }
    
    for(i = 0; i < g.n; i++)
    {
        if(!visited[i]) BFS(i, visited, g);
    }
    
    free(visited);
}

// Added by Bo
int main(void)
{
    LGraph lg;
    
    // BFS(LGraph) on Figure 9.14(a), p.163
    
    Init(&lg, 8);
    
    // This is an undirected graph, thus
    // each egde is inserted twice...
    Insert(&lg, 0, 1, 0);
    Insert(&lg, 0, 2, 0);
    Insert(&lg, 0, 4, 0);
    Insert(&lg, 1, 0, 0);
    Insert(&lg, 1, 2, 0);
    Insert(&lg, 1, 3, 0);
    Insert(&lg, 1, 5, 0);
    Insert(&lg, 2, 0, 0);
    Insert(&lg, 2, 1, 0);
    Insert(&lg, 2, 4, 0);
    Insert(&lg, 2, 5, 0);
    Insert(&lg, 2, 6, 0);
    Insert(&lg, 3, 1, 0);
    Insert(&lg, 3, 5, 0);
    Insert(&lg, 4, 0, 0);
    Insert(&lg, 4, 2, 0);
    Insert(&lg, 4, 6, 0);
    Insert(&lg, 4, 7, 0);
    Insert(&lg, 5, 1, 0);
    Insert(&lg, 5, 2, 0);
    Insert(&lg, 5, 3, 0);
    Insert(&lg, 5, 6, 0);
    Insert(&lg, 6, 2, 0);
    Insert(&lg, 6, 4, 0);
    Insert(&lg, 6, 5, 0);
    Insert(&lg, 6, 7, 0);
    Insert(&lg, 7, 4, 0);
    Insert(&lg, 7, 6, 0);
    
    BFSGraph(lg);
    
    Destroy(&lg);
    
    printf("\n");
    
    return 0;
}
