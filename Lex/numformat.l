digit [0-9]
%%
^(({digit},|{digit}{digit},|{digit}{digit}{digit},)?({digit}{digit}{digit},)*({digit}{digit}{digit})|({digit}{digit})|{digit})\n    printf("Accepted\n");
%%
int yywrap(void)
{
    return 1;
}

int main(void)
{
    yylex();
    return 0;
}