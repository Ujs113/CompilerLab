#include<stdio.h>
#include<stdlib.h>
#include<string.h>


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

void clean(char* str)
{
    char* tmp = (char*)malloc(strlen(str));
    for(int i = 0; i < strlen(str); i++)
    {
        tmp[i] = str[i];
        if(isSpecChar(str[i]))
        {
            tmp[i] = '\0';
            break;
        }
    }

    strcpy(str, tmp);
}

int hasBraces(char* str)
{
    for(int i = 0; i < strlen(str); i++)
    {
        if (str[i] == '(')
            return 1;
    }
    return 0;
}

void split(char* str, char* str2, char delim)
{
    int i;
    char* tmp = (char*)malloc(strlen(str));
    for(i = 0; i < strlen(str); i++)
    {
        tmp[i] = str[i];
        if(isSpecChar(str[i]))
        {
            tmp[i] = '\0';
            break;
        }
    }
    ++i;
    for(int j = 0; i < strlen(str); i++, j++)
    {
        str2[j] = str[i];
    }

    strcpy(str, tmp);
}

int main(int argc, char* argv[])
{
    FILE* file = fopen(argv[1], "r");
    char buf[100], tmp[100], str2[100];
    
    if(file == NULL)
    {
        printf("Error opening file");
        return -1;
    }

    int flag = 0;
    char type[10];
    char varname[100];
    while(fscanf(file, "%s", buf) != EOF)
    {
        memset(str2, 0, 100);
        strcpy(tmp, buf);
        if(hasBraces(buf))
        {
            split(buf, str2, '(');
            
        }
        clean(buf);
        if(isType(buf))
        {
            printf("%s\t", tmp);
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
        if(str2[0] != 0)
        {
            printf("%s\t", str2);
            flag = 1;
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