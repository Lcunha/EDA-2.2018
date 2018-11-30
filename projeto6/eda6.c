#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>
#include "projeto2.h"
#include "projeto6.h"

int main(int argc, char *argv[])
{
  int opcao = 0;
  while (opcao < 1 || opcao > 2)
  {
    printf("\nJa possui vetores do projeto 2?\n");
    printf("1 - para SIM \n2 - para NAO\n opcao: ");
    scanf("%d", &opcao);
  }
  if (opcao == 2)
    projeto2();

  int neuronios_Camadaoculta = atoi(argv[1]);
  if (argc != 2)
  {
    printf("Parametro incorreto. Exit.\n");
    exit(1);
  }
  printf("\n\n\n--------------------------------\nNeuronios Camada Oculta: %d\n--------------------------------\n", neuronios_Camadaoculta);
  projeto6(neuronios_Camadaoculta);
  return 0;
} //fim da main
