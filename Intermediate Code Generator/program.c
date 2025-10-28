#include <stdio.h>
#include <ctype.h>

int main()
{
	char expr[50];
	int t = 1;
	char op, a, b;

	printf("Enter an arithmetic expression (like b*c+a): ");
	scanf("%s", expr);

	printf("\nThree Address Code:\n");

	for (int i = 0; expr[i] != '\0'; i++)
	{
		// If it's an operator
		if (expr[i] == '+' || expr[i] == '-' || expr[i] == '*' || expr[i] == '/')
		{
			op = expr[i];
			b = expr[i + 1]; // right operand
			a = expr[i - 1]; // left operand

			if (a == 't')
			{
				printf("t%d = t%d %c %c\n", t, t - 1, op, b);
			}
			else
			{
				printf("t%d = %c %c %c\n", t, a, op, b);
			}

			expr[i + 1] = 't'; // replace left operand with result
			// expr[i] = '0' + t; // mark temp variable number
			t++;
		}
	}

	printf("\nFinal result stored in: t%d\n", t - 1);
	return 0;
}