// Program 3.3, partially, p.37
// For simplicity, I added "Stack" directly in the code below...
// #include "stack.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STACKSIZE 20
#define ITEMSIZE 20
#define POSTFIXSIZE 200

// Added by Bo
#define TRUE 1
#define FALSE 0
typedef int BOOL;

////////////////////////////////////////////////////////////////////////////////
// Extracted from Ch03_SeqStack.c

// Added by Bo
typedef double ElemType;

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
////////////////////////////////////////////////////////////////////////////////

// Program 3.3, partially, p.37-39
BOOL IsLegal(char *postfix)
{
    int i;
    char c;
    
    for(i = 0; i < strlen(postfix); i++)
    {
        c = postfix[i];
        
        if(!((c >= '0' && c <= '9') || c == '.' || c == '+' || c == '-'
            || c == '*' || c == '/' || c == '^' || c == ' ') )
            return FALSE;
    }
    
    return TRUE;
}

int GetItem(char *postfix, int *curPos, char *item)
{
    int i = 0, k = *curPos, flag;
    
    if(postfix[k] == '.')
        flag = -1;
    else if( (postfix[k] >= '0' && postfix[k] <= '9') )
    {
        while((postfix[k] >= '0' && postfix[k] <= '9') || postfix[k] == '.')
            item[i++] = postfix[k++];
        
        item[i] = '\0';
        
        flag = 0;
    }
    else
    {
        item[0] = postfix[k++];
        item[1] = '\0';
        flag = 1;
    }
    
    while(postfix[k] == ' ')
        k++;
    
    *curPos = k;
    
    return flag;
}

void DoOperator(Stack *S, char oper)
{
    double oper1, oper2;
    
    if(!Top(S, &oper1))
    {
        printf("Error: Postfix expression error, extra operators exists!\n");
        exit(0);
    }
    
    Pop(S);
    
    if(!Top(S, &oper2))
    {
        printf("Error: Postfix expression error, extra operators exists!\n");
        exit(0);
    }
    
    Pop(S);
    
    switch(oper)
    {
    case '+':
        Push(S, oper2 + oper1);
        break;
    case '-':
        Push(S, oper2 - oper1);
        break;
    case '*':
        Push(S, oper2 * oper1);
        break;
    case '/':
        if(fabs(oper1) < 1e-6)
        {
            printf("Error: oper1 is zero!\n");
            exit(0);
        }
        else
            Push(S, oper2 / oper1);
        break;
    case '^':
        Push(S, pow(oper2, oper1));
        break;
    }
}

double Calcuting(char *postfix)
{
    Stack S;
    char item[ITEMSIZE];
    double data;
    int flag = -1;
    int curPos = 0;
    
    while(postfix[curPos] == ' ')
        curPos++;
    
    Create(&S, STACKSIZE);
    
    while(curPos < strlen(postfix))
    {
        flag = GetItem(postfix, &curPos, item);
        
        if(flag == -1)
        {
            printf("Error: Illegal postfix expression elements!\n");
            exit(0);
        }
        else if(flag == 1)
        {
            switch(item[0])
            {
            case '+':
            case '-':
            case '*':
            case '/':
            case '^':
                DoOperator(&S, item[0]);
                break;
            }
        }
        else
        {
            data = atof(item);
            Push(&S, data);
        }
    }
    
    if(S.top == 0)
        Top(&S, &data);
    else
    {
        printf("Error: Postfix expression error, extra numbers exists!\n");
        exit(0);
    }
    
    Destroy(&S);
    
    return data;
}

int main(int argc, char **argv)
{
    char postfix[POSTFIXSIZE];
    
    printf("Please input a postfix expression (Use space to separate successive numbers):\n");
    
    // gets() is deprecated in new C standard, so I use fgets() instead...
    // But need postprocessing to replace the end of the string from '\n' to '\0'
    // gets(postfix);
    // gets_s(postfix, POSTFIXSIZE);
    fgets(postfix, POSTFIXSIZE, stdin);
    // Postprocess the string
    int i = strlen(postfix);
    if(postfix[i-1] == '\n')
        postfix[i-1] = 0;
    
    if(!IsLegal(postfix))
    {
        printf("Error: Postfix expression contains illegal chars!\n");
        return -1;
    }
	
    printf("%s = %.2f\n", postfix, Calcuting(postfix));
    
	return 0;
}
