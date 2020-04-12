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
void DFS(int v, int visited[], MGraph g)
{
    int j;
    
    printf("%d ", v);
    
    visited[v] = 1;
    
    for(j = 0; j < g.n; j++)
    {
        if(!visited[j] && j != v && g.a[v][j] != g.noEdge)
        {
            DFS(j, visited, g);
        }
    }
}

void DFSGraph(MGraph g)
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
    MGraph mg;
    
    // DFS(MGraph) on Figure 9.1(b), p.151
    
    Init(&mg, 4, noEdgeValue);
    
    Insert(&mg, 0, 1, 1);
    Insert(&mg, 0, 2, 1);
    Insert(&mg, 1, 3, 1);
    Insert(&mg, 2, 1, 1);
    Insert(&mg, 3, 2, 1);
    
    OutputMatrix(mg);
    
    DFSGraph(mg);
    
    Destroy(&mg);
    
    printf("\n\n");
    
    // DFS(MGraph) on Figure 9.13(a), p.162
    Init(&mg, 6, noEdgeValue);
    
    Insert(&mg, 0, 1, 1);
    Insert(&mg, 1, 2, 1);
    Insert(&mg, 1, 3, 1);
    Insert(&mg, 2, 0, 1);
    Insert(&mg, 3, 0, 1);
    Insert(&mg, 3, 2, 1);
    Insert(&mg, 4, 0, 1);
    Insert(&mg, 4, 2, 1);
    Insert(&mg, 5, 1, 1);
    Insert(&mg, 5, 3, 1);
    
    OutputMatrix(mg);
    
    DFSGraph(mg);
    
    Destroy(&mg);
    
    printf("\n\n");
    
    // DFS(MGraph) on Figure 9.6(a), p.153
    Init(&mg, 5, noEdgeValue);
    
    Insert(&mg, 0, 4, 1);
    Insert(&mg, 1, 0, 1);
    Insert(&mg, 1, 3, 1);
    Insert(&mg, 2, 0, 1);
    Insert(&mg, 2, 1, 1);
    Insert(&mg, 2, 3, 1);
    Insert(&mg, 4, 1, 1);
    
    OutputMatrix(mg);
    
    DFSGraph(mg);
    
    Destroy(&mg);
    
    printf("\n");
    
    return 0;
}
