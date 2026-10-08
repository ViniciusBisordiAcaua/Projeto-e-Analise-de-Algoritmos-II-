#include <stdio.h>
#include <stdlib.h>

// Estrutura para representar cada objeto
typedef struct {
    int id;
    double valor;
    double peso;
    double razao;
} Objeto;

// Ordenar os objetos pela razao valor/peso (decrescente)
int comparar(const void *a, const void *b) {
    Objeto *obj1 = (Objeto *)a;
    Objeto *obj2 = (Objeto *)b;

    if (obj1->razao < obj2->razao)
        return 1;

    if (obj1->razao > obj2->razao)
        return -1;

    return 0;
}

// Algoritmo guloso da mochila fracionaria
void mochila_fracionaria(Objeto objetos[], int n, double capacidade) {

    // Ordenar os objetos pela razao valor/peso
    qsort(objetos, n, sizeof(Objeto), comparar);

    double valor_total = 0;

    printf("\nObjetos colocados na mochila:\n");

    for (int i = 0; i < n && capacidade > 0; i++) {

        if (objetos[i].peso <= capacidade) {

            // Coloca o objeto inteiro
            printf("Objeto %d: 100%%\n", objetos[i].id);

            capacidade -= objetos[i].peso;
            valor_total += objetos[i].valor;

        } else {

            // Coloca uma fracao do objeto
            double fracao = capacidade / objetos[i].peso;

            printf("Objeto %d: %.2f%%\n",
                   objetos[i].id, fracao * 100);

            valor_total += objetos[i].valor * fracao;

            capacidade = 0;
        }
    }

    printf("\nValor total da mochila: %.2f\n", valor_total);
}

int main() {

    int n;
    double capacidade;

    printf("Digite a quantidade de objetos: ");
    if (scanf("%d", &n) != 1 || n <= 0 || n > 100) {
        printf("Quantidade invalida (permitido de 1 a 100).\n");
        return 1;
    }

    Objeto objetos[100];

    printf("Digite a capacidade da mochila: ");
    if (scanf("%lf", &capacidade) != 1 || capacidade < 0) {
        printf("Capacidade invalida.\n");
        return 1;
    }

    for (int i = 0; i < n; i++) {

        objetos[i].id = i + 1;

        printf("\nObjeto %d\n", i + 1);

        printf("Valor: ");
        if (scanf("%lf", &objetos[i].valor) != 1 ||
            objetos[i].valor < 0) {
            printf("Valor invalido.\n");
            return 1;
        }

        printf("Peso: ");
        if (scanf("%lf", &objetos[i].peso) != 1 ||
            objetos[i].peso <= 0) {
            printf("Peso invalido.\n");
            return 1;
        }

        objetos[i].razao = objetos[i].valor / objetos[i].peso;
    }

    mochila_fracionaria(objetos, n, capacidade);

    return 0;
}