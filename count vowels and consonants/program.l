

%{
    int vowels = 0, consos = 0;
%}

%%

[aeiou] {vowels++;}

[A-Za-z] {consos++;}

%%


int main () {

    FILE *input = fopen("input.txt", "r");

    yyin = input;

    yylex();

    printf("Number of vowels and consonants are %d and %d", vowels, consos);

    return 0;
}

int yywrap () {
    return 1;
}