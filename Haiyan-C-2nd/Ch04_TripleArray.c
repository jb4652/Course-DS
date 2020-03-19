// Added by Bo
#include <stdlib.h>
#include <stdio.h>

// Program 4.1, partially, p.51
#define ERROR 0
#define OK 1
#define NotPresent 2
#define Duplicate 3
#define IllegalIndex 4
typedef int Status;

// Program, p.51
typedef struct triplearray
{
    int m1;
    int m2;
    int m3;
    
    int *array;
}TripleArray;

// Program 4.1, partially, p.51-53
Status CreateArray(TripleArray *tripleArray, int m1, int m2, int m3)
{
    tripleArray->m1 = m1;
    tripleArray->m2 = m2;
    tripleArray->m3 = m3;

    tripleArray->array = (int*)malloc(m1 * m2 * m3 * sizeof(int));
    if(!tripleArray->array)
        return ERROR;
    
    return OK;
}

Status DestroyArray(TripleArray *tripleArray)
{
    if(!tripleArray)
        return ERROR;
    
    if(tripleArray->array)
        free(tripleArray->array);
    
    // This line is wrong and is of no need, comment out...
    // free(tripleArray);
    
    return OK;
}

Status RetrieveArray(TripleArray tripleArray, int i1, int i2, int i3, int *x)
{
    if(!tripleArray.array)
        return NotPresent;
    
    if(i1 < 0 || i2 < 0 || i3 < 0 || i1 >= tripleArray.m1 || i2 >= tripleArray.m2 || i3 >= tripleArray.m3)
        return IllegalIndex;
    
    *x = *(tripleArray.array + i1 * tripleArray.m2 * tripleArray.m3 + i2 * tripleArray.m3 + i3);
    
    return OK;
}

Status StoreArrayItem(TripleArray *tripleArray, int i1, int i2, int i3, int x)
{
    if(!tripleArray->array)
        return NotPresent;
    
    if(i1 < 0 || i2 < 0 || i3 < 0 || i1 >= tripleArray->m1 || i2 >= tripleArray->m2 || i3 >= tripleArray->m3)
        return IllegalIndex;
    
    *(tripleArray->array + i1 * tripleArray->m2 * tripleArray->m3 + i2 * tripleArray->m3 + i3) = x;
    
    return OK;
}

void OutputArray(TripleArray tripleArray)
{
    int i1, i2, i3;
    
    if(!tripleArray.array)
        return;
    
    for(i1 = 0; i1 < tripleArray.m1; i1++)
        for(i2 = 0; i2 < tripleArray.m2; i2++)
            for(i3 = 0; i3 < tripleArray.m3; i3++)
            {
                int value;
                
                RetrieveArray(tripleArray, i1, i2, i3, &value);
                
                printf("array[%d][%d][%d] = %d\n", i1, i2, i3, value);
            }
}

Status CopyArray(TripleArray *tripleArrayA, TripleArray *tripleArrayB)
{
    int i1, i2, i3;
    
    if(!tripleArrayA->array || !tripleArrayB->array)
        return NotPresent;
    
    if(tripleArrayA->array == tripleArrayB->array)
        return Duplicate;
    
    if(tripleArrayA->m1 != tripleArrayB->m1 || tripleArrayA->m2 != tripleArrayB->m2 || tripleArrayA->m3 != tripleArrayB->m3)
        return ERROR;
    
    for(i1 = 0; i1 < tripleArrayA->m1; i1++)
        for(i2 = 0; i2 < tripleArrayA->m2; i2++)
            for(i3 = 0; i3 < tripleArrayA->m3; i3++)
            {
                int value;
                
                RetrieveArray(*tripleArrayA, i1, i2, i3, &value);
                
                StoreArrayItem(tripleArrayB, i1, i2, i3, value);
            }
    
    return OK;
}

// Program 4.2, p.53
int main(void)
{
    int i1, i2, i3;
    
    TripleArray tripleArrayA, tripleArrayB;
    
    CreateArray(&tripleArrayA, 2, 2, 2);
    CreateArray(&tripleArrayB, 2, 2, 2);
    
    for(i1 = 0; i1 < tripleArrayA.m1; i1++)
        for(i2 = 0; i2 < tripleArrayA.m2; i2++)
            for(i3 = 0; i3 < tripleArrayA.m3; i3++)
            {
                StoreArrayItem(&tripleArrayA, i1, i2, i3, 10);
                
                StoreArrayItem(&tripleArrayB, i1, i2, i3, 5);
            }
    
    printf("Triple Array A before copy:\n");
    OutputArray(tripleArrayA); printf("\n");
    printf("Triple Array B before copy:\n");
    OutputArray(tripleArrayB); printf("\n");
    
    CopyArray(&tripleArrayA, &tripleArrayB);
    
    printf("Triple Array A after copy:\n");
    OutputArray(tripleArrayA); printf("\n");
    printf("Triple Array B after copy:\n");
    OutputArray(tripleArrayB); printf("\n");
    
    DestroyArray(&tripleArrayA);
    DestroyArray(&tripleArrayB);
}
