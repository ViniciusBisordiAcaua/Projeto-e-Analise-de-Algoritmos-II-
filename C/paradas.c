#include <stdio.h>

int main() {
    int n, autonomia, destino;

    printf("Quantidade de postos: ");
    scanf("%d", &n);

    int postos[n + 2];

    postos[0] = 0;

    printf("Digite a posicao dos postos:\n");

    for (int i = 1; i <= n; i++) {
        scanf("%d", &postos[i]);
    }

    printf("Digite a distancia do destino: ");
    scanf("%d", &destino);

    printf("Digite a autonomia do carro: ");
    scanf("%d", &autonomia);

    postos[n + 1] = destino;

    int atual = 0;
    int quantidade_paradas = 0;

    printf("\nCaminho: 0");

    while (atual < n + 1) {

        int proximo = atual;

        // Procura o ponto mais distante que ainda pode ser alcancado
        for (int i = atual + 1; i <= n + 1; i++) {

            if (postos[i] - postos[atual] <= autonomia) {
                proximo = i;
            } else {
                break;
            }
        }

        if (proximo == atual) {
            printf("\nNao e possivel chegar ao destino.\n");
            return 0;
        }

        atual = proximo;

        printf(" -> %d", postos[atual]);

        // Destino nao conta como parada
        if (atual != n + 1) {
            quantidade_paradas++;
        }
    }

    printf("\nQuantidade de paradas: %d\n", quantidade_paradas);

    return 0;
}