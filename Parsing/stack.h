#ifndef STACK_H
#define STACK_H

typedef struct stack {
    char val[100];
    int top;
} stack;

void init(stack *s);
int push(stack *s, char c);
char peek(stack *s);
char pop(stack *s);
int isEmpty(stack *s);


#endif