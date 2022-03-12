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

int hasChar(char* str, char c)
{
    for(int i = 0; i < strlen(str); i++)
    {
        if (str[i] == c)
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

    int flag = 0, i = 0;
    char excepts[] = {'-', '.'};
    char type[10];
    char varname[100];
    char scope[100];
    char ttype[100][10];
    char idname[100][100];
    char tscope[100][100];
    char tdefault[100][100];
    strcpy(scope, "global");
    while(fscanf(file, "%s", buf) != EOF)
    {
        memset(str2, 0, 100);
        strcpy(tmp, buf);
        if(hasChar(buf, '('))
        {
            split(buf, str2, '(');
        }
        if(hasChar(buf, '}'))
        {
            strcpy(scope, "global");
        }

        if(hasChar(buf, '='))
        {
            flag = 2;
        }
        
        if(flag != 2)
        {
            clean(buf);
            clean(str2);
        }

        if(isType(buf))
        {
            if(!flag)
            {
                strcpy(ttype[i], tmp);
                strcpy(tscope[i], scope);
                flag = 1;
            }
            else
            {
                strcat(ttype[i], " ");
                strcat(ttype[i], tmp);
            }
            
        }
        else if(flag == 1 && !isKeyword(buf))
        {
            flag = 0;
            strcpy(idname[i], buf);
            ++i;
        }
        if(flag == 2 && strcmp(buf, "=") != 0)
        {
            buf[strlen(buf) - 1] = '\0';    //Removes the semicolon at the end because we don't call clean for this case
            strcpy(tdefault[i - 1], buf);
            flag = 0;
        }
        if(isType(str2))
        {
            strcpy(scope, buf);
            flag = 1;
            strcpy(ttype[i], str2);
            strcpy(tscope[i], buf);
        }
    }

    int len = i;

    for(int i = 0; i < len; i++)
    {
        printf("%s\t%s\t%s\t%s\n", tscope[i], ttype[i], idname[i], tdefault[i]);
    }

    return 0;
}