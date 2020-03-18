// Added by Bo
#include <stdlib.h>
#include <stdio.h>

// Added by Bo
#define FALSE 0
#define TRUE 1
typedef int BOOL;

// Added by Bo
typedef char ElemType;

// Program 3.2, p.33-34
typedef struct queue
{
    int front;
    int rear;
    
    int maxSize;
    
    ElemType *element;
}Queue;

void Create(Queue *Q, int mSize)
{
    Q->maxSize = mSize;
    Q->element = (ElemType*)malloc(sizeof(ElemType) * mSize);
    Q->front = Q->rear = 0;
}

void Destroy(Queue *Q)
{
    Q->maxSize = 0;
    free(Q->element);
    Q->front = Q->rear = -1;
}

void Clear(Queue *Q)
{
    Q->front = Q->rear = 0;
}

BOOL IsEmpty(Queue *Q)
{
    return Q->front == Q->rear;
}

BOOL IsFull(Queue *Q)
{
    return (Q->rear + 1) % Q->maxSize == Q->front;
}

BOOL Front(Queue *Q, ElemType *x)
{
    if(IsEmpty(Q))
        return FALSE;
    
    *x = Q->element[(Q->front + 1) % Q->maxSize];
    
    return TRUE;
}

BOOL EnQueue(Queue *Q, ElemType x)
{
    if(IsFull(Q))
        return FALSE;
    
    Q->rear = (Q->rear + 1) % Q->maxSize;
    Q->element[Q->rear] = x;
    
    return TRUE;
}

BOOL DeQueue(Queue *Q)
{
    if(IsEmpty(Q))
        return FALSE;
    
    Q->front = (Q->front + 1) % Q->maxSize;
    
    return TRUE;
}

// Added by Bo
void Output_ElemType_d(Queue *Q)
{
    printf("Queue: [Front] ");
    
    if(IsEmpty(Q))
    {
        printf("[Rear]\n");
        
        return;
    }
    
    int i = (Q->front + 1) % Q->maxSize;
    while(i != (Q->rear + 1) % Q->maxSize)
    {
        printf("%d ", Q->element[i]);
        
        i = (i + 1) % Q->maxSize;
    }
    
    printf("[Rear]\n");
}

// Added by Bo
void Output_ElemType_c(Queue *Q)
{
    printf("Queue: [Front] ");
    
    if(IsEmpty(Q))
    {
        printf("[Rear]\n");
        
        return;
    }
    
    int i = (Q->front + 1) % Q->maxSize;
    while(i != (Q->rear + 1) % Q->maxSize)
    {
        printf("%c ", Q->element[i]);
        
        i = (i + 1) % Q->maxSize;
    }
    
    printf("[Rear]\n");
}

// Added by Bo
int main(int argc, char **argv)
{
    Queue q;
    Create(&q, 10);
    
    ElemType c;
    for(c = 'A'; c <= 'E'; c++)
    {
        EnQueue(&q, c);
        Output_ElemType_c(&q);
    }
    
    int i;
    ElemType x;
    for(i = 0; i < 5; i++)
    {
        Front(&q, &x);
        DeQueue(&q);
        Output_ElemType_c(&q);
    }
    
    Clear(&q);
    
    Destroy(&q);
	
	return 0;
}
