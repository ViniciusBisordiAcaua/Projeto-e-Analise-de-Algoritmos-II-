#include <stdio.h>

#define N 8

int tabuleiro[N];

// Verifica se é possível colocar uma rainha
// na posição (linha, coluna)
int posicaoSegura(int linha, int coluna) {

    for (int i = 0; i < linha; i++) {

        // Verifica se existe rainha na mesma coluna
        if (tabuleiro[i] == coluna) {
            return 0;
        }

        // Verifica as diagonais
        if (tabuleiro[i] - i == coluna - linha ||
            tabuleiro[i] + i == coluna + linha) {
            return 0;
        }
    }

    return 1;
}

// Backtracking
int resolver(int linha) {

    // Se chegou depois da última linha,
    // encontramos uma solução
    if (linha == N) {
        return 1;
    }

    // Testa todas as colunas da linha atual
    for (int coluna = 0; coluna < N; coluna++) {

        if (posicaoSegura(linha, coluna)) {

            // Coloca a rainha
            tabuleiro[linha] = coluna;

            // Tenta colocar a próxima rainha
            if (resolver(linha + 1)) {
                return 1;
            }

            // Se não funcionou, o backtracking
            // ocorre ao tentar a próxima coluna
        }
    }

    return 0;
}

// Mostra o tabuleiro
void imprimirTabuleiro() {

    for (int linha = 0; linha < N; linha++) {

        for (int coluna = 0; coluna < N; coluna++) {

            if (tabuleiro[linha] == coluna) {
                printf("Q ");
            } else {
                printf(". ");
            }
        }

        printf("\n");
    }
}

int main() {

    if (resolver(0)) {
        printf("Solucao encontrada:\n\n");
        imprimirTabuleiro();
    } else {
        printf("Nao existe solucao.\n");
    }

    return 0;
}