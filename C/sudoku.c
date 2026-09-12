#include <stdio.h>

#define TAM 9

void imprimirSudoku(int sudoku[TAM][TAM]) {

    for (int i = 0; i < TAM; i++) {

        for (int j = 0; j < TAM; j++) {
            printf("%d ", sudoku[i][j]);
        }

        printf("\n");
    }
}


// Verifica se o número pode ser colocado na posição
int valido(int sudoku[TAM][TAM], int linha, int coluna, int numero) {

    // Verifica a linha
    for (int j = 0; j < TAM; j++) {

        if (sudoku[linha][j] == numero) {
            return 0;
        }
    }


    // Verifica a coluna
    for (int i = 0; i < TAM; i++) {

        if (sudoku[i][coluna] == numero) {
            return 0;
        }
    }


    // Descobre onde começa o bloco 3x3
    int inicioLinha = linha - linha % 3;
    int inicioColuna = coluna - coluna % 3;


    // Verifica o bloco 3x3
    for (int i = 0; i < 3; i++) {

        for (int j = 0; j < 3; j++) {

            if (sudoku[inicioLinha + i][inicioColuna + j] == numero) {
                return 0;
            }
        }
    }


    return 1;
}


int resolverSudoku(int sudoku[TAM][TAM]) {

    int linha = -1;
    int coluna = -1;
    int vazio = 0;


    // Procura uma posição vazia
    for (int i = 0; i < TAM; i++) {

        for (int j = 0; j < TAM; j++) {

            if (sudoku[i][j] == 0) {

                linha = i;
                coluna = j;
                vazio = 1;

                break;
            }
        }

        if (vazio) {
            break;
        }
    }


    // Caso base:
    // se não existir nenhuma posição vazia,
    // o Sudoku está resolvido
    if (!vazio) {
        return 1;
    }


    // Tenta números de 1 até 9
    for (int numero = 1; numero <= 9; numero++) {

        if (valido(sudoku, linha, coluna, numero)) {

            sudoku[linha][coluna] = numero;


            // Chamada recursiva
            if (resolverSudoku(sudoku)) {
                return 1;
            }


            // Backtracking:
            // o número escolhido não levou à solução
            sudoku[linha][coluna] = 0;
        }
    }


    return 0;
}


int main() {

    int sudoku[TAM][TAM] = {

        {5, 3, 0, 0, 7, 0, 0, 0, 0},
        {6, 0, 0, 1, 9, 5, 0, 0, 0},
        {0, 9, 8, 0, 0, 0, 0, 6, 0},

        {8, 0, 0, 0, 6, 0, 0, 0, 3},
        {4, 0, 0, 8, 0, 3, 0, 0, 1},
        {7, 0, 0, 0, 2, 0, 0, 0, 6},

        {0, 6, 0, 0, 0, 0, 2, 8, 0},
        {0, 0, 0, 4, 1, 9, 0, 0, 5},
        {0, 0, 0, 0, 8, 0, 0, 7, 9}

    };


    printf("Sudoku inicial:\n\n");

    imprimirSudoku(sudoku);


    if (resolverSudoku(sudoku)) {

        printf("\nSudoku resolvido:\n\n");

        imprimirSudoku(sudoku);

    } else {

        printf("\nNao existe solucao.\n");
    }


    return 0;
}