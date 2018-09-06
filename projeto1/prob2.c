#include <stdio.h>
#include <stdlib.h>
#define TAMANHO 10

int* recebe_notas(float*, int, int*);
void conta_notas(int*, int, int*, int*);
int percent_aprov(int*, int*, int*, int*,int);

int main(){

    // declarações
    float notas[TAMANHO];
    int APR[TAMANHO];
    int* p;
    int* apro;
    int* repro;
    int* per_apro;
    int* per_repro;
    int aprovados=0, reprovados=0, per_aprovados=0, per_reprovados=0;
    int maioria;

    // link de variavéis
    apro = &aprovados;
    repro = &reprovados;
    per_apro= &per_aprovados;
    per_repro= &per_reprovados;

    // Solicitação de entrada de dados, satisfaz item D.
    printf("Entre com as notas:\n");
    for(int i = 0; i < TAMANHO; i++){
        scanf("%f", &notas[i]);
    }

    // Call das funções, satisfaz item D.
    p = recebe_notas(notas,TAMANHO,APR);
    conta_notas(APR,TAMANHO,apro,repro);
    maioria = percent_aprov(apro,repro,per_apro,per_repro,TAMANHO);

    // Apresentação de resultados, satisfaz item D.
    printf("Quantidade de aprovados: %d\n", *apro);
    printf("Quantidade de reprovados: %d\n", *repro);
    printf("Percentual de aprovados: %d\n", *per_apro);
    printf("Percentual de rerovados: %d\n", *per_repro);

    if(maioria == 1){
      printf("Mais da medate da turma aprovada!\n");
    }else{
      printf("Menos da medate da turma reprovada!\n");
    }
    
    return 0;
}

//Função recebe_notas, satisfaz item A.
int* recebe_notas(float *notas, int tamanho, int* APR){

    for(int i = 0; i < tamanho; i++){
        if(notas[i] >= 6.0){
            APR[i] = 1;
        } else {
            APR[i] = 0;
        }
    }

    return APR;
}
//Função conta_notas, satisfa item B.
void conta_notas(int* apr, int tamanho, int* aprovados, int* reprovados){

    for(int i=0 ; i<tamanho ; i++){
      if(apr[i] == 1){
          *aprovados += 1;
      }else{
          *reprovados += 1;
      }
    }
}

//Função percent_aprov, satisfaz item C.
int percent_aprov(int* apro, int* repro, int* per_apro, int* per_repro, int tamanho){

    *per_repro = (((*repro)*100)/tamanho);
    *per_apro = ((float)*apro/tamanho)*100;

    if(*per_apro >= 51){
      return 1;
    }else{
      return 0;
    }
}
