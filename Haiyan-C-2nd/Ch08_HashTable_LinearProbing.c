// Added by Bo
#include <stdio.h>
#include <stdlib.h>

// Program 8.1, p.145-147
#define TRUE 1
#define FALSE 0
#define NotPresent -1
#define NeverUsed -99

typedef int BOOL;

typedef struct hashTable
{
    int M;
    int num;
    
    BOOL *empty;
    int *elements;
}HashTable;

void CreateHT(HashTable *ht, int size)
{
    int i;
    
    ht->M = size;
    ht->num = 0;
    
    ht->empty = (BOOL*)malloc(sizeof(BOOL) * size);
    ht->elements = (int*)malloc(sizeof(int) * size);
    
    for(i = 0; i < size; i++)
    {
        ht->empty[i] = TRUE;
        ht->elements[i] = NeverUsed;
    }
}

void DestroyHT(HashTable *ht)
{
    free(ht->empty);
    free(ht->elements);
}

void ClearHT(HashTable *ht)
{
    int i;
    
    ht->num = 0;
    
    for(i = 0; i < ht->M; i++)
    {
        ht->empty[i] = TRUE;
        ht->elements[i] = NeverUsed;
    }
}

BOOL IsEmpty(HashTable *ht)
{
    if(ht->num == 0)
        return TRUE;
    else
        return FALSE;
}

BOOL IsFull(HashTable *ht)
{
    if(ht->num == ht->M)
        return TRUE;
    else
        return FALSE;
}

int Hash(int M, int key)
{
    return key % M;
}

int Search(HashTable *ht, int key)
{
    int anchor, pos;
    
    anchor = pos = Hash(ht->M, key);
    
    do{
        if(ht->empty[pos])
            return NotPresent;
        
        if(ht->elements[pos] == key)
            return pos;
        
        pos = (pos + 1) % ht->M;
    }while(pos != anchor);
    
    return NotPresent;
}

BOOL Insert(HashTable *ht, int key)
{
    int anchor, i;
    
    if(IsFull(ht))
        return FALSE;
    
    if(Search(ht, key) != NotPresent)
        return FALSE;
    
    i = anchor = Hash(ht->M, key);
    
    do{
        if(ht->elements[i] == NeverUsed)
        {
            ht->elements[i] = key;
            ht->empty[i] = FALSE;
            ht->num++;
            
            return TRUE;
        }
        
        i = (i + 1) % ht->M;
    }while(i != anchor);
    
    return FALSE;
}

BOOL Delete(HashTable *ht, int key)
{
    if(IsEmpty(ht))
        return FALSE;
    
    int pos = Search(ht, key);
    
    if(pos == NotPresent)
        return FALSE;
    else
    {
        ht->elements[pos] = NeverUsed;
        ht->num--;
        
        return TRUE;
    }
}

void Output(HashTable *ht)
{
    int i;
    
    for(i = 0; i < ht->M; i++)
        printf("%5d", ht->elements[i]);
    
    printf("\n");
    
    for(i = 0; i < ht->M; i++)
        printf("%5d", ht->empty[i]);
    
    printf("\n");
}

// Added by Bo
int main(void)
{
    HashTable ht;
    
    // I want to show the same results of Figure 8.4, p.143
    CreateHT(&ht, 11);
    
    Insert(&ht, 65);
    Insert(&ht, 40);
    Insert(&ht, 80);
    Output(&ht);
    
    printf("\n");
    
    Insert(&ht, 58);
    Insert(&ht, 24);
    Output(&ht);
    
    printf("\n");
    
    Insert(&ht, 35);
    Output(&ht);
    
    ClearHT(&ht);
    
    DestroyHT(&ht);
    
    return 0;
}
