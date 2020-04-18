// Added by Bo
#include <stdio.h>
#include <stdlib.h>
// For INFTY in Floyd()
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

// Program 9.19, p.181
void Floyd(MGraph g)
{
    int i, j, k;
    
    ElemType **d = (ElemType**)malloc(g.n * sizeof(ElemType*));
    int **p = (int**)malloc(g.n * sizeof(int*));
    
    for(i = 0; i < g.n; i++)
    {
        d[i] = (ElemType*)malloc(g.n * sizeof(ElemType));
        p[i] = (int*)malloc(g.n * sizeof(int));
        
        for(j = 0; j < g.n; j++)
        {
            d[i][j] = g.noEdge;
            p[i][j] = 0;
        }
    }
    
    for(i = 0; i < g.n; i++)
    {
        for(j = 0; j < g.n; j++)
        {
            d[i][j] = g.a[i][j];
            
            if(i != j && g.a[i][j] < INFTY)
                p[i][j] = i;
            else
                p[i][j] = -1;
        }
    }
    
    for(k = 0; k < g.n; k++)
    {
        for(i = 0; i < g.n; i++)
        {
            for(j = 0; j < g.n; j++)
            {
                if(d[i][k] + d[k][j] < d[i][j])
                {
                    d[i][j] = d[i][k] + d[k][j];
                    p[i][j] = p[k][j];
                }
            }
        }
    }
    
    for(i = 0; i < g.n; i++)
    {
        for(j = 0; j < g.n; j++)
        {
            printf("%d ", d[i][j]);
        }
        
        printf("\n");
    }
}

// Added by Bo
int main(void)
{
    MGraph mg;
    
    // Shortest Path - Floyd (MGraph) on Figure 9.22 & Table 9.5, p.180
    
    Init(&mg, 4, noEdgeValue);
    
    Insert(&mg, 0, 1, 1);
    Insert(&mg, 0, 3, 4);
    Insert(&mg, 1, 2, 9);
    Insert(&mg, 1, 3, 2);
    Insert(&mg, 2, 0, 3);
    Insert(&mg, 2, 1, 5);
    Insert(&mg, 2, 3, 8);
    Insert(&mg, 3, 2, 6);
    
    // Print out Table 9.5(d), p.180
    OutputMatrix(mg);
    
    printf("\n");
    
    // Print out Table 9.5(d3), p.180
    Floyd(mg);
    
    Destroy(&mg);
    
    return 0;
}
