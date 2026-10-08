#include <stdio.h>
#include <stdlib.h>


int comparar_decrescente(const void *a, const void *b) {
    return (*(int*)b - *(int*)a);
}

void calcular_troco_guloso(int valor_troco, int moedas[], int tamanho) {
    qsort(moedas, tamanho, sizeof(int), comparar_decrescente);

    printf("Quantidade de moedas/cedulas para o troco de %d:\n", valor_troco);

    for (int i = 0; i < tamanho; i++) {
        if (valor_troco == 0) {
            break;
        }

        int quantidade = valor_troco / moedas[i];

        if (quantidade > 0) {
            printf("%dx de %d\n", quantidade, moedas[i]);
            valor_troco %= moedas[i];
        }
    }

    if (valor_troco > 0) {
        printf("Nao foi possivel dar o troco exato. Restaram: %d\n", valor_troco);
    }
}

int main() {
    int moedas[] = {100, 50, 25, 10, 5, 1};
    int tamanho = sizeof(moedas) / sizeof(moedas[0]);
    
    int troco_desejado = 187; // Exemplo: R$ 1,87

    calcular_troco_guloso(troco_desejado, moedas, tamanho);

    return 0;
}