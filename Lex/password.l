%{
    int lcount = 0, ucount = 0, dcount = 0, scount = 0, ccount = 0;

%}
%%
[a-z]   {lcount++; ccount++;}
[A-Z]   {ucount++; ccount++;}
[0-9]   {dcount++; ccount++;}
[!@#$%^&*()?_,.-]   {scount++; ccount++;}
\n  {if(lcount > 0 && ucount > 0 && dcount >0 && scount >0 && ccount >= 8) printf("Valid Password\n");
        lcount = ucount = dcount = scount = ccount = 0;}
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