#include <stdio.h>

void gerarBinarios(char binario[], int posicao, int n) {
    // Caso base: completou n posições
    if (posicao == n) {
        binario[n] = '\0';
        printf("%s\n", binario);
        return;
    }

    // Coloca 0 na posição atual
    binario[posicao] = '0';
    gerarBinarios(binario, posicao + 1, n);

    // Coloca 1 na posição atual
    binario[posicao] = '1';
    gerarBinarios(binario, posicao + 1, n);
}

int main() {
    int n;

    printf("Digite o tamanho n: ");
    scanf("%d", &n);

    char binario[n + 1];

    printf("Saida:\n");
    gerarBinarios(binario, 0, n);

    return 0;
}