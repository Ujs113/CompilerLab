#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"stack.h"


char types[][10] = {"int", "float", "char", "double", "void", "auto", "unsigned", "long", "const"};

char key[][32] = { "int", "float", "char", "auto", "break", "case",
                    "const", "continue", "default", "do", "double", "else", 
                    "enum", "extern", "for", "goto", "if", "long", "register",
                    "return", "short", "signed", "sizeof", "static", "struct",
                    "switch", "typedef", "union", "unsigned", "void", "volatile",
                    "while" };

char special[] = {'~', '|', '#', '$', '%', '^', '&',
                   '*', '(', ')', '_', '+', '!', '\\',
                   '`', '-', '=', '{', '}', '[', ']',
                   ':', '"', ';', '<', '>', '?', ',',
                   '.', '/' };

int isType(char* word)
{
    for(int i = 0; i < 9; i++)
    {
        if(strcmp(word, types[i]) == 0)
        {
            return 1;
        }
    }

    return 0;
}

int isKeyword(char* word)
{
    for(int i = 0; i < 32; i++)
    {
        if(strcmp(word, key[i]) == 0)
        {
            return 1;
        }
    }
    return 0;
}

int isSpecChar(char chr)
{
    for(int i = 0; i < strlen(special); i++)
    {
        if(chr == special[i])
            return 1;
    }

    return 0;
}

int hasSpecChar(char* str)
{
    for(int i = 0; i < strlen(str); i++)
    {
        if(isSpecChar(str[i]))
            return 1;
    }
    return 0;
}

// void clean(char* str)
// {
//     char* tmp = (char*)malloc(strlen(str));
//     for(int i = 0; i < strlen(str); i++)
//     {
//         tmp[i] = str[i];
//         if(isSpecChar(str[i]))
//         {
//             tmp[i] = '\0';
//             break;
//         }
//     }

//     strcpy(str, tmp);
// }

char clean(char* str)
{
    char* tmp = (char*)malloc(strlen(str));
    char c;
    for(int i = 0; i < strlen(str); i++)
    {
        tmp[i] = str[i];
        if(isSpecChar(str[i]))
        {
            c = str[i];
            tmp[i] = '\0';
            break;
        }
    }
    strcpy(str, tmp);
    return c;
}

int main(int argc, char* argv[])
{
    FILE* file = fopen(argv[1], "r");
    char buf[100], tmp[100];
    
    if(file == NULL)
    {
        printf("Error opening file");
        return -1;
    }

    stack s;
    init_stack(&s, 100);

    int flag = 0;
    char type[10];
    char varname[100];
    while(fscanf(file, "%s", buf) != EOF)
    {
        strcpy(tmp, buf);
        clean(buf);
        if(isType(buf))
        {
            printf("%s\t", tmp);
            //push(&s, buf);
            flag = 1;
        }
        if(flag && isSpecChar(buf))
        {
            flag = 0;
        }
        if(flag && !isKeyword(buf))
        {
            printf("%s\n", buf);
            flag = 0;
        }
    }

    return 0;
}

/*

TODO: Check if a given input is a function.
How?
Suggestion:
When cleaning if the special character is '(', then parse input until ')' is found. Then it is function.

*/