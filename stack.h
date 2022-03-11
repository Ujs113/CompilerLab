#ifndef STACK_H
#define STACK_H

#include<stdlib.h>

typedef struct stack {
    char** data;
    int size;
    int top;
}stack;

void init_stack(stack* stac, unsigned int size)
{
    stac->data = (char*) malloc(sizeof(size));
}

void push(stack* stac, char* c)
{
    stac->data[stac->top] = c;
    stac->top = stac->top + 1;
}
char pop(stack* stac)
{
    char ele = stac->data[stac->top - 1];
    stac->top = stac->top - 1;
    return ele;
}


#endif