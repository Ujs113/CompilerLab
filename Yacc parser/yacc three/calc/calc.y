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
 printf("\nResult: %d\n",$$);
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
}
void yyerror(){
 flag=1; 
}
