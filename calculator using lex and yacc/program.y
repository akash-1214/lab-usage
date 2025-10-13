

%{
    #include<stdio.h>
    int valid = 1;
%}


%token NUMBER

%%  
    ArithmeticExpression: E {

        printf("\nResult=%d\n",$$);

        return 0;

    };

    E : E '+' E {$$=$1+$3;} |
        E '-' E {$$=$1+$3;} |
        E '/' E {$$=$1/$3;} |
        E '*' E {$$=$1*$3;} | 
        E '%' E {$$=$1%$3;} |
        E '('E')'{$$=$2;}   |
        NUMBER {$$=$1;}
    ;

%%


int yyerror() {

    printf("Failed to evaluate expression");

    valid = 0;
}

int main() {


    printf("Please enter a valid expression");
    yyparse();

    if (valid) {
        printf("Expression evaluated");
    }

    return 0;


}