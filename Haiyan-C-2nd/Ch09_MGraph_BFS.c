// Added by Bo
#include <stdio.h>
#include <stdlib.h>

// Added by Bo
const int noEdgeValue = -99;

// Program, p.156
typedef int ElemType;

typedef struct mGraph
{
    ElemType **a;
    
    int n;
    int e;
    
    ElemType noEdge;
}MGraph;

// Program 9.1, p.156
#define ERROR 0
#define OK 1
#define Overflow 2
#define Underflow 3
#define NotPresent 4
#define Duplicate 5

typedef int Status;

Status Init(MGraph *mg, int nSize, ElemType noEdgeValue)
{
    int i, j;
    
    mg->n = nSize;
    mg->e = 0;
    mg->noEdge = noEdgeValue;
    mg->a = (ElemType**)malloc(nSize * sizeof(ElemType*));
    if(!mg->a)
        return ERROR;
    
    for(i = 0; i < mg->n; i++)
    {
        mg->a[i] = (ElemType*)malloc(nSize * sizeof(ElemType));
        
        for(j = 0; j < mg->n; j++)
            mg->a[i][j] = mg->noEdge;
        
        mg->a[i][i] = 0;
    }
    
    return OK;
}

// Program 9.2, p.157
void Destroy(MGraph *mg)
{
    int i;
    
    for(i = 0; i < mg->n; i++)
    {
        free(mg->a[i]);
    }
    
    free(mg->a);
}

// Program 9.3, p.157
Status Exist(MGraph *mg, int u, int v)
{
    if(u < 0 || v < 0 || u > mg->n - 1 || v > mg->n - 1 || u == v || mg->a[u][v] == mg->noEdge)
        return ERROR;
    
    return OK;
}

// Program 9.4, p.157
Status Insert(MGraph *mg, int u, int v, ElemType w)
{
    if(u < 0 || v < 0 || u > mg->n - 1 || v > mg->n - 1 || u == v)
        return ERROR;
    
    if(mg->a[u][v] != mg->noEdge)
        return Duplicate;
    
    mg->a[u][v] = w;
    mg->e++;
    
    return OK;
}

// Program 9.5, p.157-158
Status Remove(MGraph *mg, int u, int v)
{
    if(u < 0 || v < 0 || u > mg->n - 1 || v > mg->n - 1 || u == v)
        return ERROR;
    
    if(mg->a[u][v] == mg->noEdge)
        return NotPresent;
    
    mg->a[u][v] = mg->noEdge;
    mg->e--;
    
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

// Added by Bo
void OutputMatrix(MGraph g)
{
    for(int i = 0; i < g.n; i++)
    {
        for(int j = 0; j < g.n; j++)
        {
            printf("%d\t", g.a[i][j]);
        }
        
        printf("\n");
    }
}

// Added by Bo
void BFS(int v, int visited[], MGraph g)
{
    Queue q;
    Create(&q, g.n);
    
    visited[v] = 1;
    
    printf("%d ", v);
    
    EnQueue(&q, v);
    
    while(!IsEmpty(&q))
    {
        Front(&q, &v);
        DeQueue(&q);
        
        for(int j = 0; j < g.n; j++)
        {
            if(!visited[j] && j != v && g.a[v][j] != g.noEdge)
            {
                visited[j] = 1;
                
                printf("%d ", j);
                
                EnQueue(&q, j);
            }
        }
    }
}

void BFSGraph(MGraph g)
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
    MGraph mg;
    
    // BFS(MGraph) on Figure 9.14(a), p.163
    
    Init(&mg, 8, noEdgeValue);
    
    // This is an undirected graph, thus
    // each egde is inserted twice...
    Insert(&mg, 0, 1, 1);
    Insert(&mg, 0, 2, 1);
    Insert(&mg, 0, 4, 1);
    Insert(&mg, 1, 0, 1);
    Insert(&mg, 1, 2, 1);
    Insert(&mg, 1, 3, 1);
    Insert(&mg, 1, 5, 1);
    Insert(&mg, 2, 0, 1);
    Insert(&mg, 2, 1, 1);
    Insert(&mg, 2, 4, 1);
    Insert(&mg, 2, 5, 1);
    Insert(&mg, 2, 6, 1);
    Insert(&mg, 3, 1, 1);
    Insert(&mg, 3, 5, 1);
    Insert(&mg, 4, 0, 1);
    Insert(&mg, 4, 2, 1);
    Insert(&mg, 4, 6, 1);
    Insert(&mg, 4, 7, 1);
    Insert(&mg, 5, 1, 1);
    Insert(&mg, 5, 2, 1);
    Insert(&mg, 5, 3, 1);
    Insert(&mg, 5, 6, 1);
    Insert(&mg, 6, 2, 1);
    Insert(&mg, 6, 4, 1);
    Insert(&mg, 6, 5, 1);
    Insert(&mg, 6, 7, 1);
    Insert(&mg, 7, 4, 1);
    Insert(&mg, 7, 6, 1);
    
    OutputMatrix(mg);
    
    BFSGraph(mg);
    
    Destroy(&mg);
    
    printf("\n");
    
    return 0;
}
