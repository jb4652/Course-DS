// Added by Bo
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// Added by Bo
#define MAX_ENCODING_LENGTH 20

// Added by Bo
#define TRUE 1
#define FALSE 0
typedef int BOOL;

// Added by Bo
typedef int ElemTypeTree;

////////////////////////////////////////////////////////////////////////////////
// Codes extracted from Ch05_BinaryTree_Build.c

// Program 5.1, p.76
typedef struct btnode
{
    ElemTypeTree element;
    struct btnode *lChild;
    struct btnode *rChild;
}BTNode;

// Program 5.2, p.76
typedef struct binarytree
{
    BTNode *root;
}BinaryTree;

// Program 5.3, p.77
void Create(BinaryTree *bt)
{
    bt->root = NULL;
}

BTNode* NewNode(ElemTypeTree x, BTNode *ln, BTNode *rn)
{
    BTNode *p = (BTNode*)malloc(sizeof(BTNode));
    
    p->element = x;
    p->lChild = ln;
    p->rChild = rn;
    
    return p;
}

BOOL Root(BinaryTree *bt, ElemTypeTree *x)
{
    if(bt->root)
    {
        x = &bt->root->element;
        
        return TRUE;
    }
    else
        return FALSE;
}

void MakeTree(BinaryTree *bt, ElemTypeTree e, BinaryTree *left, BinaryTree *right)
{
    if(bt->root || left == right)
        return;
    
    bt->root = NewNode(e, left->root, right->root);
    
    left->root = right->root = NULL;
}
////////////////////////////////////////////////////////////////////////////////

// Added by Bo
typedef BinaryTree ElemType;

////////////////////////////////////////////////////////////////////////////////
// Codes extracted from Ch05_PriorityQueue.c

// Program 5.11, p.94
void AdjustDown(ElemType heap[], int current, int border)
{
    int p = current;
    int minChild;
    ElemType temp;
    
    while(2*p+1 <= border)
    {
        if( (2*p+2 <= border) && (heap[2*p+1].root->element > heap[2*p+2].root->element) )
            minChild = 2*p+2;
        else
            minChild = 2*p+1;
        
        if(heap[p].root->element <= heap[minChild].root->element)
            break;
        else
        {
            temp = heap[p];
            heap[p] = heap[minChild];
            heap[minChild] = temp;
            p = minChild;
        }
    } 
}

// Program 5.13, p.97
void AdjustUp(ElemType heap[], int current)
{
    int p = current;
    ElemType temp;
    
    while(p > 0)
    {
        if(heap[p].root->element < heap[(p-1)/2].root->element)
        {
            temp = heap[p];
            heap[p] = heap[(p-1)/2];
            heap[(p-1)/2] = temp;
            
            p = (p-1)/2;
        }
        else
            break;
    }
}

// Program 5.12, p.96
// Program 5.14, partially, p.98
typedef struct priorityQueue
{
    ElemType *elements;
    int n;
    int maxSize;
}PriorityQueue;

// Program 5.14, partially, p.98-99
void CreatePQ(PriorityQueue *PQ, int mSize)
{
    PQ->maxSize = mSize;
    PQ->n = 0;
    PQ->elements = (ElemType*)malloc(mSize * sizeof(ElemType));
}

void Destroy(PriorityQueue *PQ)
{
    free(PQ->elements);
    PQ->n = 0;
    PQ->maxSize = 0;
}

BOOL IsEmpty(PriorityQueue *PQ)
{
    if(PQ->n == 0)
        return TRUE;
    else
        return FALSE;
}

BOOL IsFull(PriorityQueue *PQ)
{
    if(PQ->n == PQ->maxSize)
        return TRUE;
    else
        return FALSE;
}

int Size(PriorityQueue *PQ)
{
    return PQ->n;
}

void Append(PriorityQueue *PQ, ElemType x)
{
    if(IsFull(PQ))
        return;
    
    PQ->elements[PQ->n] = x;
    PQ->n++;
    AdjustUp(PQ->elements, PQ->n - 1);
}

void Serve(PriorityQueue *PQ, ElemType *x)
{
    if(IsEmpty(PQ))
        return;
    
    *x = PQ->elements[0];
    PQ->n--;
    
    PQ->elements[0] = PQ->elements[PQ->n];
    AdjustDown(PQ->elements, 0, PQ->n - 1);
}
////////////////////////////////////////////////////////////////////////////////

// Program 5.5, p.79-80
void PreOrder(BTNode *t)
{
    if(!t)
        return;
    
    printf("%d ", t->element);
    PreOrder(t->lChild);
    PreOrder(t->rChild);
}

void PreOrderTree(BinaryTree *bt)
{
    PreOrder(bt->root);
}

// Added by Bo
void InOrder(BTNode *t)
{
    if(!t)
        return;
    
    InOrder(t->lChild);
    printf("%d ", t->element);
    InOrder(t->rChild);
}

void InOrderTree(BinaryTree *bt)
{
    InOrder(bt->root);
}

// Program 5.8, p.82
void Clear(BTNode *t)
{
    if(!t)
        return;
    
    Clear(t->lChild);
    Clear(t->rChild);
    free(t);
}

void TreeClear(BinaryTree* bt)
{
    Clear(bt->root);
}

// Program 5.15, p.103
BinaryTree CreateHFMTree(int w[], int m)
{
    PriorityQueue PQ;
    BinaryTree x, y, z;
    
    CreatePQ(&PQ, m);
    Create(&x); Create(&y); Create(&z);
    
    for(int i = 0; i < m; i++)
    {
        MakeTree(&x, w[i], &y, &z);// y and z are NULL trees, but you can't use just NULL...
        Append(&PQ, x);
        
        x.root = NULL;
    }
    
    while(PQ.n > 1)
    {
        Serve(&PQ, &x);
        Serve(&PQ, &y);
        
        if(x.root->element < y.root->element)
            MakeTree(&z, x.root->element + y.root->element, &x, &y);
        else
            MakeTree(&z, x.root->element + y.root->element, &y, &x);
        
        Append(&PQ, z);
        
        z.root = NULL;
    }
    
    Serve(&PQ, &x);
    
    return x;
}

// Added by Bo
// Find the Huffman encodings means find tree leaves
// and record "0" or "1" in the visiting path...
void Leaf(BTNode *t, char encodings[])
{
    if(!t->lChild && !t->lChild)// This is a leaf node
    {
        printf("%d: %s\n", t->element, encodings);
        
        return;
    }
    
    if(t->lChild)
    {
        char temp[MAX_ENCODING_LENGTH];
        strcpy(temp, encodings);
    
        strcat(temp, "0");// Visit left child, record "0"
        
        Leaf(t->lChild, temp);
    }
    
    if(t->rChild)
    {
        char temp[MAX_ENCODING_LENGTH];
        strcpy(temp, encodings);
    
        strcat(temp, "1");// Visit right child, record "1"
        
        Leaf(t->rChild, temp);
    }
}

void FindLeaf(BinaryTree *bt, char encodings[])
{
    Leaf(bt->root, encodings);
}

// Added by Bo
int main(void)
{
    // Here I constructed the HFM Tree of Figure 5.34, p.104
    int w[] = {6, 4, 2, 3};
    int m = 4;
    
    BinaryTree HFMTree = CreateHFMTree(w, m);
    
    printf("The construced Huffman tree is:\n");
    printf("PreOrder:\t"); PreOrderTree(&HFMTree);
    printf("\n");
    printf("InOrder:\t"); InOrderTree(&HFMTree);
    printf("\n");
    
    printf("\n");
    printf("Its Huffman encodings:\n");
    char encodings[MAX_ENCODING_LENGTH] = "";
    FindLeaf(&HFMTree, encodings);
    
    TreeClear(&HFMTree);
    
    return 0;
}
