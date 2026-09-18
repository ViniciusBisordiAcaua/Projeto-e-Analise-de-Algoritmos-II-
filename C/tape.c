#include <stdio.h>
#include <stdlib.h>

#define MAX_MUSICAS 50

typedef struct {
    int m;
    int s;
    int tempo_total_seg;
} Musica;

int n_musicas;
int cap_lado_seg;

Musica musicas[MAX_MUSICAS];

int lado[MAX_MUSICAS];

int solucao_encontrada = 0;


// Mostra a solução encontrada
void mostra_solucao(int caso) {

    printf("Caso:%d\n", caso);

    printf("Lado A\n");

    for (int i = 0; i < n_musicas; i++) {

        if (lado[i] == 1) {

            printf(
                "%dm %ds\n",
                musicas[i].m,
                musicas[i].s
            );
        }
    }

    printf("Lado B\n");

    for (int i = 0; i < n_musicas; i++) {

        if (lado[i] == 2) {

            printf(
                "%dm %ds\n",
                musicas[i].m,
                musicas[i].s
            );
        }
    }
}


// Função recursiva de backtracking
void grava_fita(
    int idx,
    int tempo_ladoA,
    int tempo_ladoB
) {

    // Se já encontrou uma solução, encerra
    if (solucao_encontrada) {
        return;
    }

    // Caso base:
    // todas as músicas foram processadas
    if (idx == n_musicas) {

        solucao_encontrada = 1;

        return;
    }


    // Tempo da música atual em segundos
    int t = musicas[idx].tempo_total_seg;


    // Tenta colocar a música no lado A
    if (tempo_ladoA + t <= cap_lado_seg) {

        lado[idx] = 1;

        grava_fita(
            idx + 1,
            tempo_ladoA + t,
            tempo_ladoB
        );

        if (solucao_encontrada) {
            return;
        }

        // Backtracking
        lado[idx] = 0;
    }


    // Tenta colocar a música no lado B
    if (tempo_ladoB + t <= cap_lado_seg) {

        lado[idx] = 2;

        grava_fita(
            idx + 1,
            tempo_ladoA,
            tempo_ladoB + t
        );

        if (solucao_encontrada) {
            return;
        }

        // Backtracking
        lado[idx] = 0;
    }
}


int main(void) {

    FILE *arq = fopen("tape.in", "r");


    if (arq == NULL) {

        printf("Erro ao abrir o arquivo tape.in\n");

        return 1;
    }


    int num_testes;


    // Lê quantidade de casos
    if (fscanf(arq, "%d", &num_testes) != 1) {

        printf("Erro ao ler quantidade de casos.\n");

        fclose(arq);

        return 1;
    }


    for (int caso = 1; caso <= num_testes; caso++) {

        int tempo_total_fita_min;


        // Lê duração total da fita e número de músicas
        if (fscanf(
                arq,
                "%d %d",
                &tempo_total_fita_min,
                &n_musicas
            ) != 2) {

            printf("Erro ao ler o caso %d.\n", caso);

            fclose(arq);

            return 1;
        }


        // Cada lado possui metade da duração total da fita
        cap_lado_seg =
            (tempo_total_fita_min * 60) / 2;


        // Lê todas as músicas
        for (int i = 0; i < n_musicas; i++) {

            if (fscanf(
                    arq,
                    "%d %d",
                    &musicas[i].m,
                    &musicas[i].s
                ) != 2) {

                printf("Erro ao ler musica.\n");

                fclose(arq);

                return 1;
            }


            // Converte minutos e segundos para segundos
            musicas[i].tempo_total_seg =
                musicas[i].m * 60 +
                musicas[i].s;


            lado[i] = 0;
        }


        solucao_encontrada = 0;


        // Inicia o backtracking
        grava_fita(0, 0, 0);


        if (solucao_encontrada) {

            mostra_solucao(caso);

        } else {

            printf("Caso:%d\n", caso);

            printf(
                "Impossivel gravar as musicas nessa fita.\n"
            );
        }


        if (caso < num_testes) {
            printf("\n");
        }
    }


    fclose(arq);

    return 0;
}