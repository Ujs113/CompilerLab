%{
 #include<stdio.h>
 int flag=0;
%}

%token NUMBER
%left '+' '-'
%left '*' '/' '%'
%left '(' ')'

%%
ArithmeticExpression:E{
return 0;
 };
E:E'+'E {$$=$1+$3;}
|E'-'E {$$=$1-$3;}
|E'*'E {$$=$1*$3;}
|E'/'E {$$=$1/$3;}
|E'%'E {$$=$1%$3;}
|'('E')'{$$=$2;}
| NUMBER {$$=$1;}
;

%%

int main(){
 printf("Enter the arithmetic expression : \n");
 yyparse();
 if(flag==0)
 printf("Entered arithmetic expression is valid\n\n");
}
void yyerror(){
 printf("Entered arithmetic expression is invalid\n\n");
 flag=1; 
}
