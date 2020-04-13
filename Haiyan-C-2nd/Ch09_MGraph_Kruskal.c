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

// Program, p.174
typedef struct edge
{
    int u;
    int v;
    ElemType w;
}Edge;

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

// Program 9.17, p.175-176
void SelectSort(Edge *eg, int n)
{
    int small, i, j;
    
    Edge t;
    
    for(i = 0; i < n - 1; i++)
    {
        small = i;
        
        for(j = i + 1; j < n; j++)
        {
            if(eg[j].w < eg[small].w)
            {
                small = j;
            }
        }
        
        t = eg[i];
        eg[i] = eg[small];
        eg[small] = t;
    }
}

void Kruskal(MGraph g)
{
    int i, j, k, u1, v1, vs1, vs2;
    
    int *vexSet = (int*)malloc(sizeof(int) * g.n);
    Edge *edgeSet = (Edge*)malloc(sizeof(Edge) * g.e);
    
    k = 0;
    
    for(i = 0; i < g.n; i++)
    {
        for(j = 0; j < i; j++)
        {
            if(g.a[i][j] != 0 && g.a[i][j] != g.noEdge)
            {
                edgeSet[k].u = i;
                edgeSet[k].v = j;
                edgeSet[k].w = g.a[i][j];
                
                k++;
            }
        }
    }
    
    SelectSort(edgeSet, g.e / 2);
    
    for(i = 0; i < g.n; i++)
    {
        vexSet[i] = i;
    }
    
    k = 0;
    j = 0;
    while(k < g.n - 1)
    {
        u1 = edgeSet[j].u;
        v1 = edgeSet[j].v;
        
        vs1 = vexSet[u1];
        vs2 = vexSet[v1];
        
        if(vs1 != vs2)
        {
            printf("%d, %d, %d\n", edgeSet[j].u, edgeSet[j].v, edgeSet[j].w);
            
            k++;
            
            for(i = 0; i < g.n; i++)
            {
                if(vexSet[i] == vs2)
                {
                    vexSet[i] = vs1;
                }
            }
        }
        
        j++;
    }
}

// Added by Bo
int main(void)
{
    MGraph mg;
    
    // Minimum Cost Spanning Tree - Kruskal (MGraph) on Figure 9.18, p.174
    
    Init(&mg, 6, noEdgeValue);
    
    Insert(&mg, 0, 1, 10);
    Insert(&mg, 0, 2, 7);
    Insert(&mg, 0, 5, 4);
    Insert(&mg, 1, 0, 10);
    Insert(&mg, 1, 4, 2);
    Insert(&mg, 2, 0, 7);
    Insert(&mg, 2, 3, 8);
    Insert(&mg, 2, 5, 6);
    Insert(&mg, 3, 2, 8);
    Insert(&mg, 3, 4, 9);
    Insert(&mg, 3, 5, 5);
    Insert(&mg, 4, 1, 2);
    Insert(&mg, 4, 3, 9);
    Insert(&mg, 4, 5, 7);
    Insert(&mg, 5, 0, 4);
    Insert(&mg, 5, 2, 6);
    Insert(&mg, 5, 3, 5);
    Insert(&mg, 5, 4, 7);
    
    Kruskal(mg);
    
    Destroy(&mg);
    
    return 0;
}
