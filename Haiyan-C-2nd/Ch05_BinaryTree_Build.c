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
    
    MakeTree(&y, 'E', &a, &b);
    MakeTree(&z, 'F', &a, &b);
    MakeTree(&x, 'C', &y, &z);
    MakeTree(&y, 'D', &a, &b);
    MakeTree(&z, 'B', &y, &x);
    
    printf("PreOrder:\t"); PreOrderTree(&z); printf("\n");
    
    TreeClear(&z);
    
    return 0;
}
