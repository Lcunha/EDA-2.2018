#include <stdio.h>

void hanoi(int qtd, char origem, char destino, char auxiliar){

    if(qtd == 1){
    	printf("Mova o disco 1 de %c para %c \n",origem ,destino);
    	return;
    }
    // 1º ação de recursividade
    hanoi(qtd-1,origem,auxiliar,destino);

    printf("Mova o disco %d de %c para %c \n",qtd,origem,destino);

    //2º ação de recursividade
    hanoi(qtd-1,auxiliar,destino,origem);
}

int main(){
    // declaraçoes
    int qtd_discos;

    // Solicitação de entradas
    printf("Digite a quantidade de discos:");
    scanf("%d",&qtd_discos);

    // A - Origem , b- Auxiliar e C= Destino
    printf("Resolução:\n");
    hanoi(qtd_discos, 'A', 'C', 'B');

    return 0;
}
