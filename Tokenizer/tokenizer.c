#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>


struct token {
    char type[100];
    char value[100];
};

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
                   '.', '/', ' ', '\n', '\t'};

char operator[] = { '+', '-', '/', '*', '!', '|', '<', '>', '%', '&', '=', '{', '}', '(', ')'};

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

int isOperator(char chr)
{
    for(int i = 0; i < strlen(operator); i++)
    {
        if(chr == operator[i])
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
    char *buf;
    size_t buflen;
    

    if(file == NULL)
    {
        printf("Error opening file");
        return -1;
    }

    FILE* out = open_memstream(&buf, &buflen);

    for(;;)
    {
        char tmp[4096];
        int n = fread(tmp, 1, sizeof(tmp), file);
        if(n == 0)
            break;
        fwrite(tmp, 1, n, out);
    }

    fclose(file);

    fflush(out);
    fputc('\0', out);
    fclose(out);

    char* p = buf;

    while(*p)
    {
        if(*p == '\n')
        {
            p++;
            continue;
        }

        if(isspace(*p))
        {
            p++;
            continue;
        }


    }

    return 0;
}