#include <stdio.h>

int main() {
    int n, alcance;

    printf("Quantidade de pedras: ");
    scanf("%d", &n);

    int posicoes[n];

    printf("Digite as posicoes das pedras:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &posicoes[i]);
    }

    printf("Alcance maximo do sapo: ");
    scanf("%d", &alcance);

    int atual = 0;
    int saltos = 0;

    printf("\nCaminho: %d", posicoes[0]);

    while (atual < n - 1) {

        int proximo = atual;

        // Procura a pedra mais distante que o sapo consegue alcancar
        for (int i = atual + 1; i < n; i++) {

            if (posicoes[i] - posicoes[atual] <= alcance) {
                proximo = i;
            } else {
                break;
            }
        }

        // Nenhuma pedra pode ser alcancada
        if (proximo == atual) {
            printf("\nNao e possivel chegar ao destino.\n");
            return 0;
        }

        atual = proximo;
        saltos++;

        printf(" -> %d", posicoes[atual]);
    }

    printf("\nNumero de saltos: %d\n", saltos);

    return 0;
}