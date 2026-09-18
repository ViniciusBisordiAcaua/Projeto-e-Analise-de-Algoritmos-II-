#include <stdio.h>
#include <stdlib.h>

#define MAX_MUSICAS 50

typedef struct {
    int m;
    int s;
    int tempo_total_seg;
}Musica;

int n_musicas;
int cap_lado_seg;
Musica musicas[MAX_MUSICAS];

int lado[MAX_MUSICAS];
int solucao_encontrada = 0;

void mostra_solucao(int caso){
    printf("Caso: %d\n", caso);
    printf("Lado A \n");
    for (int i = 0; i < n_musicas; i++){
        if(lado[i] == 1){
            printf("%dm %ds\n", musicas[i].m, musicas[i].s);
            
        }
    }
    printf("Labo B\n");
    for(int i = 0; i < n_musicas; i++){
        if(lado[i] == 2){
            printf("%dm %ds\n", musicas[i].m, musicas[i].s);
        }
    }
}

//Funcão recursiva de backtracking
void grava_fita(int idx, int tempo_ladoA, int tempo_ladoB){
    //if(solucao_encontrada) return;
    
    //Caso base: todas as músicas foram processados
    if (idx == n_musicas){
        solucao_encontrada = 1;
        return;
    }
    int i = musicas[idx].tempo_total_seg;
    
    //tenta colocar a musica no lado A 
    if (tempo_ladoA + t <= cap_lado_seg){
        lado[idx] = 1;
        grava_fita(idx + 1, tempo_ladoA + t, tempo_ladoB);
        if (solucao_encontrada) return;
        lado[idx] = 0; //backtracking
        
    }
    //tenta colocar a musica no ladoB 
    if (tempo_ladoB + t <= cop_lado_seg){
        lado[idx] = 2;
        grava_fita(idx + 1, tempo_ladoA, tempo_ladoB + t);
        if(solucao_encontrada) return;
        lado[idx] = 0; //backtracking
    }
}

int main() {
    FILE *arq = fopen("tape.in", "r");
    if (arq == NULL){
        printf("Erro ao abrir o arquivo tape.in \n");
        return 1;
    }
    int num_testes;
    if (fscanf (arq, "%d", &num_testes != 1)){
        fclose(arq);
        return 0;
    }
    for (int caso = 1; caso <= num_testes; i++){
        int tempo_total_fita_min;
        fscanf(arq, "%d %d", &tempo_total_fita_min * 60 /2);
        for (int i = 0; i < n_musicas; i++){
            fscanf(arq, "%d %d", &musicas[i].m, &musicas[i].s);
            musicas[i].tempo_total_seg = musicas[i].m * 60 + musicas[i].s;
            lado[i] = 0;
            
        }
        solucao_encontrada = 0;
        grava_fita (0, 0, 0);
        if(solucao_encontrada){
            mostra_solucao(caso);
        } else {
            printf("Caso: %d\d", caso);
            printf("Impossível grava as músicas nesta fita.\n");
        }
    }
    fclose(arq);
    return 0;
}