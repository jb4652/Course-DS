// Added by Bo
#include <stdlib.h>
#include <stdio.h>

// Added by Bo
#define FALSE 0
#define TRUE 1
typedef int BOOL;

// Added by Bo
typedef char ElemType;

// Program 3.1, p.30-31
typedef struct stack
{
    int top;
    int maxSize;
    ElemType *element;
}Stack;

void Create(Stack *S, int mSize)
{
    S->maxSize = mSize;
    S->element = (ElemType*)malloc(sizeof(ElemType) * mSize);
    S->top = -1;
}

void Destroy(Stack *S)
{
    S->maxSize = 0;
    free(S->element);
    S->top = -1;
}

void Clear(Stack *S)
{
    S->top = -1;
}

BOOL IsEmpty(Stack *S)
{
    return S->top == -1;
}

BOOL IsFull(Stack *S)
{
    return S->top == S->maxSize - 1;
}

BOOL Top(Stack *S, ElemType *x)
{
    if(IsEmpty(S))
        return FALSE;
    
    *x = S->element[S->top];
    
    return TRUE;
}

BOOL Push(Stack *S, ElemType x)
{
    if(IsFull(S))
        return FALSE;
    
    S->top++;
    S->element[S->top] = x;
    
    return TRUE;
}

BOOL Pop(Stack *S)
{
    if(IsEmpty(S))
        return FALSE;
    
    S->top--;
    
    return TRUE;
}

// Added by Bo
void Output_ElemType_d(Stack *S)
{
    int i;
    
    printf("Stack: [Top] ");
    for(i = S->top; i >= 0; i--)
        printf("%d ", S->element[i]);
    
    printf("[Bottom]\n");
}

// Added by Bo
void Output_ElemType_c(Stack *S)
{
    int i;
    
    printf("Stack: [Top] ");
    for(i = S->top; i >= 0; i--)
        printf("%c ", S->element[i]);
    
    printf("[Bottom]\n");
}

// Added by Bo
int main(int argc, char **argv)
{
    Stack s;
    Create(&s, 10);
    
    ElemType c;
    for(c = 'A'; c <= 'E'; c++)
    {
        Push(&s, c);
        Output_ElemType_c(&s);
    }
    
    int i;
    ElemType x;
    for(i = 0; i < 5; i++)
    {
        Top(&s, &x);
        Pop(&s);
        Output_ElemType_c(&s);
    }
    
    Clear(&s);
    
    Destroy(&s);
	
	return 0;
}
