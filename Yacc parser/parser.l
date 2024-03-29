%{
    #include<stdio.h>
    #include"y.tab.h"
%}

%%

"char"  {return(CHAR);}
"const" {return(CONST);}
"int"   {return(INT);}
"float" {return(FLOAT);}
"void"  {return(VOID);}
"double"    {return(DOUBLE);}
"unsigned"  {return(UNSIGNED);}
"short" {return(SHORT);}
"long"  {return(LONG);}
"volatile"  {return(VOLATILE);}
[a-zA-Z_]([a-zA-Z_]|[0-9])* {return(IDENTIFIER);}
\".*\"  {return(STRING);}
-?[0-9]+.?[0-9]*    {return(CONSTANT);}
\'.\'   {return(CONSTANT);}
"," {return(',');}
";" {return(';');}
"=" {return('=');}

%%

yywrap()
{
    return (1);
}