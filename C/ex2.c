#include <stdio.h>

void gerarSequencias(char sequencia[], int posicao, int golsA, int golsB) {
    // Caso base: todos os gols já foram utilizados
    if (golsA == 0 && golsB == 0) {
        sequencia[posicao] = '\0';
        printf("%s\n", sequencia);
        return;
    }

    // Se ainda existem gols do time A
    if (golsA > 0) {
        sequencia[posicao] = 'A';
        gerarSequencias(sequencia, posicao + 1, golsA - 1, golsB);
    }

    // Se ainda existem gols do time B
    if (golsB > 0) {
        sequencia[posicao] = 'B';
        gerarSequencias(sequencia, posicao + 1, golsA, golsB - 1);
    }
}

int main() {
    int m, n;

    printf("Digite os gols do time A: ");
    scanf("%d", &m);

    printf("Digite os gols do time B: ");
    scanf("%d", &n);

    char sequencia[m + n + 1];

    printf("Possiveis sucessoes de gols:\n");
    gerarSequencias(sequencia, 0, m, n);

    return 0;
}