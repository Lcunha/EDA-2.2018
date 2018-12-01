
#ifndef MESCLADOR_H
#define MESCLADOR_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>
#include "projeto2.h"
#include "projeto6.h"

//mesclador separa arquivos para treino e teste
void mesclador()
{
    printf("Arquivos ja sorteados e vetorizados!\nSeparando teste e treino..");
    FILE *testeAG;
    FILE *treinoAG;
    FILE *asphalt;
    FILE *grass;
    asphalt = fopen("asphalt.dat", "r");
    grass = fopen("grass.dat", "r");
    testeAG = fopen("testeAG.dat", "w+");
    treinoAG = fopen("treinoAG.dat", "w+");
    int z = 0;
    char tranf;
    while (z < 25)
    {
        tranf = fgetc(asphalt);
        fprintf(testeAG, "%c", tranf);
        if (tranf == '\n')
            z++;
    }
    z = 0;
    while (z < 25)
    {
        tranf = fgetc(grass);
        fprintf(testeAG, "%c", tranf);
        if (tranf == '\n')
            z++;
    }
    z = 25;
    while (z < 50)
    {
        tranf = fgetc(asphalt);
        fprintf(treinoAG, "%c", tranf);
        if (tranf == '\n')
            z++;
    }
    z = 25;
    while (z < 50)
    {
        tranf = fgetc(grass);
        fprintf(treinoAG, "%c", tranf);
        if (tranf == '\n')
            z++;
    }

    fclose(testeAG);
    fclose(testeAG);
    fclose(treinoAG);
    fclose(asphalt);
    fclose(grass);
}
#endif