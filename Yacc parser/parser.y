%token IDENTIFIER CONSTANT STRING
%token INT CHAR FLOAT VOID CONST DOUBLE UNSIGNED LONG SHORT VOLATILE
%start declaration

%{
    int flag = 0;
%}

%%
declaration
    : declaration_specs declaration ';'    { return 0; }
    ;

declaration_specs
    : INT
    | FLOAT
    | SHORT
    | UNSIGNED
    | LONG
    | CHAR
    | VOID
    | DOUBLE
    ;

declaration
    : IDENTIFIER
    | IDENTIFIER '=' value
    ;

value
    : CONSTANT
    | STRING
    | IDENTIFIER
    ;

%%
#include"lex.yy.c"

void yyerror(char* s)
{  
    fprintf (stderr, "%s\nInvalid variable declaration", s);
    flag = 1;
}

int main()
{
    yyparse();
    if (flag == 0)
    {
        printf("Valid variable declaration");
    }
    return 1;
}