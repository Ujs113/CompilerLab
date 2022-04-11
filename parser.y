%token IDENTIFIER CONSTANT STRING
%token INT CHAR FLOAT VOID CONST DOUBLE UNSIGNED LONG SHORT VOLATILE
%start declaration

%%
declaration
    : declaration_specs declaration_list ';'
    ;

declaration_specs
    : type_specs
    | type_specs declaration_specs
    | type_quals declaration_specs
    ;

type_specs
    : INT
    ;

type_quals
    : CONST
    | VOLATILE
    ;

declaration_list
    : declaration
    | declaration_list ',' declaration
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

int main(int argc, char* argv[])
{
    if(argc > 1)
    {
        FILE *fp = fopen(argv[1], "r");
        if(fp)
            yyin = fp;
    }
    yyparse();
    return 1;
}