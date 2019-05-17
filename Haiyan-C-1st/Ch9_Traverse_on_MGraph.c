#include <stdio.h>// printf()
#include <stdlib.h>// malloc(), free()
#include <limits.h>// INT_MAX for noEdgeValue

typedef int ElemType;

typedef int BOOL;
#define TRUE 0
#define FALSE -1

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

// Function name conflicted with Destroy() of mGraph, so I changed its name...
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
// MGraph
// P.139 - 141

// P.139
typedef int ElemType;
typedef struct
{
    ElemType **a;
    int n;
    int e;
    ElemType noEdge;
}mGraph;

// P.139 Program 9.1
#define ERROR 0
#define OK 1
#define Overflow 2
#define Underflow 3
#define NotPresent 4
#define Duplicate 5
typedef int Status;

Status Init(mGraph *mg, int nSize, ElemType noEdgeValue)
{
    int i, j;
    
    mg->n = nSize;
    mg->e = 0;
    mg->noEdge = noEdgeValue;    
    mg->a = (ElemType**)malloc(nSize * sizeof(ElemType*));
    if(!mg->a)
        return ERROR;
        
    for(i=0; i<mg->n; i++)
    {
        mg->a[i] = (ElemType*)malloc(nSize * sizeof(ElemType));
        
        for(j=0; j<mg->n; j++)
            mg->a[i][j] = mg->noEdge;
            
        mg->a[i][i] = 0;
    }
    
    return OK;
}

// P.140 Program 9.2
void Destroy(mGraph *mg)
{
    int i;
    
    for(i=0; i<mg->n; i++)
        free(mg->a[i]);
    
    free(mg->a);
}

// P.140 Program 9.3
Status Exist(mGraph *mg, int u, int v)
{
    if(u<0 || v<0 || u>mg->n-1 || v>mg->n-1 || u==v || mg->a[u][v]==mg->noEdge)
        return ERROR;
    
    return OK;
}

// P.140 Program 9.4
Status Insert(mGraph *mg, int u, int v, ElemType w)
{
    if(u<0 || v<0 || u>mg->n-1 || v>mg->n-1 || u==v)
        return ERROR;
    
    if(mg->a[u][v] != mg->noEdge)
        return Duplicate;
    
    mg->a[u][v] = w;
    mg->e++;
    
    return OK;
}

// P.140 Program 9.5
Status Remove(mGraph *mg, int u, int v)
{
    if(u<0 || v<0 || u>mg->n-1 || v>mg->n-1 || u==v)
        return ERROR;
    
    if(mg->a[u][v] == mg->noEdge)
        return NotPresent;
    
    mg->a[u][v] = mg->noEdge;
    mg->e--;
    
    return OK;
}
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// DFS
// There are not any DFS programs based on MGraph in the textbook, 
// so I made it...
void DFS(int v, int visited[], mGraph g)
{
    int i;
    
    printf("%d ", v);
    visited[v] = 1;
    
    for(i=0; i<g.n; i++)
    {
        if(g.a[v][i] != 0 && g.a[v][i] != g.noEdge && !visited[i])
        {
            DFS(i, visited, g);
        }
    }
}

void DFSGraph(mGraph g)
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
// There are not any BFS programs based on MGraph in the textbook, 
// so I made it...
void BFS(int v, int visited[], mGraph g)
{
    int i;
    
    Queue q;
    Create(&q, g.n);
    
    visited[v] = 1;
    printf("%d ", v);
    
    EnQueue(&q, v);
    while(!IsEmpty(&q))
    {
        Front(&q, &v);
        DeQueue(&q);
        
        for(i=0; i<g.n; i++)
        {
            if(g.a[v][i] != 0 && g.a[v][i] != g.noEdge && !visited[i])
            {
                visited[i] = 1;
                printf("%d ", i);
                EnQueue(&q, i);
            }
        
        }
    }
}

void BFSGraph(mGraph g)
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
int main(int argc, char **argv)
{
	// Build the MGraph in Fig 9.13 (P.145)
    mGraph graph_913;
    Init(&graph_913, 6, INT_MAX);// I have 6 vertices in this graph
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
    
    // Build the MGraph in Fig 9.14 (P.146)
    mGraph graph_914;
    Init(&graph_914, 8, INT_MAX);// I have 8 vertices in this graph
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
