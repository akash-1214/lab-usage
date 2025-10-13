

%{    
    #include<stdio.h>

    int valid  = 1;
%}

%token id digit operator

%%

    start : id '=' s ';'

    s : id x
        | digit x
        | '-' digit x
        | '(' s ')' x
        ;

    x : operator s
        | '-' s
        |
        ;

%%


int yyerror () {

    printf("Invalid expression");
    valid = 0;
}

int main() {

    yyparse();

    if (valid) {
        printf(" Valid expression");
    }

    return 0;
    
}

