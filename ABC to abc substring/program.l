%{
#include <stdio.h>
#include <string.h>
%}

%%

[a-zA-Z]+ {
    int len = yyleng;
    for (int i = 0; i < len - 2; i++) {
        if (yytext[i] == 'a' && yytext[i+1] == 'b' && yytext[i+2] == 'c') {
            yytext[i] = 'A';
            yytext[i+1] = 'B';
            yytext[i+2] = 'C';
        }
    }
    printf("%s", yytext);
}

[ \t]+        ;           // Ignore whitespace
\n            { printf("\n"); }
.             { ECHO; }   // Echo any other character

%%

int main() {
    yylex();
    return 0;
}

int yywrap() {
    return 1;
}

