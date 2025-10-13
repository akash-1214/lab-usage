

%{
    int lines = 0, characters = 0;
%}


%%

\n         {lines++;}

[ \t]       {}

.           {characters++;}

%%


int main () {

    FILE *input = fopen("input.txt", "r");

    yyin = input;

    yylex();

    printf("Number of lines and characters are %d and %d", lines, characters);

    return 0;
}

int yywrap () {
    return 1; // 1 means no further processing and 0 means further processing
}