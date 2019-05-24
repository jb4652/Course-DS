#include <stdio.h>// printf()
#include <stdlib.h>// malloc()

// P.129
#define HTMaxSize 11// To demonstrate Table 8.4 I changed 100 to 11
#define ElemType int
#define NeverUsed 0
#define Status int
#define OK 1
#define ERROR -1

// I made the following 3 lines because gcc has no bool type
typedef int bool;
#define true 1;
#define false -1;

// P.129
typedef struct htnode
{
    ElemType Element;
    bool Empty;
}HTNode;
typedef struct hashtable
{
    int HTSize;
    HTNode *ht;
}HashTable;

////////////////////////////////////////////////////////////////////////////////
// Hash table with linear probing/linear open addressing
// P.129
// Program 8.3
Status Create(HashTable *p)
{
    p->HTSize = HTMaxSize;
    p->ht = malloc(sizeof(HTNode) * HTMaxSize);
    if(!p->ht)
        return ERROR;
    
    for(int i=0; i<HTMaxSize; i++)
    {
        p->ht[i].Empty = true;
        p->ht[i].Element = NeverUsed;
    }
    
    return OK;
}

// P.129
// Program 8.4
void Traverse(HashTable *p)
{
    for(int i=0; i<HTMaxSize; i++)
    {
        printf("%d ", p->ht[i].Element);
    }
}

// P.130
// Program 8.5
Status Insert(HashTable *p, ElemType k)
{
    int i = k % p->HTSize;
    int j = i;
    
    do{
        if(p->ht[j].Element == k)
        {
            printf("Duplicate\n");
            return ERROR;
        }
        else if(p->ht[j].Element == NeverUsed)
        {
            p->ht[j].Empty = false;
            p->ht[j].Element = k;
            return true;
        }
        
        j = (j+1) % p->HTSize;// linear probing/linear open addressing
    }while(j!=i);
    
    printf("OverFlow\n");
    return false;
}

// P.131
// Program 8.6
int hSearch(HashTable *p, int k)
{
    int i, j;
    i = k % p->HTSize;
    j = i;
    
    do{
        if(p->ht[j].Empty || p->ht[j].Element == k)
            return j;
        
        j = (j+1) % p->HTSize;// linear probing/linear open addressing
    }while(j!=i);
    
    return j;
}

int Search(HashTable htb, int k)
{
    int b = hSearch(&htb, k);
    if(htb.ht[b].Element != k)
        return ERROR;
    
    return b;
}

// P.131
// Program 8.7
Status Delete(HashTable *htb, int k)
{
    int i = hSearch(htb, k);
    if(htb->ht[i].Element != k)
    {
        printf("No element");
        return ERROR;
    }
    
    htb->ht[i].Element = NeverUsed;
    
    return OK;
}
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// main()
int main(int argc, char **argv)
{
    HashTable ht;
    Create(&ht);
    
    // Input sequence: 81, 36, 91, 46, 71, 56, 61, 66
    // Table 8.3
    // P.128
    Insert(&ht, 81);
    Insert(&ht, 36);
    Insert(&ht, 91);
    Insert(&ht, 46);
    Insert(&ht, 71);
    Insert(&ht, 56);
    Insert(&ht, 61);
    Insert(&ht, 66);
    
    Traverse(&ht);
    
    return 0;
}
