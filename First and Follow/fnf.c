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
    if(islower(symbol))
    {
        union_op(firsts, symbol);// Return the symbol itself
        return firsts;
    }
        
    else
    {
        if(nullable(symbol, rules, n))
        {
            union_op(firsts, '~');// Add epsilon('~') to first
        }
        for(int i = 0; i < n; i++)
        {
            if(rules[i].head == symbol)
            {
                if(islower(rules[i].sub[0]))
                    union_op(firsts, rules[i].sub[0]);//Add rules[i].sub[0] to first
                else
                {
                    int j = 0;
                    while(j < strlen(rules[i].sub))
                    {
                        char* x = first(rules[i].sub[j], rules, n);
                        union_of(firsts, x);//Add first(rules[i].sub[j]) to first except epsilon
                        j++;
                        if(!nullable(rules[i].sub[j], rules, n))
                        {
                            break;
                        }
                    }
                }
                
            }
        }
    }
    return firsts;
}

char* follow(char subst);

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
    production* rules;

    printf("Enter the number of productinos: ");
    scanf("%d", &n);
    fgetc(stdin);
    rules = (production*) malloc(n * sizeof(production));
    
    getProds(rules, n);

    for(int i = 0; i < n; i++)
    {
        printf("Production %d:\n", i + 1);
        printProd(rules[i]);
    }

    for(int i = 0; i < n; i++)
    {
        printf("%c\t%d\n", rules[i].head, nullable(rules[i].head, rules, n));
    }

    printf("Firsts\n");
    for(int i = 0; i < n; i++)
    {
        char *x;
        x = first(rules[i].head, rules, n);
        printf("%c\t", rules[i].head);
        for(int j = 0; j < strlen(x); j++)
        {
            printf("%c\t", x[j]);
        }
        printf("\n");
    }

    return 0;
}