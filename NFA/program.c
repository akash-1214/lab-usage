#include <stdio.h>
#include <stdlib.h>

#define MAX_STATES 10

int n; // number of states
int epsilon[MAX_STATES][MAX_STATES]; // adjacency matrix for epsilon transitions

int visited[MAX_STATES]; // for DFS

void dfs(int state, int closure[]) {
    closure[state] = 1; // include this state
    visited[state] = 1;

    for (int next = 0; next < n; next++) {
        if (epsilon[state][next] && !visited[next]) {
            dfs(next, closure);
        }
    }
}

void epsilon_closure(int state) {
    int closure[MAX_STATES] = {0};

    // reset visited array
    for (int i = 0; i < n; i++) visited[i] = 0;

    dfs(state, closure);

    printf("Epsilon-closure(%d): { ", state);
    for (int i = 0; i < n; i++) {
        if (closure[i]) printf("%d ", i);
    }
    printf("}\n");
}

int main() {
    n = 3; // number of states

    // initialize epsilon matrix to 0
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            epsilon[i][j] = 0;

    // define epsilon transitions
    epsilon[0][1] = 1;
    epsilon[1][2] = 1;

    // compute epsilon closure for all states
    for (int i = 0; i < n; i++) {
        epsilon_closure(i);
    }

    return 0;
}
