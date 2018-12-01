#ifndef PROJETO6_H
#define PROJETO6_H
#include "projeto2.h"

//declaraçoes de funcoes
void mesclador();
//executar projeto6
void projeto6(int n_camadaoculta){
    mesclador();
}//fim projeto 6

//funções projeto 6
void mesclador(){
    FILE *testeAG;
    FILE *treinoAG;
    FILE *asphalt;
    FILE *grass;
    asphalt = fopen ("asphalt.dat", "r");
    grass = fopen ("grass.dat", "r");
    testeAG = fopen ("testeAG.dat", "w+");
    treinoAG =fopen ("treino.dat", "w+");
    int z=0;
    char tranf;
    while(z<25){
        tranf = fgetc(asphalt);
        fprintf(testeAG, "%c", tranf);
        if(tranf == '\n')
            z++;
    }
    z =0;
    while(z<25){
        tranf = fgetc(grass);
        fprintf(testeAG, "%c", tranf);
        if(tranf == '\n')
            z++;
    }
    z=25;
    while(z<50){
        tranf = fgetc(asphalt);
        fprintf(treinoAG, "%c", tranf);
        if(tranf == '\n')
            z++;
    }
    z=25;
    while(z<50){
        tranf = fgetc(grass);
        fprintf(treinoAG, "%c", tranf);
        if(tranf == '\n')
            z++;
    }

    fclose(testeAG);
    fclose(testeAG);
    fclose(treinoAG);
    fclose(asphalt);
    fclose(grass);
}
#endif