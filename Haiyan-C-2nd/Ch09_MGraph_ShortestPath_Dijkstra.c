// Added by Bo
#include <stdio.h>
#include <stdlib.h>
// For INFTY in Choose() & Dijkstra()
#include <limits.h>
#define INFTY INT_MAX

// Added by Bo
const int noEdgeValue = 99999;

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

// Program 9.18, p.178-179
int Choose(int *d, int *s, int n)
{
    int i, minpos;
    
    ElemType min;
    
    min = INFTY;
    
    minpos = -1;
    
    for(i = 1; i < n; i++)
    {
        if(d[i] < min && !s[i])
        {
            min = d[i];
            
            minpos = i;
        }
    }
    
    return minpos;
}

Status Dijkstra(int v, ElemType *d, int *path, MGraph g)
{
    int i, k, w;
    
    int *s;
    
    if(v < 0 || v > g.n - 1)
        return ERROR;
    
    s = (int*)malloc(sizeof(int) * g.n);
    
    for(i = 0; i < g.n; i++)
    {
        s[i] = 0;
        d[i] = g.a[v][i];
        
        if(i != v && d[i] < INFTY)
            path[i] = v;
        else
            path[i] = -1;
    }
    
    s[v] = 1; d[v] = 0;
    
    for(i = 1; i < g.n - 1; i++)
    {
        k = Choose(d, s, g.n);
        
        s[k] = 1;
        
        printf("%d ", k);
        
        for(w = 0; w < g.n; w++)
        {
            if(!s[w] && d[k] + g.a[k][w] < d[w])
            {
                d[w] = d[k] + g.a[k][w];
                
                path[w] = k;
            }
        }
    }
    
    printf("\n");
    
    for(i = 0; i < g.n; i++)
        printf("%d ", d[i]);
    
    printf("\n");
    
    return OK;
}

// Added by Bo
int main(void)
{
    MGraph mg;
    
    // Shortest Path - Dijkstra (MGraph) on Figure 9.19, p.176 & Table 9.4, p.178
    
    Init(&mg, 6, noEdgeValue);
    
    Insert(&mg, 0, 1, 50);
    Insert(&mg, 0, 2, 10);
    Insert(&mg, 0, 4, 80);
    Insert(&mg, 1, 2, 15);
    Insert(&mg, 1, 4, 20);
    Insert(&mg, 2, 3, 15);
    Insert(&mg, 3, 1, 20);
    Insert(&mg, 3, 4, 45);
    Insert(&mg, 5, 3, 9);
    Insert(&mg, 5, 4, 10);
    
    // Source vertex
    int v = 0;
    
    int *d = (int*)malloc(sizeof(int) * mg.n);
    int *path = (int*)malloc(sizeof(int) * mg.n);
    
    Dijkstra(v, d, path, mg);
    
    Destroy(&mg);
    free(d);
    free(path);
    
    return 0;
}
