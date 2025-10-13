#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

struct quadraple
{
    int pos;
    char op;
    char arg1[20];
    char arg2[20];
    char result[20];
} quad[50];

char tuple[50][50];
int n = 0;

void assignment(int);
void uminus(int);
void explore();
void codegen(const char *, int);
void optimize();

int main(void)
{
    FILE *src;
    int i;

    src = fopen("int.txt", "r");
    if (!src)
    {
        printf("Error: could not open input file.\n");
        return 1;
    }

    // Read intermediate code line by line
    while (fscanf(src, "%s", tuple[n]) != EOF)
    {
        n++;
    }
    fclose(src);

    printf("INPUT:\nIntermediate codes:\n");
    for (i = 0; i < n; i++)
        printf("%s\n", tuple[i]);

    explore();

    // Run optimization
    optimize();

    printf("\nOUTPUT:\n");
    printf("Quadruple after optimization:\n");
    printf("pos\topr\targ1\targ2\tresult\n");
    for (i = 0; i < n; i++)
    {
        if (quad[i].op != '#') // '#' = deleted instruction
            printf("%d\t%c\t%s\t%s\t%s\n", quad[i].pos, quad[i].op,
                   quad[i].arg1, quad[i].arg2, quad[i].result);
    }

    printf("\nGenerated Code:\n");
    i = 0;
    while (i < n)
    {
        if (quad[i].op == '#') // skip dead code
        {
            i++;
            continue;
        }
        if (quad[i].op == '+')
        {
            char op[5] = "ADD";
            codegen(op, i);
        }
        else if (quad[i].op == '=')
            assignment(i);
        else if (quad[i].op == '-')
        {
            if (strcmp(quad[i].arg2, "\0") == 0)
                uminus(i);
            else
            {
                char op[5] = "SUB";
                codegen(op, i);
            }
        }
        else if (quad[i].op == '*')
        {
            char op[5] = "MUL";
            codegen(op, i);
        }
        else if (quad[i].op == '/')
        {
            char op[5] = "DIV";
            codegen(op, i);
        }
        i++;
    }

    return 0;
}

// ----------------- Optimizer -----------------
void optimize()
{
    int i, val1, val2, res;
    for (i = 0; i < n; i++)
    {
        // Constant Folding (e.g., t1 = 2+3 -> t1=5)
        if (isdigit(quad[i].arg1[0]) && isdigit(quad[i].arg2[0]))
        {
            val1 = atoi(quad[i].arg1);
            val2 = atoi(quad[i].arg2);
            switch (quad[i].op)
            {
            case '+':
                res = val1 + val2;
                break;
            case '-':
                res = val1 - val2;
                break;
            case '*':
                res = val1 * val2;
                break;
            case '/':
                if (val2 != 0)
                    res = val1 / val2;
                else
                    continue;
                break;
            default:
                continue;
            }
            sprintf(quad[i].arg1, "%d", res);
            quad[i].arg2[0] = '\0';
            quad[i].op = '=';
        }

        // Dead Code Elimination (if result is never used later)
        int used = 0, j;
        for (j = i + 1; j < n; j++)
        {
            if (strcmp(quad[i].result, quad[j].arg1) == 0 ||
                strcmp(quad[i].result, quad[j].arg2) == 0)
            {
                used = 1;
                break;
            }
        }
        if (!used)
        {
            // but only eliminate temps (like t1,t2)
            if (quad[i].result[0] == 't')
                quad[i].op = '#'; // mark as deleted
        }
    }
}

// ----------------- Codegen -----------------
void codegen(const char *op, int t)
{
    printf("MOV %s,R0\n", quad[t].arg1);
    printf("%s %s,R0\n", op, quad[t].arg2);
    printf("MOV R0,%s\n", quad[t].result);
}

void assignment(int t)
{
    printf("MOV %s,%s\n", quad[t].result, quad[t].arg1);
}

void uminus(int t)
{
    printf("MOV R0,0\n");
    printf("SUB %s,R0\n", quad[t].arg1);
    printf("MOV R0,%s\n", quad[t].result);
}

// ----------------- Quadruple Builder -----------------
void explore()
{
    int i, j, t, t1, t2;
    for (i = 0; i < n; i++)
    {
        quad[i].pos = i;
        for (j = 0, t = 0; j < strlen(tuple[i]) && tuple[i][j] != '='; j++)
        {
            quad[i].result[t++] = tuple[i][j];
        }
        t1 = j;
        quad[i].result[t] = '\0';
        if (tuple[i][j] == '=')
        {
            quad[i].op = '=';
        }
        if (tuple[i][j + 1] == '+' || tuple[i][j + 1] == '-' ||
            tuple[i][j + 1] == '*' || tuple[i][j + 1] == '/')
        {
            quad[i].op = tuple[i][j + 1];
            t1 = j + 1;
        }
        for (j = t1 + 1, t = 0; j < strlen(tuple[i]) &&
                                tuple[i][j] != '+' && tuple[i][j] != '-' &&
                                tuple[i][j] != '*' && tuple[i][j] != '/';
             j++)
        {
            quad[i].arg1[t++] = tuple[i][j];
        }
        t2 = j;
        quad[i].arg1[t] = '\0';
        if (tuple[i][j] == '+' || tuple[i][j] == '-' ||
            tuple[i][j] == '*' || tuple[i][j] == '/')
        {
            quad[i].op = tuple[i][j];
        }
        for (j = t2 + 1, t = 0; j < strlen(tuple[i]); j++)
        {
            quad[i].arg2[t++] = tuple[i][j];
        }
        quad[i].arg2[t] = '\0';
    }
}
