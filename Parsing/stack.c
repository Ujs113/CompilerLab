#include"stack.h"

void init(stack *s)
{
    s->top = -1;
}

int push(stack *s, char c)
{
    if(s->top != 100)
    {
        s->val[++(s->top)] = c;
        return 0;
    }
    
    return -1;
}

char peek(stack *s)
{
    if(s->top != -1)
        return s->val[s->top];
    return '\0';
}

char pop(stack *s)
{
    if(s->top != -1)
    {
        char tmp = s->val[s->top];
        --s->top;
        return tmp;
    }
    
    return '\0';
}

int isEmpty(stack *s)
{
    if(s->top != -1)
        return 0;
    return 1;
}