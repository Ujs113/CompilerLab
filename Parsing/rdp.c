#include<stdio.h>
#include<stdlib.h>

char *l;

void Y()
{
    if(*l == 'b')
        ++l;
    else
        printf("Error: Unexpected symbol %c. Expecting %c\n", *l, 'b');
}

void X()
{
    if(*l == 'a')
        ++l;
    else
        printf("Error: Unexpected symbol %c. Expecting %c\n", *l, 'a');
    
    Y();
}

void S()
{
    X();
    Y();
}

int main()
{
    char line[100];
    printf("Enter statement: ");
    scanf("%s", line);
    l = line;
    S();
    if(*l != '\0')
        printf("Error: Unexpected symbol(s) %s, expecting EOF\n", l);
    printf("Parsing finished\n");
    return 0;
}