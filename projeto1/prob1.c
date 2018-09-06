#include <stdio.h>
#include <stdlib.h>
#define TAMANHO 10

void fneuronio(double*, double*, int, int, int*);

int main(){
    //declaraçoes
    double entradas[TAMANHO] = {0};
    double pesos[TAMANHO] = {0};
    double limiarT = 0.0;
    int memoria;
    int* resultado = &memoria;

    /*
    Solicitações de entrada de dados ao usuário. satisfazendo o item A.
    */
    printf("Digite os valores:\n");

    for(int i = 0; i < TAMANHO; i++){
        scanf("%lf", &entradas[i]);
    }

    printf("Digite os pesos:\n");

    for(int i = 0; i < TAMANHO; i++){
        scanf("%lf", &pesos[i]);
    }

    printf("Digite o limiar T:\n");
    scanf("%lf", &limiarT);

    //Call da função fneuronio, satisfazendo o item A.
    fneuronio(entradas, pesos, limiarT, TAMANHO, resultado);

    //Verificando resultado através de ponteiro, satisfazendo o item C.
    if(*resultado == 1){
        printf("Neurônio ativado!\n");
    }else{
        printf("Neurônio inibido!\n");
    }

    return 0;
}

//Função de verficação do neuronio, satisfazendo o item B.
void fneuronio(double* entradas, double* pesos, int limiarT, int tamanho, int* resultado){
    double SOMAP = 0.0;

    for(int j = 0; j < tamanho; j++){
        SOMAP += entradas[j]*pesos[j];
    }

    //Retornando 0 ou 1, satisfzando o item B.
    if(SOMAP > limiarT){
        *resultado = 1;
    } else {
        *resultado = 0;
    }
}
