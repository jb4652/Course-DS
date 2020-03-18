// Added by Bo
#include <stdlib.h>
#include <stdio.h>

// Added by Bo
#define TRUE 1
#define FALSE 0
typedef int BOOL;

// Program 5.4, partially, p.77
typedef char ElemType;

// Program 5.1, p.76
typedef struct btnode
{
    ElemType element;
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

BTNode* NewNode(ElemType x, BTNode *ln, BTNode *rn)
{
    BTNode *p = (BTNode*)malloc(sizeof(BTNode));
    
    p->element = x;
    p->lChild = ln;
    p->rChild = rn;
    
    return p;
}

BOOL Root(BinaryTree *bt, ElemType *x)
{
    if(bt->root)
    {
        x = &bt->root->element;
        
        return TRUE;
    }
    else
        return FALSE;
}

void MakeTree(BinaryTree *bt, ElemType e, BinaryTree *left, BinaryTree *right)
{
    if(bt->root || left == right)
        return;
    
    bt->root = NewNode(e, left->root, right->root);
    
    left->root = right->root = NULL;
}

// Program 5.5, p.79-80
void PreOrder(BTNode *t)
{
    if(!t)
        return;
    
    printf("%c", t->element);
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
    printf("%c", t->element);
    InOrder(t->rChild);
}

void InOrderTree(BinaryTree *bt)
{
    InOrder(bt->root);
}

// Added by Bo
void PostOrder(BTNode *t)
{
    if(!t)
        return;
    
    PostOrder(t->lChild);
    PostOrder(t->rChild);
    printf("%c", t->element);
}

void PostOrderTree(BinaryTree *bt)
{
    PostOrder(bt->root);
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

// Program 5.4, partially, p.77-78
int main(void)
{
    BinaryTree a, b, x, y, z;
    
    Create(&a); Create(&b); Create(&x); Create(&y); Create(&z);
    
    // I want to build a tree of Fig 5.11, p.79
    MakeTree(&x, 'J', &a, &b);
    MakeTree(&y, 'G', &a, &b);
    MakeTree(&z, 'F', &x, &y);// x and y will be set to NULL and can be reused
    
    MakeTree(&y, 'H', &a, &b);
    MakeTree(&x, 'E', &y, &z);// y and z will be set to NULL and can be reused
    
    MakeTree(&y, 'D', &x, &b);// x and z will be available
    
    MakeTree(&x, 'K', &a, &b);
    MakeTree(&z, 'C', &x, &b);// x will be available
    MakeTree(&x, 'B', &a, &z);// z will be available
    
    MakeTree(&z, 'A', &y, &x);
    
    printf("PreOrder:\t"); PreOrderTree(&z); printf("\n");
    printf("InOrder:\t"); InOrderTree(&z); printf("\n");
    printf("PostOrder:\t"); PostOrderTree(&z); printf("\n");
    
    TreeClear(&z);
    
    printf("\n");
    
    // Another way more easy to understand for building the same tree...
    BinaryTree aa, bb;
    BinaryTree A, B, C, D, E, F, G, H, J, K;
    Create(&aa); Create(&bb);
    Create(&A); Create(&B); Create(&C); Create(&D); Create(&E);
    Create(&F); Create(&G); Create(&H); Create(&J); Create(&K);
    
    // I want to build a tree of Fig 5.11, p.79
    MakeTree(&J, 'J', &aa, &bb);
    MakeTree(&G, 'G', &aa, &bb);
    MakeTree(&F, 'F', &J, &G);
    MakeTree(&H, 'H', &aa, &bb);
    MakeTree(&E, 'E', &H, &F);
    MakeTree(&D, 'D', &E, &bb);
    
    MakeTree(&K, 'K', &aa, &bb);
    MakeTree(&C, 'C', &K, &bb);
    MakeTree(&B, 'B', &aa, &C);
    
    MakeTree(&A, 'A', &D, &B);
    
    printf("PreOrder:\t"); PreOrderTree(&A); printf("\n");
    printf("InOrder:\t"); InOrderTree(&A); printf("\n");
    printf("PostOrder:\t"); PostOrderTree(&A); printf("\n");
    
    TreeClear(&A);
    
    return 0;
}
