#include <stdio.h>// printf()
#include <stdlib.h>// malloc(), free()

typedef int ElemType;

typedef int BOOL;
#define TRUE 0
#define FALSE -1

#define ERROR 0
#define OK 1
#define Overflow 2
#define Underflow 3
#define NotPresent 4
#define Duplicate 5
typedef int Status;

////////////////////////////////////////////////////////////////////////////////
// P.34
// Program 3.2 Queue
typedef struct
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

// Function name conflicted with Destroy() of LGraph, so I changed its name...
void Destroy_Queue(Queue *Q)
{
    Q->maxSize = -1;
    free(Q->element);
    Q->front = Q->rear = -1;
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

void Clear(Queue *Q)
{
    Q->front = Q->rear = 0;
}
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// LGraph
// P.141 - 144

// P.141
typedef struct ENode
{
    int adjVex;
    ElemType w;
    struct ENode* nextArc;
}ENode;

// P.142
typedef struct
{
    int n;
    int e;
    ENode **a;
}LGraph;

// P.142 Program 9.6
Status Init(LGraph *lg, int nSize)
{
    int i;
    
    lg->n = nSize;
    lg->e = 0;
    lg->a = (ENode**)malloc(nSize * sizeof(ENode*));
    if(!lg->a)
    {
        return ERROR;
    }
    else
    {
        for(i=0; i<lg->n; i++)
            lg->a[i] = NULL;
        
        return OK;
    }
}

// P.142 Program 9.7
void Destroy(LGraph *lg)
{
    int i;
    ENode *p, *q;
    
    for(i=0; i<lg->n; i++)
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

// P.143 Program 9.8
Status Exist(LGraph *lg, int u, int v)
{
    ENode *p;
    
    if(u<0 || v<0 || u>lg->n-1 || v>lg->n-1 || u==v)
        return ERROR;
    
    p = lg->a[u];
    while(p && p->adjVex!=v)
        p = p->nextArc;
    
    if(!p)
        return ERROR;
    else
        return OK;
}

// P.143 Program 9.9
Status Insert(LGraph *lg, int u, int v, ElemType w)
{
    ENode *p;
    
    if(u<0 || v<0 || u>lg->n-1 || v>lg->n-1 || u==v)
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

// P.144 Program 9.10
Status Remove(LGraph *lg, int u, int v)
{
    ENode *p, *q;
    
    if(u<0 || v<0 || u>lg->n-1 || v>lg->n-1 || u==v)
        return ERROR;
    
    p = lg->a[u]; q = NULL;
    while(p && p->adjVex!=v)
    {
        q = p;
        p = p->nextArc;
    }
    
    if(!p)
        return NotPresent;
        
    if(q)
        q->nextArc = p->nextArc;
    else
        lg->a[u] = p->nextArc;
    
    free(p);
    lg->e--;
    
    return OK;
}
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// DFS
// P.146 Program 9.11
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
    
    // Init visited
    int *visited = malloc(g.n * sizeof(int));
    for(i=0; i<g.n; i++)
        visited[i] = 0;
    
    // Do DFS
    for(i=0; i<g.n; i++)
    {
        if(!visited[i])
        {
            DFS(i ,visited, g);
        }
    }
    
    free(visited);
}
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// BFS
// P.147 Program 9.12
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
    
    // Init visited
    int *visited = malloc(g.n * sizeof(int));
    for(i=0; i<g.n; i++)
        visited[i] = 0;
    
    // Do BFS
    for(i=0; i<g.n; i++)
    {
        if(!visited[i])
        {
            BFS(i ,visited, g);
        }
    }
        
    free(visited);
}
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// main
int main(int argc, char **argv)
{
    // Build the LGraph in Fig 9.13 (P.145)
    LGraph graph_913;
    Init(&graph_913, 6);// I have 6 vertices in this graph
    Insert(&graph_913, 5, 1, 1);
    Insert(&graph_913, 5, 3, 1);
    Insert(&graph_913, 0, 1, 1);
    Insert(&graph_913, 1, 3, 1);
    Insert(&graph_913, 3, 2, 1);
    Insert(&graph_913, 2, 0, 1);
    Insert(&graph_913, 1, 2, 1);
    Insert(&graph_913, 3, 0, 1);
    Insert(&graph_913, 4, 0, 1);
    Insert(&graph_913, 4, 2, 1);
    // DFS
    printf("The DFS result of Fig 9.13 is: ");
    DFSGraph(graph_913);
    printf("\n");
    // Destroy
    Destroy(&graph_913);
    
    // Build the LGraph in Fig 9.14 (P.146)
    LGraph graph_914;
    Init(&graph_914, 8);// I have 8 vertices in this graph
    // This is a undirected graph...
    Insert(&graph_914, 0, 1, 1); Insert(&graph_914, 1, 0, 1);
    Insert(&graph_914, 0, 2, 1); Insert(&graph_914, 2, 0, 1);
    Insert(&graph_914, 0, 4, 1); Insert(&graph_914, 4, 0, 1);
    Insert(&graph_914, 1, 2, 1); Insert(&graph_914, 2, 1, 1);
    Insert(&graph_914, 2, 4, 1); Insert(&graph_914, 4, 2, 1);
    Insert(&graph_914, 1, 3, 1); Insert(&graph_914, 3, 1, 1);
    Insert(&graph_914, 1, 5, 1); Insert(&graph_914, 5, 1, 1);
    Insert(&graph_914, 2, 5, 1); Insert(&graph_914, 5, 2, 1);
    Insert(&graph_914, 2, 6, 1); Insert(&graph_914, 6, 2, 1);
    Insert(&graph_914, 4, 6, 1); Insert(&graph_914, 6, 4, 1);
    Insert(&graph_914, 4, 7, 1); Insert(&graph_914, 7, 4, 1);
    Insert(&graph_914, 3, 5, 1); Insert(&graph_914, 5, 3, 1);
    Insert(&graph_914, 5, 6, 1); Insert(&graph_914, 6, 5, 1);
    Insert(&graph_914, 6, 7, 1); Insert(&graph_914, 7, 6, 1);
    // BFS
    printf("The BFS result of Fig 9.14 is: ");
    BFSGraph(graph_914);
    printf("\n");
    // Destroy
    Destroy(&graph_914);
    
	return 0;
}
