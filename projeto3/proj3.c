#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Agenda
typedef struct agenda{
	char nome[101];
	char telefone[12];
	char endereco[101];
	unsigned int cep;
	char dataNascimento[10];
}Agenda;

// No lista dinamica duplamente encadeada
typedef struct node{
	struct node *ant;
	Agenda * info;
	struct node *prox;
}Node;

// Funcao que iniciliza a lista
Node *inicializarLista(){
	Node *no = (Node*)malloc(sizeof(Node));
	no->prox = NULL;
	no->ant = NULL;
	no->info = NULL;
	return no;
}

// Função que insere um novo cadastro
Node* inserirNoTopoDaLista(Node* lista, char* nome, char* telefone, char* endereco, unsigned int cep, char* dataNascimento){
	Agenda* agenda;
	Node* novoNo;
	agenda = (Agenda*) malloc(sizeof(Agenda));
	if (agenda == NULL){
			printf("Sem memoria suficiente!\n");
			exit(1);
	}
	strcpy(agenda->nome,nome);
	strcpy(agenda->telefone,telefone);
	strcpy(agenda->endereco,endereco);
	agenda->cep = cep;
	strcpy(agenda->dataNascimento,dataNascimento);

	novoNo = (Node *)malloc(sizeof(Node));
	novoNo->info = agenda;
	novoNo->ant = NULL;
	novoNo->prox = lista;
	if(lista != NULL){
			lista->ant = novoNo;
	}
	return novoNo;
}

// Função responsavel por realizar uma busca por uma determinada string
Node *buscarPorString(Node *lista, char *string){
	Node *aux;
	for(aux = lista; aux->info != NULL; aux = aux->prox){
			if(strstr(aux->info->nome, string) != NULL){
					return aux;
			}
	}
	return NULL;
}


// Função responsável por imprimir contatos que contenham em seu nome alguma parte da string pesquisada.
void imprimirPorString(Node *lista, char *string){
	Node* cnt = lista;
	int i = 0;
	if(lista==NULL){
			printf("Memoria Insuficiente !\n");
			printf("Programa finalizado \n");
			exit(1);
	}
	if(lista -> info == NULL){
			printf("Agenda vazia!!\n");
	}
	while(cnt->prox != NULL){
			if(strstr(cnt->info->nome, string) != NULL){
				printf("\nNome: %s\n",cnt->info->nome);
				printf("Telefone: %s\n",cnt->info->telefone);
				printf("Endereco: %s\n",cnt->info->endereco);
				printf("CEP: %d\n",cnt->info->cep);
				printf("Data de Nascimento: %s\n",cnt->info->dataNascimento);
				i++;
			}
			cnt = cnt->prox;
	}
	if(i == 0){
		printf("\n\nCadastro não existe na base de dados!\n");
	}
	getchar();
	printf("\n\nPressione 'Enter' para voltar ao menu.\n");
	getchar();
}

// Função responsavel por remover o contato desejado a partir de uma string relacionada ao nome
Node *deletarContato(Node *lista, char *nome){
	Node *delCont = buscarPorString(lista,nome);
	Node *aux ;
	int i = 0;
	// Verifica se o nome digitado existe na Agenda
	if(delCont == NULL){
			printf("\n\nCadastro não existe na base de dados!\n");
			getchar();
			printf("\n\nPressione 'Enter' para voltar ao menu.\n");
			getchar();
			return lista;
	}
	// Método iterativo para contar quantos registros com o mesmo nome existe na agenda
	while(delCont != NULL){
			aux = delCont->prox;
			if(lista == delCont){
					lista = delCont->prox;
			} else{
					delCont->ant->prox = delCont->prox;
			}

			if(delCont != NULL){
					delCont->prox->ant = delCont->ant;
			}
			delCont = aux;
			delCont = buscarPorString(lista,nome);
			i++;
	}
	// Pega a quantidade de iterações para informar quantos registros do banco de dados foram removidos
	printf("%d cadastro(s) removido(s) com sucesso!\n", i);
	// Funcão equivalente a system("pause") do windows;
	getchar();
	printf("\n\nPressione 'Enter' para voltar ao menu.\n");
	getchar();
	free(delCont);
	return lista;
}

// Função responsável por imprimir todos os contatos contidos na lista.
void visualizarTodosContatos(Node *lista){
	Node* vsCont = lista;
	if(lista==NULL){
			printf("Memoria Insuficiente !\n");
			printf("Programa finalizado \n");
			exit(1);
	}
	if(lista -> info == NULL){
			printf("Agenda vazia!!\n");
	}
	while(vsCont->prox != NULL){
			printf("\nNome: %s\n",vsCont->info->nome);
			printf("Telefone: %s\n",vsCont->info->telefone);
			printf("Endereco: %s\n",vsCont->info->endereco);
			printf("CEP: %d\n",vsCont->info->cep);
			printf("Data de Nascimento: %s\n",vsCont->info->dataNascimento);

			vsCont = vsCont->prox;
	}
	getchar();
	printf("\n\nPressione 'Enter' para voltar ao menu.\n");
	getchar();
}

// Funcao responsavel por captar dados do contato.txt para a lista.
Node *coletarDados(Node* lista){

	FILE *arquivo;
	char nome[101] = "N";
	char telefone[12];
	char endereco[101];
	unsigned int cep;
	char dataNascimento[11];
	char cifrao = 'C';

	// Abre o arquivo contato.txt e caso não exista cria o mesmo.
	arquivo = fopen("contatos.txt","a+");

	fscanf(arquivo," %[^\n]",nome);
	getc(arquivo);

	if(strcmp(nome,"N")!= 0){
		 rewind(arquivo);
		 while(fscanf(arquivo," %[^\n]",nome) != EOF){
				getc(arquivo);

				fscanf(arquivo,"%s",telefone);
				getc(arquivo);

				fscanf(arquivo," %[^\n]",endereco);
				getc(arquivo);

				fscanf(arquivo,"%d",&cep);
				getc(arquivo);

				fscanf(arquivo," %[^\n]",dataNascimento);
				getc(arquivo);

				fscanf(arquivo,"%c",&cifrao);
				getc(arquivo);

				lista = inserirNoTopoDaLista(lista,nome,telefone,endereco,cep,dataNascimento);

		 }
	}
	fclose(arquivo);
	return lista;
}

// Função responsavel por gravar dados da lista no arquivo txt
void gravarDados(Node *lista){
	FILE *arquivo;
	Node *contato = lista;
	arquivo = fopen("contatos.txt","w+");
	while(contato->prox != NULL){
			fprintf(arquivo, "%s\n",contato->info->nome);
			fprintf(arquivo, "%s\n",contato->info->telefone);
			fprintf(arquivo, "%s\n",contato->info->endereco);
			fprintf(arquivo, "%d\n",contato->info->cep);
			fprintf(arquivo, "%s\n",contato->info->dataNascimento);
			fprintf(arquivo, "%c\n",'$');
			contato = contato->prox;
	}
	fclose(arquivo);
}

// Função responsavel por imprimir o menu.
void menu(){
		system("clear");
		printf("*----------------------------------*\n");
		printf("*              AGENDA              *\n");
		printf("*----------------------------------*\n");
		printf("*                                  *\n");
		printf("* 1- Inserir novo contato          *\n");
		printf("*                                  *\n");
		printf("* 2- Remover contato               *\n");
		printf("*                                  *\n");
		printf("* 3- Visualizar um contato         *\n");
		printf("*                                  *\n");
		printf("* 4- Visualizar todos os contatos  *\n");
		printf("*                                  *\n");
		printf("* 5- Sair                          *\n");
		printf("*                                  *\n");
		printf("*----------------------------------*\n");
		printf("\n\n");
}

//Função responsavel por inserir um cadastro na agenda através da função de inserirNoTopoDaLista.
Node* inserirContato(Node *lista){
	Agenda* agenda;
	Node* novoNo;
	char nome[101];
	char telefone[12];
	char endereco[101];
	unsigned int cep;
	char dataNascimento[11];

	printf("\t\n\nNome: ");
	scanf(" %[^\n]", nome);

	printf("\nTelefone: ");
	scanf("%s", telefone);

	printf("\nEndereço: ");
	scanf(" %[^\n]", endereco);

	printf("\nCEP: ");
	scanf("%d", &cep);

	printf("\nData de nascimento: ");
	scanf("%s", dataNascimento);

	agenda = (Agenda*) malloc(sizeof(Agenda));
	if (agenda == NULL){
			printf("Sem memoria suficiente!\n");
			exit(1);
	}
	strcpy(agenda->nome,nome);
	strcpy(agenda->telefone,telefone);
	strcpy(agenda->endereco,endereco);
	agenda->cep = cep;
	strcpy(agenda->dataNascimento,dataNascimento);

	novoNo = (Node *)malloc(sizeof(Node));
	novoNo->info = agenda;
	novoNo->ant = NULL;
	novoNo->prox = lista;
	if(lista != NULL){
			lista->ant = novoNo;
	}

	return novoNo;
}

//Funcao que ler um nome e o encapsula para pesquisas em outras funções.
char *lerNome(){
	char *nome;
	nome = (char*)calloc(101,sizeof(char));
	scanf(" %[^\n]",nome);
	return nome;
}


//Metodo de ordenação Insertion Sort

Node *insertionSort(Node *lista){
		Node *p;
		Node *j;
		Agenda *aux;

		for(p = lista->prox; p->prox != NULL ; p = p -> prox){
				aux = p->info;
				j = p->ant;

				while((j->ant != NULL)&&((strcmp(j->info->nome,aux->nome) < 0))){
						j->prox->info = j->info;
						j = j -> ant;
				}

				j->prox->info = aux;

		}

		return lista;
}

void limparLista(Node *lista){
	if(lista != NULL){
			Node* aux;
			while(lista != NULL){
					aux = lista;
					lista = lista -> prox;
					free(aux);
			}
			free(lista);
	}
}

//Função responsavel por tratar dados antes da finalização do programa.
void finalizar(Node* lista){
	lista = insertionSort(lista);
	gravarDados(lista);
	limparLista(lista);
	printf("\n\tPrograma Finalizado!\n\n");
	exit(1);
};

//Função responsavel pela execução do programa.
int main(){
	Node *lst;
	int opcao = 1;
	lst = inicializarLista();
	lst = coletarDados(lst);
	do {
		menu();
		scanf("%d", &opcao);
		system("clear");

		switch(opcao){
				case 1:
						printf("*----------------------------------*\n");
						printf("*                                  *\n");
						printf("*        Inserir novo contato      *\n");
						printf("*                                  *\n");
						printf("*----------------------------------*\n");
						lst = inserirContato(lst);

						break;
				case 2:
						printf("*----------------------------------*\n");
						printf("*                                  *\n");
						printf("*    Excluir contato por string.   *\n");
						printf("*                                  *\n");
						printf("*----------------------------------*\n");
						printf("\n\nNome do contato a ser excluido : ");
						lst = deletarContato(lst,lerNome());
						break;
				case 3:
						printf("*----------------------------------*\n");
						printf("*                                  *\n");
						printf("*    Buscar contato por string.    *\n");
						printf("*                                  *\n");
						printf("*----------------------------------*\n");
						printf("\n\nNome do contato a ser buscado: ");
						imprimirPorString(lst,lerNome());
						break;
				case 4:
						printf("*----------------------------------*\n");
						printf("*          Lista de contatos       *\n");
						printf("*----------------------------------*\n");
						lst = insertionSort(lst);
						visualizarTodosContatos(lst);
						break;
				case 5:
						finalizar(lst);
						break;
				default:
						printf("Opcao invalida, por favor digite uma opcao valida.\n");
		}
	} while(opcao);
	return 0;
}
