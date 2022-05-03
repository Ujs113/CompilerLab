#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"stack.h"

stack s, t;

int precedence[5][2] = {
    4, 5,
    4, 3,
    2, 1,
    2, 1,
    0, 0
};
char ops[5] = { 'i', '*', '+', '-', '$'};

int prec(char l, char r)
{
    int ind1, ind2;
    ind1 = ind2 = -1;
    for(int i = 0; i < 7; i++)
    {
        if(ops[i] == l)
        {
            ind1 = i;
        }
        if(ops[i] == r)
        {
            ind2 = i;
        }
    }

    if(ind1 != -1 && ind2 != -1)
    {
        int val1 = precedence[ind1][0] - precedence[ind2][1];
        return (precedence[ind1][0] - precedence[ind2][1]);
    }
    return -1;
}

void reduce()
{
    if(peek(&s) == 'i')
    {
        pop(&s);
        push(&t, 'E');
    }
    else
    {
        char x[3];
        int i = 0;
        x[0] = pop(&s);
        
        if(x[0] == '+' || x[0] == '*' || x[0] == '-')
        {
            for(int i = 1; i < 3; i++)
            {
                if(!isEmpty(&t))
                    x[i] = pop(&t);
                else
                {
                    printf("Syntax Error\n");
                    exit(-1);
                }
            }
            if(x[1] == 'E' && x[2] == 'E')
                push(&t, 'E');
        }
        else
        {
            printf("Syntax Error\n");
            exit(-1);
        }
    }
}

// E -> E+E|E*E|E-E|id
int parse(char* expr)
{
    push(&s, '$');
    for(int i = 0; i < strlen(expr); i++)
    {
        if(!isEmpty(&s))
        {
            int val = prec(expr[i], peek(&s));
            if(val > 0)
            {
                push(&s, expr[i]);
            }
            else if(val < 0)
            {
                reduce();
                --i;
            }
            else if(expr[i] == '$' && peek(&s) == '$')
                return 1;
            else
            {
                printf("Syntax Error\n");
                return -1;
            }
        }
        else
        {
            printf("Error\n");
            return -1;
        }
        
    }
    if(!isEmpty(&s))
    {
        printf("Syntax Error\n");
        return -1;
    }
}

int main()
{
    char expr[100];
    printf("Enter the expression to be parsed: ");
    scanf("%s", expr);
    strcat(expr, "$");
    init(&s);
    init(&t);
    int res = parse(expr);
    if(res > 0)
        printf("Parsing successful\n");

    return 0;
}