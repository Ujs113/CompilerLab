%%
^[a-zA-Z0-9+_.-]+@[a-zA-Z0-9.-]+$   printf("Valid E-mail id");
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