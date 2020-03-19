// Please note:
// This is the upgraded version by Bo that can handle numbers, chars and '^'
// Examples:
// 1/(2-3)+4*5 ===> 1 2 3 - / 4 5 * +
// a/(b-c)+d*e ===> a b c - / d e * +
// b^2-4*a*c ===> b 2 ^ 4 a * c * -

// Program 3.4, partially, p.41
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// For simplicity, I added "Stack" directly in the code below...
// #include "stack.h"

#define STACKSIZE 20
#define ITEMSIZE 20
#define EXPSIZE 200

// Added by Bo
#define TRUE 1
#define FALSE 0
typedef int BOOL;

////////////////////////////////////////////////////////////////////////////////
// Extracted from Ch03_SeqStack.c

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
////////////////////////////////////////////////////////////////////////////////

// Program 3.4, partially, p.41-44
BOOL IsLegal(char *postfix)
{
    int i;
    char c;
    
    for(i = 0; i < strlen(postfix); i++)
    {
        c = postfix[i];
        
        if(!((c >= '0' && c <= '9') || c == '.' || c == '+' || c == '-'
            || c == '*' || c == '/' || c == ' ' || c == '(' || c == ')'
            || (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '^' ))
            return FALSE;
    }
    
    return TRUE;
}

// Same as the part of Program 3.3, p.37
int GetItem(char *postfix, int *curPos, char *item)
{
    int i = 0, k = *curPos, flag;
    
    if(postfix[k] == '.')
        flag = -1;
    else if( (postfix[k] >= '0' && postfix[k] <= '9') || (postfix[k] >= 'a' && postfix[k] <= 'z') || (postfix[k] >= 'A' && postfix[k] <= 'Z') )
    {
        while((postfix[k] >= '0' && postfix[k] <= '9') || (postfix[k] >= 'a' && postfix[k] <= 'z') || (postfix[k] >= 'A' && postfix[k] <= 'Z') || postfix[k] == '.')
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

int ICP(char c)
{
    if(c == '#')
        return 0;
    else if(c == '(')
        return 9;
    else if(c == '^')
        return 7;    
    else if(c == '*' || c == '/')
        return 4;
    else if(c == '+' || c == '-')
        return 2;
    else if(c == ')')
        return 1;
    else
    {
        printf("Unsupported operator: %c!\n", c);
        
        exit(0);
    }
}

int ISP(char c)
{
    if(c == '#')
        return 0;
    else if(c == '(')
        return 1;
    else if(c == '^')
        return 6;
    else if(c == '*' || c == '/')
        return 5;
    else if(c == '+' || c == '-')
        return 3;
    else if(c == ')')
        return 9;
    else
    {
        printf("Unsupported operator: %c!\n", c);
        
        exit(0);
    }
}

void InfixToPostfix(char *infix, char *postfix)
{
    Stack S;
    char item[ITEMSIZE];
    int flag = -1;
    int curPos = 0;
    int k = 0, i;
    char ch, curOP;
    
    while(infix[curPos] == ' ')
        curPos++;
    
    Create(&S, STACKSIZE);
    
    Push(&S, '#');
    
    while(curPos < strlen(infix))
    {
        flag = GetItem(infix, &curPos, item);
        
        if(flag == -1)
        {
            printf("Error: Illegal infix expression elements!\n");
            exit(0);
        }
        else if(flag == 1)
        {
            curOP = item[0];
            
            if(curOP == ')')
            {
                do
                {
                    Top(&S, &ch);
                    Pop(&S);
                    
                    if(ch == '#')
                    {
                        printf("Error: Illegal infix expression!\n");
                        exit(0);
                    }
                    
                    if(ch != '(')
                    {
                        postfix[k++] = ch;
                        postfix[k++] = ' ';
                    }
                }while(ch != '(');
            }
            else
            {
                Top(&S, &ch);
                
                while(ICP(curOP) <= ISP(ch))
                {
                    Pop(&S);
                    postfix[k++] = ch;
                    postfix[k++] = ' ';
                    Top(&S, &ch);
                }
                
                Push(&S, curOP);
            }
        }
        else
        {
            for(i = 0; i < strlen(item); i++, k++)
                postfix[k] = item[i];
                
            postfix[k++] = ' ';
        }
    }
    
    while(!IsEmpty(&S))
    {
        Top(&S, &ch);
        Pop(&S);
        
        if(ch != '#')
        {
            postfix[k++] = ch;
            postfix[k++] = ' ';
        }
    }
    
    postfix[--k] = '\0';
}

int main(int argc, char **argv)
{
    char infix[EXPSIZE];
    char postfix[EXPSIZE];
    
    printf("Please input a infix expression:%s\n", infix);
    
    // gets() is deprecated in new C standard, so I use fgets() instead...
    // But need postprocessing to replace the end of the string from '\n' to '\0'
    // gets(postfix);
    // gets_s(postfix, POSTFIXSIZE);
    fgets(infix, EXPSIZE, stdin);
    // Postprocess the string
    int i = strlen(infix);
    if(infix[i-1] == '\n')
        infix[i-1] = 0;
    
    if(!IsLegal(infix))
    {
        printf("Error: Infix expression contains illegal chars!\n");
        return -1;
    }
	
    InfixToPostfix(infix, postfix);
    
    printf("%s ===> %s\n", infix, postfix);
    
	return 0;
}
