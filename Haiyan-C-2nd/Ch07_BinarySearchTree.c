// Added by Bo
#include <stdio.h>
#include <stdlib.h>

// Added by Bo
#define TRUE 1
#define FALSE 0
typedef int BOOL;

// Added by Bo
// Useless, bebause I only use KeyType
typedef char ElemType;

// Program, p.117
typedef int KeyType;

typedef struct entry
{
    KeyType Key;
    ElemType Data;
}Entry;

typedef struct bstnode
{
    Entry Element;
    struct bstnode *LChild, *RChild;
}BSTNode, *BSTree;

// Program 7.1, p.117
BSTree RecSearchBST(BSTree T, KeyType k)
{
    if(!T)
        return NULL;
    
    if(T->Element.Key == k)
        return T;
    else if(k < T->Element.Key)
        return RecSearchBST(T->LChild, k);
    else
        return RecSearchBST(T->RChild, k);
}

// Program 7.2, p.118
BSTree IterSearchBST(BSTree T, KeyType k)
{
    while(T)
    {
        if(k < T->Element.Key)
            T = T->LChild;
        else if(k > T->Element.Key)
            T = T->RChild;
        else
            return T;
    }
    
    return NULL;
}

// Program 7.3, p.119
// BSTree *T is actually BSTNode **T, for construct the tree from NULL pointer input
BOOL InsertBST(BSTree *T, Entry e)
{
    BSTNode *p = *T, *q, *r;
    KeyType k = e.Key;
    
    while(p)
    {
        q = p;
        
        if(k < p->Element.Key) p = p->LChild;
        else if(k > p->Element.Key) p = p->RChild;
        else
        {
            printf("Duplicate\n");
            
            return FALSE;
        }
    }
    
    r = (BSTNode*)malloc(sizeof(BSTNode));
    r->Element = e;
    r->LChild = NULL;
    r->RChild = NULL;
    
    if(!(*T))
        *T = r;
    else if(k < q->Element.Key)
        q->LChild = r;
    else
        q->RChild = r;
    
    return TRUE;
}

// Program 7.4, p.120-121
BOOL DeleteBST(BSTree T, KeyType k)
{
    BSTNode *c, *r, *s, *p = T, *q;
    
    while(p && p->Element.Key != k)
    {
        q = p;
        
        if(k < p->Element.Key)
            p = p->LChild;
        else
            p = p->RChild;
    }
    
    if(!p)
    {
        printf("NotPresent\n");
        
        return FALSE;
    }
    
    if(p->LChild && p->RChild)
    {
        s = p->RChild;
        r = p;
        
        while(s->LChild)
        {
            r = s;
            s = s->LChild;
        }
        
        p->Element = s->Element;
        p = s;
        q = r;
    }
    
    if(p->LChild)
        c = p->LChild;
    else
        c = p->RChild;
    
    if(p == T)
        T = c;
    else if(p == q->LChild)
        q->LChild = c;
    else
        q->RChild = c;
    
    free(p);
    
    return TRUE;
}

// Added by Bo
void PreOrder(BSTNode *t)
{
    if(t)
    {
        printf("%5d", t->Element.Key);
        if(t->LChild) PreOrder(t->LChild);
        if(t->RChild) PreOrder(t->RChild);
    }
}

// Added by Bo
void DestroyBST(BSTree T)
{
    if(T)
    {
        if(T->LChild) DestroyBST(T->LChild);
        if(T->RChild) DestroyBST(T->RChild);
        
        free(T);
    }
}

// Added by Bo
int main(void)
{
    // If I want to pass a NULL pointer to InsertBST(),
    // and get the correct node come out, 
    // I have to pass a pointer to a pointer, i.e. BSTNode**/BSTree* to InsertBST()
    // See the following URL:
    // https://blog.csdn.net/wang371372/article/details/51304003
    
    // I want to show the same results of Figure 7.3, p.119
    BSTree T = NULL;
    
    Entry E_28; E_28.Key = 28;
    Entry E_21; E_21.Key = 21;
    Entry E_25; E_25.Key = 25;
    Entry E_36; E_36.Key = 36;
    Entry E_33; E_33.Key = 33;
    Entry E_43; E_43.Key = 43;
    
    InsertBST(&T, E_28); PreOrder(T); printf("\n");
    InsertBST(&T, E_21); PreOrder(T); printf("\n");
    InsertBST(&T, E_25); PreOrder(T); printf("\n");
    InsertBST(&T, E_36); PreOrder(T); printf("\n");
    InsertBST(&T, E_33); PreOrder(T); printf("\n");
    InsertBST(&T, E_43); PreOrder(T); printf("\n");
    
    printf("\n");
    
    DestroyBST(T);
    
    // I want to show the same results of Figure 7.4, p.120
    BSTree T1 = NULL;
    
    Entry E_26; E_26.Key = 26;
    Entry E_30; E_30.Key = 30;
    Entry E_35; E_35.Key = 35;
    Entry E_38; E_38.Key = 38;
    Entry E_40; E_40.Key = 40;
    Entry E_45; E_45.Key = 45;
    Entry E_50; E_50.Key = 50;
    
    InsertBST(&T1, E_30);
    InsertBST(&T1, E_25);
    InsertBST(&T1, E_28);
    InsertBST(&T1, E_26);
    InsertBST(&T1, E_40);
    InsertBST(&T1, E_35);
    InsertBST(&T1, E_50);
    InsertBST(&T1, E_38);
    InsertBST(&T1, E_45);
    PreOrder(T1); printf("\n");
    
    DeleteBST(T1, 45); PreOrder(T1); printf("\n");
    DeleteBST(T1, 25); PreOrder(T1); printf("\n");
    DeleteBST(T1, 30); PreOrder(T1); printf("\n");
    
    printf("\n");
    
    // To search 50 in Figure 7.4(d)
    if(RecSearchBST(T1, 50))
        printf("I recursively find 50 in Figure 7.4(d)\n");
    else
        printf("I recursively can not find 50 in Figure 7.4(d)\n");
        
    if(IterSearchBST(T1, 50))
        printf("I iteratively find 50 in Figure 7.4(d)\n");
    else
        printf("I iteratively can not find 50 in Figure 7.4(d)\n");
        
    // To search 60 in Figure 7.4(d)
    if(RecSearchBST(T1, 60))
        printf("I recursively find 60 in Figure 7.4(d)\n");
    else
        printf("I recursively can not find 60 in Figure 7.4(d)\n");
        
    if(IterSearchBST(T1, 60))
        printf("I iteratively find 60 in Figure 7.4(d)\n");
    else
        printf("I iteratively can not find 60 in Figure 7.4(d)\n");
    
    DestroyBST(T1);
    
    return 0;
}
