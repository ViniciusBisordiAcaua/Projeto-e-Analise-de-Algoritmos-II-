#include <stdio.h>

void imprimir(int s[], int m) {
    for (int i = 0; i < m; i++) {
        printf("%d ", s[i]);
    }

    printf("\n");
}

void sequencias(int s[], int i, int v[], int n, int m) {

    // Caso base: sequência completa
    if (i == m) {
        imprimir(s, m);
        return;
    }

    // Coloca cada elemento de v na posição atual
    for (int j = 0; j < n; j++) {

        s[i] = v[j];

        sequencias(s, i + 1, v, n, m);
    }
}

int main() {

    int v[] = {1, 2, 3, 4};

    int n = 4;  // tamanho de v
    int m = 3;  // tamanho da sequência

    int s[3];

    sequencias(s, 0, v, n, m);

    return 0;
}