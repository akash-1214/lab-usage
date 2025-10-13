%{
    #include "y.tab.h"
%}


%%

[a-zA-Z_][a-zA-Z0-9_]*      return id;
[0-9][0-9]*                 return digit;
[+/*]                       return operator;
.                           return yytext[0];
\n                          return 0;

%%

int yywrap() {

    return 1;
}

