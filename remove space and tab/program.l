

%{
    #include<stdio.h>    
%}

%%

[ \t\n]     {}

.           {printf("%s", yytext);}


%%


int main() {

    FILE *input = fopen("input.txt", "r");

    yyin = input;

    yylex();

    return 0;
}

int yywrap () {

    return 1;
}
