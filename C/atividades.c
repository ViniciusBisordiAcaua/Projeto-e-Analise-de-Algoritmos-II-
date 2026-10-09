#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int id;
    int inicio;
    int fim;
} Atividade;

// Ordena pelo horario de termino
int comparar(const void *a, const void *b) {

    Atividade *atividade1 = (Atividade *)a;
    Atividade *atividade2 = (Atividade *)b;

    return atividade1->fim - atividade2->fim;
}

int main() {

    int n;

    printf("Quantidade de atividades: ");
    scanf("%d", &n);

    Atividade atividades[n];

    for (int i = 0; i < n; i++) {

        atividades[i].id = i + 1;

        printf("\nAtividade %d\n", i + 1);

        printf("Inicio: ");
        scanf("%d", &atividades[i].inicio);

        printf("Fim: ");
        scanf("%d", &atividades[i].fim);
    }

    // Ordena pelo menor horario de termino
    qsort(atividades, n, sizeof(Atividade), comparar);

    printf("\nAtividades selecionadas:\n");

    // Primeira atividade sempre e escolhida
    printf("Atividade %d (%d, %d)\n",
           atividades[0].id,
           atividades[0].inicio,
           atividades[0].fim);

    int ultimo_fim = atividades[0].fim;
    int quantidade = 1;

    for (int i = 1; i < n; i++) {

        // Verifica se nao existe conflito
        if (atividades[i].inicio >= ultimo_fim) {

            printf("Atividade %d (%d, %d)\n",
                   atividades[i].id,
                   atividades[i].inicio,
                   atividades[i].fim);

            ultimo_fim = atividades[i].fim;

            quantidade++;
        }
    }

    printf("\nTotal de atividades selecionadas: %d\n", quantidade);

    return 0;
}