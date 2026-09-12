#include <stdio.h>

void imprimir(int s[], int n) {

    for (int i = 0; i < n; i++) {
        printf("%d ", s[i]);
    }

    printf("\n");
}

void permutacoes(int s[], int i, int v[], int n, int usado[]) {

    // Caso base: permutação completa
    if (i == n) {
        imprimir(s, n);
        return;
    }

    for (int j = 0; j < n; j++) {

        // Só usa o elemento se ele ainda não estiver
        // na permutação atual
        if (usado[j] == 0) {

            s[i] = v[j];

            usado[j] = 1;

            permutacoes(s, i + 1, v, n, usado);

            // Backtracking
            usado[j] = 0;
        }
    }
}

int main() {

    int v[] = {1, 2, 3};

    int n = 3;

    int s[3];

    int usado[3] = {0, 0, 0};

    permutacoes(s, 0, v, n, usado);

    return 0;
}