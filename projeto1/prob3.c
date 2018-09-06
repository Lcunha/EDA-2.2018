#include <stdio.h>

void hanoi(int qtd){
    char origem = 'A';
    char destino = 'C';
    char auxiliar = 'B'

    if(qtd == 1){
    	printf("Mova o disco 1 de %c para %c \n",origem ,destino);
    	return;
    }

    hanoi(qtd-1,origem,auxiliar,destino);

    printf("Mova o disco %d de %c para %c \n",n,origem,destino);

    hanoi(qtd-1,auxiliar,destino,origem);
}

int main(){
    // declaraçoes
    int qtd_discos;

    // Slicitação de entradas
    printf("Digite a quantidade de discos:");
    scanf("%d",&qtd_discos);

    printf("Resolução:\n");
    hanoi(qtd_discos);

    return 0;
}
