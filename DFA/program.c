#include <stdio.h>
#include <string.h>

int main() {
    char input[100];
    int state = 0; // q0 is state 0

    printf("Enter a binary string: ");
    scanf("%s", input);

    for (int i = 0; i < strlen(input); i++) {
        char c = input[i];

        switch(state) {
            case 0:
                if (c == '0') state = 0;
                else if (c == '1') state = 1;
                else {
                    printf("Invalid input character '%c'\n", c);
                    return 0;
                }
                break;

            case 1:
                if (c == '0') state = 2;
                else if (c == '1') state = 1;
                break;

            case 2:
                if (c == '0') state = 0;
                else if (c == '1') state = 1;
                break;
        }
    }

    if (state == 2)
        printf("String accepted by DFA.\n");
    else
        printf("String rejected by DFA.\n");

    return 0;
}
