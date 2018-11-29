#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "binaryTree.h"
#include <stdio.h>

int main(){

    // Arvore
    NodeTree *no;

    // Variaveis
    
		int altura;
    int pesquisaValor;
    int levelPesquisaValor;
    int removerValor;
    int i;
    int escolhaMenu;
		char fileName[10];

    // Menu
        /*  O programa deve apresentar um menu que permita ao usuário escolher
     qual ação deve ser executada. Após a execução de cada escolha, o menu
     deve ser exibido novamente, até que o usuário escolha pelo encerramento
     do programa via menu. */
    system("clear");
    printf("\t==================================================================\n");
    printf("\t=     Digite o nome do arquivo a ser carregado para a arvore     =\n");
    printf("\t==================================================================\n\n\t");
    scanf("%s", fileName);
    no = loadTreeFromFile(fileName);
    altura = getHeight(no);
    getchar();
    printf("\n\n\tPressione 'Enter' para ir ao menu principal\n\t");
    getchar();

    do{
        menu();
        scanf("%d", &escolhaMenu);
        system("clear");


        switch(escolhaMenu){
            case 1:
						  printf("\t=====================================\n");
							printf("\t=     Digite o nome do arquivo:     =\n");
							printf("\t=====================================\n\n\t");
							scanf("%s", fileName);
							no = loadTreeFromFile(fileName);
							pause();
              break;
            case 2:
							printf("\t=====================================\n");
							printf("\t=        Impressao da arvore!       =\n");
							printf("\t=====================================\n\n");
							 showTree(no);
							pause();
	            break;
            case 3:
							printf("\t=====================================\n");
							printf("\t=           Arvore  cheia?          =\n");
							printf("\t=====================================\n\n\t");
							isFull(no);
							pause();
              break;
            case 4:
              printf("\t=====================================\n");
              printf("\t=        Valor a ser pesquisado     =\n");
              printf("\t=====================================\n\n\t");
              scanf("%d", &pesquisaValor);
              searchValue(no,pesquisaValor);
              levelPesquisaValor = getLevel(no, pesquisaValor);
              if(levelPesquisaValor){
                printf("\tNivel do numero %d: %d\n", pesquisaValor, getLevel(no, pesquisaValor));
              }
              else{
                printf("\n\tValor %d nao esta presente na arvore!", pesquisaValor);
              }
              pause();
              break;
            case 5:
							printf("\t=====================================\n");
							printf("\t=         Altura da arvore          =\n");
							printf("\t=====================================\n\n\t");
							printf("Altura da arvore: %d\n",getHeight(no));
							pause();
              break;
            case 6:
            	printf("\t=====================================\n");
							printf("\t=          Remover valor            =\n");
							printf("\t=====================================\n\n\t");
              printf("\n\tQual valor deseja remover? ");
						  scanf("%d", &removerValor);
              printf("\n\t");
              no = removeValue(no,removerValor);
							pause();
              break;
            case 7:
							printf("\t=====================================\n");
							printf("\t=         Algoritmo In Order        =\n");
							printf("\t=====================================\n\n");
							printInOrder(no);
							pause();
              break;
            case 8:
              printf("\t=====================================\n");
							printf("\t=        Algoritmo Pre Order        =\n");
              printf("\t=====================================\n\n");
							printPreOrder(no);
							pause();
							break;
            case 9:
              printf("\t=====================================\n");
							printf("\t=       Algoritmo Post Order:       =\n");
              printf("\t=====================================\n\n");
							printPostOrder(no);
							pause();
              break;
						case 10:
              printf("\t=====================================\n");
							printf("\t=       Balanceamento de Arvore:     =\n");
              printf("\t=====================================\n\n");
							no = balanceTree(no);
              pause();
							break;
            case 0:
              libera(no);
							sair();
              break;
						default:
							printf("\tOpcao Invalida!\n");
							pause();
        }
    }while(escolhaMenu);
    return 0;
}
