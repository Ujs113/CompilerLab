#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

typedef struct production {
    char head;
    char sub[10];
} production;

int union_op(char* s1, char s2)
{
    for(int i = 0; i < strlen(s1); i++)
    {
        if(s1[i] == s2)
            return 1;
    }
    strncat(s1, &s2, 1);
    return 0;
}

int union_of(char *s1, char* s2)
{
    for(int i = 0; i < strlen(s2); i++)
    {
        union_op(s1, s2[i]);
    }
    return 0;
}

int difference(char* s1, char s2)
{
    // char* tmp = (char*)malloc((strlen(s1) + 1) * sizeof(char));
    for(int i = 0; i < strlen(s1); i++)
    {
        if(s1[i] == s2)
        {
            int j;
            for(j = i; j < strlen(s1) - 1; j++)
            {
                s1[j] = s1[j + 1];
            }
            s1[j + 1] = '\0';
            break;
        }
    }
}

int in(char* s1, char s2)
{
    for(int i = 0; i < strlen(s1); i++)
    {
        if(s1[i] == s2)
            return i;
    }
    return -1;
}

int nullable(char nt, production* prods, int n)
{
    int flag = 0;
    if(islower(nt))
    {
        return 0;
    }
    for(int i = 0; i < n; i++)
    {
        if(prods[i].head == nt)
        {
            for(int j = 0; j < strlen(prods[i].sub); j++)
            {
                if(prods[i].sub[j] == '~')
                    return 1;
                else
                {
                    flag = nullable(prods[i].sub[j], prods, n);
                }
            }
        }
    }
    return flag;
}

char* first(char symbol, production* rules, int n)
{
    char *firsts = (char*)malloc(n * sizeof(char));
    if(!isupper(symbol))
    {
        union_op(firsts, symbol);// Return the symbol itself
        return firsts;
    }
        
    else
    {
        if(nullable(symbol, rules, n))
        {
            union_op(firsts, '~');
        }
        for(int i = 0; i < n; i++)
        {
            if(rules[i].head == symbol)
            {
                if(islower(rules[i].sub[0]))
                    union_op(firsts, rules[i].sub[0]);
                else
                {
                    int j = 0;
                    while(j < strlen(rules[i].sub))
                    {
                        char* x = first(rules[i].sub[j], rules, n);
                        difference(x, '~');
                        union_of(firsts, x);
                        if(!nullable(rules[i].sub[j], rules, n))
                        {
                            break;
                        }
                        j++;
                    }
                }
                
            }
        }
    }
    return firsts;
}

char* follow(char symobl, production* rules, int n)
{
    char *follows = (char*)malloc(n * sizeof(char));
    if(symobl == 'S')
    {
        union_op(follows, '$');
    }
    for(int i = 0; i < n; i++)
    {
        int index = in(rules[i].sub, symobl);
        if(index >= 0)
        {
            if(rules[i].sub[index + 1] != '\n' && rules[i].sub[index + 1] != '\0')
            {
                if(in(first(rules[i].sub[index + 1], rules, n), '~'))
                {
                    union_of(follows, first(rules[i].sub[index + 1], rules, n));
                    difference(follows, '~');
                    union_of(follows, follow(rules[i].head, rules, n));
                }
                else
                {
                    union_of(follows, first(rules[i].sub[index + 1], rules, n));
                }
            }
            else
            {
                union_op(follows, '$');
            }
        }
    }
    return follows;
}

void getProds(production* prods, int n)
{
    for(int i = 0; i < n; i++)
    {
        printf("Enter head: ");
        prods[i].head = fgetc(stdin);
        fgetc(stdin);
        printf("Enter substitution(Enter '~' for epsilon): ");
        fgets(prods[i].sub, 10, stdin);
    }
}

void printProd(production prod)
{
    printf("%c -> %s\n", prod.head, prod.sub);
}

int main()
{
    int n;
    char *visited;
    production* rules;

    printf("Enter the number of productions: ");
    scanf("%d", &n);
    fgetc(stdin);
    rules = (production*) malloc(n * sizeof(production));
    visited = (char*)malloc(n * sizeof(char));
    getProds(rules, n);

    for(int i = 0; i < n; i++)
    {
        printf("Production %d:\n", i + 1);
        printProd(rules[i]);
    }

    printf("Firsts\n");
    for(int i = 0; i < n; i++)
    {
        if(in(visited, rules[i].head) < 0)
        {
            char *x;
            x = first(rules[i].head, rules, n);
            printf("%c\t", rules[i].head);
            for(int j = 0; j < strlen(x); j++)
            {
                printf("%c\t", x[j]);
            }
            printf("\n");
            union_op(visited, rules[i].head);
        }
    }

    memset(visited, 0, strlen(visited) + 1);

    printf("Follows\n");
    for(int i = 0; i < n; i++)
    {
        if(in(visited, rules[i].head) < 0)
        {
            char *x;
            x = follow(rules[i].head, rules, n);
            printf("%c\t", rules[i].head);
            for(int j = 0; j < strlen(x); j++)
            {
                printf("%c\t", x[j]);
            }
            printf("\n");
            union_op(visited, rules[i].head);
        }
        
    }

    return 0;
}