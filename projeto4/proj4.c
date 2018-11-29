#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

typedef struct voo {
  char codigo[7];
  char modo;
  int combustivel;
  struct voo *prox;
} Voo;

typedef struct fila {
  Voo *inicio;
  Voo *final;
} Fila;

Voo *inicializarVoo(char *codigo, char modo, int combustivel) {

  Voo *voo = (Voo *)malloc(sizeof(Voo));
  // Iguala os elementos aos elementos recebidos como parâmetros.
  strcpy(voo->codigo, codigo);
  voo->modo = modo;
  voo->combustivel = combustivel;
  voo->prox = NULL;

  return voo;
}

Voo *inserirVooLista(Voo *lista, Voo *voo) {

  if(lista != NULL) {
    voo->prox = lista;
  }

  return voo;

}

Fila *inicializarLista() {
  Fila *fi = (Fila *) malloc(sizeof(Fila));

  if (fi != NULL) {
    fi->inicio = NULL;
    fi->final = NULL;
  }

  return fi;
}

void liberarFila(Fila *fi) {
  if (fi != NULL) {
    Voo *no;
    while (fi->inicio != NULL) {
      no = fi->inicio;
      fi->inicio = fi->inicio->prox;
      free(no);
    }
    free(fi);
  }
}

void inserirVooNaFila(Fila *fi, Voo *voo) {

  if (fi == NULL) {
    printf("Alocação falhou!\n");
    exit(1);
  }

  if (voo == NULL) {
    printf("Alocação falhou!\n");
    exit(1);
  }

  voo->prox = NULL;

  if (fi->final == NULL) { // inicio da fila
    fi->inicio = voo;
  } else {
    fi->final->prox = voo;
  }
  fi->final = voo;
}

void removerFila(Fila *fi) {
  if (fi == NULL) {
    printf("Alocação falhou!\n");
    exit(1);
  }
  if (fi->inicio == NULL) {
    printf("Fila está vazia\n");
    exit(1);
  }
  Voo *no = fi->inicio;
  fi->inicio = fi->inicio->prox;
  if (fi->inicio == NULL) {
    fi->final = NULL;
  }
  free(no);
}

int main() {

  int numDecolagens = 0, numAproximacoes = 0, numVoos = 0, cont = 0;
  char *nomeVoos[64] = {"VG3001",
  "JJ4404", "LN7001", "TG1501", "GL7602", "TT1010", "AZ1009", "AZ1008",
  "AZ1010", "TG1506", "VG3002", "JJ4402", "GL7603", "RL7880", "AL0012",
  "TT4544", "TG1505", "VG3003", "JJ4403", "JJ4401", "LN7002", "AZ1002",
  "AZ1007", "GL7604", "AZ1006", "TG1503", "AZ1003", "JJ4403", "AZ1001",
  "LN7003", "AZ1004", "TG1504", "AZ1005", "TG1502", "GL7601",
  "TT4500", "RL7801", "JJ4410", "GL7607", "AL0029", "VV3390", "VV3392",
  "GF4681", "GF4690", "AZ1020", "JJ4435", "VG3010", "LF0920", "AZ1065",
  "LF0978", "RL7867", "TT4502", "GL7645", "LF0932", "JJ4434", "TG1510",
  "TT1020", "AZ1098", "BA2312", "VG3030", "BA2304", "KL5609",
  "KL5610", "KL5611"};


  int semente = time(NULL);
  srand(semente);
  numDecolagens = 10 + (rand() % 22);
  srand(semente+4);
  numAproximacoes = 10 + (rand() % 22);
  numVoos = numAproximacoes + numDecolagens;


  int *voosFocados, numRandom = 0;
  voosFocados = (int *) calloc(64, sizeof(int));

  Voo *primeiraLista = NULL;
  Voo *voo;

  int decolagens = 0, aproximacoes = 0;
  srand(semente+1);
  //Randomização dos voos de decolagens
  for(cont = 0; cont < numDecolagens; cont++) {

    numRandom = (rand() % 64);

    if( *(voosFocados + numRandom) == 1) {
      cont--;
    }
    else if( *(voosFocados + numRandom) == 0) {
      *(voosFocados + numRandom) = 1;
      voo = inicializarVoo( nomeVoos[numRandom], 'D', -1);
      primeiraLista = inserirVooLista(primeiraLista, voo);

    }

  }

  srand(semente+2);
  //Randomização dos voos de aproximações
  for(cont = 0; cont < numAproximacoes; cont++) {
    numRandom = (rand() % 64);

    if( *(voosFocados + numRandom) == 1 ) {
      cont--;
    }
    else if( *(voosFocados + numRandom) == 0) {
      *(voosFocados + numRandom) = 1;
      int combustivel = (rand() % 13);
      voo = inicializarVoo( nomeVoos[numRandom], 'A', combustivel);
      primeiraLista = inserirVooLista(primeiraLista, voo);
    }

  }

  //libera vetor de 64 posições
  free(voosFocados);

  Fila *filaAproximacoes = inicializarLista();
  //Ordenação
  for (int i = 0; i < 13; i++) {

    Voo *elementoAtual = primeiraLista;
    Voo *elementoAnterior = NULL;

    while (elementoAtual != NULL) {

      if (elementoAtual->combustivel == i) {
        if (elementoAtual == primeiraLista) {
          primeiraLista = primeiraLista->prox;
        }
        else {
          elementoAnterior->prox = elementoAtual->prox;
        }

        Voo *aux = elementoAtual->prox;
        inserirVooNaFila(filaAproximacoes, elementoAtual);
        elementoAtual = aux;
      }

      else {
        elementoAnterior = elementoAtual;
        elementoAtual = elementoAtual->prox;
      }
    }
  }

  Fila *filaDecolagens = inicializarLista();

  Voo *elementoAtual = primeiraLista;
  Voo *proximoElemento = NULL;

  while(elementoAtual != NULL) {
    proximoElemento = elementoAtual->prox;
    inserirVooNaFila(filaDecolagens, elementoAtual);
    elementoAtual = proximoElemento;
  }

  printf("--------------------------------------------------------------------------------\n");
  printf("Aeroporto Internacional de Brasília\n");
  printf("Hora Inicial: 10:00\n");
  printf("Fila de Pedidos: [código do voo – P/D – prioridade]\n\n");
  

  Voo *imprimirFilaAproximacoes = filaAproximacoes->inicio;

  while (imprimirFilaAproximacoes != NULL) {

    printf("[%s-%c-%d]\n", imprimirFilaAproximacoes->codigo, imprimirFilaAproximacoes->modo, imprimirFilaAproximacoes->combustivel);

    imprimirFilaAproximacoes = imprimirFilaAproximacoes->prox;
  }

  Voo *imprimirFilaDecolagens = filaDecolagens->inicio;

  while (imprimirFilaDecolagens != NULL) {

    printf("[%s-%c]\n", imprimirFilaDecolagens->codigo, imprimirFilaDecolagens->modo);

    imprimirFilaDecolagens = imprimirFilaDecolagens->prox;
  }
  
  printf("\nNVoos: %d\n", numVoos);
  printf("Naproximações: %d\n", numAproximacoes);
  printf("NDecolagens: %d\n", numDecolagens);
  printf("--------------------------------------------------------------------------------\n");
  printf("\nListagem de eventos:\n\n");


  //eventos de voos

  int hora = 10, minuto = 0, verificacaoCombustivel = 1;
  int pista1 = 0, pista2 = 0, pista3 = 0;

  while(filaAproximacoes->inicio != NULL || filaDecolagens->inicio != NULL) {

    // verificar emergências
    int combVazio = 0;
    Voo *verifComb = filaAproximacoes->inicio;

    while(verifComb != NULL) {
      if(verifComb->combustivel == 0) {
        combVazio++;
      }
      verifComb = verifComb->prox;
    }

    if(combVazio >= 3) {
      printf("\n\nALERTA GERAL DE DESVIO DE AERONAVE\n\n");
    }

    //Pista 1
    if(pista1 == 0) {
      if(filaAproximacoes->inicio != NULL) {
        printf("Código do voo: %s - %c - %d\n", filaAproximacoes->inicio->codigo, filaAproximacoes->inicio->modo, filaAproximacoes->inicio->combustivel);
        printf("Status: [Aeronave Pousou]\n");
        printf("Horário do ínicio do procedimento: %02d:%02d\n", hora, minuto);
        printf("Número da pista: 1\n\n");
        pista1 = 4;
        removerFila(filaAproximacoes);
      }
      else if(filaDecolagens->inicio != NULL){
        printf("Código do voo: %s - %c\n", filaDecolagens->inicio->codigo, filaDecolagens->inicio->modo);
        printf("Status: [Aeronave Decolou]\n");
        printf("Horário do ínicio do procedimento: %02d:%02d\n", hora, minuto);
        printf("Número da pista: 1\n\n");
        pista1 = 2;
        removerFila(filaDecolagens);
      }
    }
    //Pista 2
    if(pista2 == 0) {
      if(filaAproximacoes->inicio != NULL) {
        printf("Código do voo: %s - %c - %d\n", filaAproximacoes->inicio->codigo, filaAproximacoes->inicio->modo, filaAproximacoes->inicio->combustivel);
        printf("Status: [Aeronave Pousou]\n");
        printf("Horário do ínicio do procedimento: %02d:%02d\n", hora, minuto);
        printf("Número da pista: 2\n\n");
        pista2 = 4;
        removerFila(filaAproximacoes);
      }
      else if(filaDecolagens->inicio != NULL) {
        printf("Código do voo: %s - %c\n", filaDecolagens->inicio->codigo, filaDecolagens->inicio->modo);
        printf("Status: [Aeronave Decolou]\n");
        printf("Horário do ínicio do procedimento: %02d:%02d\n", hora, minuto);
        printf("Número da pista: 2\n\n");
        pista2 = 2;
        removerFila(filaDecolagens);
      }
    }
    //Pista 3
    if(combVazio >= 3) {
      if(pista3 == 0) {
        printf("Código do voo: %s - %c - %d\n", filaAproximacoes->inicio->codigo, filaAproximacoes->inicio->modo, filaAproximacoes->inicio->combustivel);
        printf("Status: [Aeronave Pousou]\n");
        printf("Horário do ínicio do procedimento: %02d:%02d\n", hora, minuto);
        printf("Número da pista: 3\n\n");
        pista3 = 4;
        removerFila(filaAproximacoes);
      }
    }

    if(pista3 == 0) {
      if(filaDecolagens->inicio != NULL) {
        printf("Código do voo: %s - %c\n", filaDecolagens->inicio->codigo, filaDecolagens->inicio->modo);
        printf("Status: [Aeronave Decolou]\n");
        printf("Horário do ínicio do procedimento: %02d:%02d\n", hora, minuto);
        printf("Número da pista: 3\n\n");
        pista3 = 2;
        removerFila(filaDecolagens);
      }
    }

    //rotinas
    if(pista1 > 0){
      pista1--;
    }
    if(pista2 > 0){
      pista2--;
    }
    if(pista3 > 0){
      pista3--;
    }
    minuto+= 5;
    if(minuto >= 60) {
      hora++;
      minuto = 0;
      if(hora >= 24) {
        hora = 0;
      }
    }

    if(verificacaoCombustivel%10 == 0) {
      Voo *gastoComb = filaAproximacoes->inicio;

      while(gastoComb != NULL) {
        gastoComb->combustivel = (gastoComb->combustivel) - 1;
        gastoComb = gastoComb->prox;
      }
      gastoComb = filaAproximacoes->inicio;
    }

    // Derruba os que estão com combustível menos de 0
    Voo *vooDerrubados = filaAproximacoes->inicio;

    while(vooDerrubados != NULL) {
      if(vooDerrubados->combustivel < 0) {
        printf("ALERTA CRÍTICO: Aeronave irá cair\n\n");
        printf("Código do voo: %s - %c - %d\n", vooDerrubados->codigo, vooDerrubados->modo, vooDerrubados->combustivel);
        printf("Status: [Aeronave Caiu]\n\n");
        removerFila(filaAproximacoes);
      }
      vooDerrubados = vooDerrubados->prox;
    }

    verificacaoCombustivel++;

  }

  liberarFila(filaAproximacoes);
  liberarFila(filaDecolagens);

  return 0;
}