keyword auto|double|int|struct|break|else|long|switch|case|enum|register|typedef|char|extern|return|union|continue|for|signed|void|do|if|static|while|default|goto|sizeof|volatile|const|float|short|include|define|main
punctuator [{};,()+-/=*%<>]

%%

\".*\" printf("String %s\n", yytext);
\'.\' printf("Character %s\n", yytext);
{keyword} printf("Keyword %s\n", yytext);
[a-zA-Z_]+[a-zA-Z0-9_]* printf("Identifier %s\n", yytext);
{punctuator} printf("Punctuator %s\n", yytext);
-?[0-9]+.?[0-9]* printf("Number %s\n", yytext);
.|\n ;

%%
int yywrap()
{
    return 1;
}
int main(int argc, char* argv[])
{
    if(argc > 1)
    {
        FILE *fp = fopen(argv[1], "r");
        if(fp)
        yyin = fp;
    }
    yylex();
    return 0;
}