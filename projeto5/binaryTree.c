#include <string.h>
#include <math.h>
#include "binaryTree.h"
#include <stdio.h>
#include <stdlib.h>
#define MAX_HEIGHT 1000
#define INFINITY (1<<20)
int lprofile[MAX_HEIGHT];
int rprofile[MAX_HEIGHT];

typedef struct BSTNode_struct BSTNode;

struct BSTNode_struct {
    BSTNode *ptLeft, *ptRight;
    int edgeLength;
    int height;
    int element;
    int parentDir;
    char label[11];
};

/* Funções*/

/* Função loadTreeFromFile, que recebe uma string com o nome do arquivo
contendo os elementos a serem inseridos na árvores e retorna o
endereço da raiz da árvore montada */
NodeTree *loadTreeFromFile(char* arquivo) {
	// Alocação para abertura do arquivo
    FILE *fp;

	// Variável para pegar o numero no arquivo
    int num;

	// Alocação inial da Árvore
    NodeTree *root = NULL;
    char fileName[40];

	// Diretório do arquivo
    snprintf(fileName, 40, "BSTs/%s.txt", arquivo);

	// Abertura
    fp = fopen(fileName,"r");

	// Verifica se o arquivo foi aberto corretamente
    if(fp == NULL){
        printf("\n\n\tFalha ao abrir arquivo, tente novamente!\n");
        exit(1);
	}
	else{
		printf("\n\tArquivo encontrado!\n");
	}

	// Faz a leitura do arquivo para a memória
    fscanf(fp,"%d ", &num);

	// Insere na arvore
    root = insert(root,num);
    printf("\n\tElementos a serem adicionados a Arvore: %d",num);
    while(!feof(fp)){
  	    fscanf(fp,"%d ", &num);
        insert(root,num);
        printf(", %d",num);
    }
	printf("\n\n\tElementos adicionados com sucesso!\n\n");

	// Fechamento do arquivo
	fclose(fp);

    return root;
}


/* Função isFull, que recebe como entrada o endereço do nó raiz e imprime na
tela se a árvore é cheia ou não. */
void isFull(NodeTree *root) {
  int key = isFullTree(root);
	if(key){
		printf("Árvore e Cheia!");
  }
	else{
    printf("Árvore nao e Cheia!");
  }
}

/* Função searchValue, que recebe como entrada o endereço do nó raiz e um
valor inteiro. Deve buscar o valor na árvore e imprimir na tela o
nível do nó encontrado, o valor de seu pai e, caso possua, seu
irmão. Caso não seja encontrado, deve-se imprimir uma mensagem
alertando que o valor não está presente na árvore. */
void searchValue(NodeTree *root,int i) {
  if(root == NULL){
		flag = 1;
		return;
  }
  if(root->number == i || (root->left != NULL  && root->left->number == i) || (root->right != NULL && root->right->number == i) ) {
    printf("\tValor encontrado!!\n");
  }
  if((root->left != NULL  && root->left->number == i ) || (root->right != NULL && root->right->number == i)) {
    if(root->left != NULL && root->right != NULL ){
      if(i == root->right->number){
	      printf("\tPai do valor %d: %d\n",i,root->number);
	      printf("\tIrmao a esquerda do valor %d: %d\n",i,root->left->number);
	      return;
      }
			else{
	      printf("\tPai do valor %d: %d\n",i,root->number);
	      printf("\tIrmao a direita do valor %d: %d\n",i,root->right->number);
	      return;
      }
    }
		else if(root->left != NULL){
      printf("\tPai do valor %d: %d\n",i,root->number);
      printf("\tIrmao a direita do valor %d: sem irmão a direita\n",i);
      return;
    }
		else if(root->right != NULL){
      printf("\tPai do valor %d: %d\n",i,root->number);
      printf("\tIrmao a esquerda do valor %d: sem irmão a esquerda\n",i);
      return;
    }
  }
  if(root->number > i){
    searchValue (root->left,i);
  }
	else{
    searchValue (root->right,i);
  }
}

/* Função getHeight, que recebe como entrada o endereço do nó raiz e
imprime na tela a altura da árvore. */
int getHeight(NodeTree *root){
  if (root == NULL) return 0;
  return 1 + MAX(getHeight(root->left), getHeight(root->right));
}


/* Função removeValue, que recebe como entrada o endereço do nó raiz e um
valor inteiro. Esse valor inteiro deve ser removido da árvore. Caso
o valor não seja encontrado, deve-se imprimir uma mensagem
alertando que o valor não está presente na árvore. */
NodeTree *removeValue(NodeTree* root,int number){
  if(root == NULL){
		printf("Valor %d nao encontrado na arvore!", number);
    return root;
  }
  if(number < root->number){
    root->left = removeValue(root->left,number);
  }
	else if(number > root->number){
    root->right = removeValue(root->right,number);
  }

  else{
    if(root->left == NULL){
      NodeTree *temp = root->right;
      free(root);
			printf("Valor removido com sucesso!");
      return temp;
    }
    else if(root->right == NULL){
      NodeTree *temp = root->left;
			printf("Valor removido com sucesso!");
      free(root);
      return temp;
    }

    NodeTree *temp = minValueNode(root->right);
    root->number = temp->number;
    root->right = removeValue(root->right,temp->number);
  }
  return root;
}

/* Função printInOrder, que recebe como entrada o endereço do nó raiz e
imprime a árvore utilizando o algoritmo in order.  */
void printInOrder(NodeTree *no){
    if (no){
      printInOrder(no->left);
      printf("\t%d\n",no->number);
      printInOrder(no->right);
    }
}

/* Função printPreOrder, que recebe como entrada o endereço do nó raiz e
imprime a árvore utilizando o algoritmo pre order. */
void printPreOrder(NodeTree *no){
   if (no){
		 printf("\t%d\n",no->number);
		 printPreOrder(no->left);
		 printPreOrder(no->right);
    }
}

/*Função printPostOrder, que recebe como entrada o endereço do nó raiz e
imprime a árvore utilizando o algoritmo post order.  */
void printPostOrder(NodeTree *no){
    if (no){
      printPostOrder(no->left);
      printPostOrder(no->right);
      printf("\t%d\n",no->number);
    }
}

/* balanceTree, que recebe como entrada o endereço do nó raiz e
realiza o balanceamento da árvore, caso esteja desbalanceada.
Caso a árvore já esteja balanceada, nenhum processamento extra
deve ser realizado. O método utilizado deve ser o de rotações.
Observe que é necessário checar se a árvore está balanceada, não
bastando apenas tentar realizar o balanceamento sem checagem
prévia. */

NodeTree* balanceTree(NodeTree* root){
  NodeTree *daddy, *grandpa, *kid;
  if (isBalanced(root)) {
    printf("A árvore já está balanceada\n");
  }else{
    root = setBackbone(root);

    while (!isBalanced(root)) {
      grandpa = root;
      daddy = root;
      if (daddy !=NULL) {
        kid = daddy->right;
      }
      if (kid != NULL) {
        root = rotationLeft(NULL, daddy, kid, root);
      }

      grandpa = daddy;
      daddy = kid;
      kid = daddy->right;

      while ((daddy != NULL) && !isBalanced(root)) {
        grandpa = daddy;
        daddy = kid;
        if (daddy !=NULL) {
          kid = daddy->right;
        }

        if (kid != NULL) {
          root = rotationLeft(grandpa, daddy, kid, root);
        }

        grandpa = daddy;
        daddy = kid;
        if (daddy != NULL) {
          kid = daddy->right;
        }
      }
    }
  }
  showTree(root);
  return root;
}

/* funçoes extras */

// Função auxiliar para inserção na arvore;
NodeTree *NewNode(int number){
  NodeTree *temp = (NodeTree*)malloc(sizeof(NodeTree));
  temp->number = number;
  temp->left = temp->right = NULL;
  return temp;
}

// Função auxiliar da loadTreeFromFile para inserir na arvore;
NodeTree *insert(NodeTree *node,int number){
  if (node == NULL) return NewNode(number);
   if(number < node->number){
    node->left = insert(node->left,number);
  }
  else if(number > node->number){
    node->right = insert(node->right,number);
  }
  return node;
}


// Função para exibição do menu na main
void menu(){
		system("clear"); //system("clear");
		printf("\t=======================================================\n");
		printf("\t==     1 - Mudar arquivo a ser colocado na arvore    ==\n");
        printf("\t==     2 - Imprimir Arvore                           ==\n");
        printf("\t==     3 - Arvore Cheia?                             ==\n");
        printf("\t==     4 - Procurar valor                            ==\n");
        printf("\t==     5 - Altura da Arvore                          ==\n");
        printf("\t==     6 - Remover valor                             ==\n");
        printf("\t==     7 - Imprimir InOrder                          ==\n");
        printf("\t==     8 - Imprimir PreOrder                         ==\n");
        printf("\t==     9 - Imprimir PostOrder                        ==\n");
        printf("\t==     10 - Balancear arvore                         ==\n");
        printf("\t==     0 - Sair                                      ==\n");
		printf("\t======================================================*\n\t");

}

// Função auxiliar para o menu
void pause(){
	getchar();
	printf("\n\n\tPressione 'Enter' para voltar ao menu principal\n\t");
	getchar();
}

// Função auxiliar para isFull
int isFullTree(NodeTree *root){
  if(root==NULL)
    return 1;
    if(root->left == NULL  && root->right == NULL) return 1;
    if((root->left) && (root->right)) return(isFullTree(root->left) && isFullTree(root->right));
    return 0;
}

 // Função auxiliar para getLevel
int getLevelUtil(NodeTree *root, int number, int level){
    if (root == NULL) return 0;

    if (root->number == number) return level;

    int downlevel = getLevelUtil(root->left, number, level+1);
    if (downlevel != 0)
        return downlevel;

    downlevel = getLevelUtil(root->right, number, level+1);
    return downlevel;
}

// Função auxiliar para getHeight
int getLevel(NodeTree *root, int number){
    return getLevelUtil(root,number,1);
}
// Função auxiliar para showTree
NodeTree* minValueNode(NodeTree *node){
  NodeTree *current = node;
  while(current->left != NULL){
    current = current->left;
  }
  return current;
} 

//Função para desalocar memoria
NodeTree *libera(NodeTree *a){
	if(!vazia(a)){
		libera(a->left);
		libera(a->right);
		free(a);
	}
	return NULL;
}

int vazia(NodeTree *a){
	return a == NULL;
}

// Função para finlaizar  programa
void sair(){
	printf("\n\tPrograma finalizado! :)\n\n");
	exit(1);
}

NodeTree * setBackbone(NodeTree *root){
  NodeTree *grandpa, *daddy, *kid;

  while (root->left != NULL) {
    root = rotationRight(NULL, root, root->left);
  }

  grandpa = root;
  daddy = root->right;

  while (daddy->right != NULL) {
    grandpa = root;
    daddy = root->right;

    while ((daddy->left == NULL) && (daddy->right !=NULL)) {
      grandpa = grandpa->right;
      daddy = daddy->right;
    }

    while(daddy->left != NULL) {
      daddy = rotationRight(grandpa, daddy, daddy->left);
    }
  }
  return root;
}

NodeTree* rotationRight(NodeTree *grandpa, NodeTree *daddy, NodeTree *kid){

  if (grandpa != NULL) {
    grandpa->right = kid;
  }

  daddy->left = kid->right;
  kid->right = daddy;

  return kid;
}

NodeTree* rotationLeft(NodeTree *grandpa, NodeTree *daddy, NodeTree *kid, NodeTree *root){
  kid->left = daddy;
  daddy->right = NULL;

  if (grandpa != NULL) {
    if (grandpa->left == daddy) {
      grandpa->left = kid;
    }else{
      grandpa->right = kid;
    }
  }

  if (daddy == root) {
    root = kid;
  }
  return root;
}

int isBalanced(NodeTree *root){
    int left_h = 0;
    int right_h = 0;

    if(root == NULL){
      return 1;
    }
    if (root->left != NULL) {
      left_h = getHeight(root->left);
    }
    if (root->right != NULL) {
      right_h = getHeight(root->right);
    }

    int left_height = MIN(left_h,right_h);
    int right_height = MAX(left_h,right_h);
    int differrence = right_height - left_height;

    if((differrence <= 1 ) && isBalanced(root->left) && isBalanced(root->right)){
      //Arvore balanceada
      return 1;
    } else{
      //Arvore não balanceada
      return 0;
    }
}


// Auxiliares para print usando ascii

NodeTree *find_min(NodeTree *t) {
    if (t == NULL) {
        return NULL;
    }
    else if (t->left == NULL) {
        return t;
    }
    else {
        return find_min(t->left);
    }
}

NodeTree *find_max(NodeTree *t) {
    if (t == NULL) {
        return NULL;
    }
    else if (t->right == NULL) {
        return t;
    }
    else {
        return find_max(t->right);
    }
}

NodeTree *find(int elem, NodeTree *t) {
    if (t == NULL) {
        return NULL;
    }

    if (elem < t->number) {
        return find(elem, t->left);
    }
    else if (elem > t->number) {
        return find(elem, t->right);
    }
    else {
        return t;
    }
}


// Insire na árvore t, a duplicata será descartada
// Retorna um ponteiro para a árvore resultante.

// ajusta o espaço entre os nós esquerdo e direito
int gap = 3;


// usado para imprimir o próximo nó no mesmo nível,
// esta é a coordenada x do próximo caractere impresso
int print_next;

BSTNode *build_ascii_tree_recursive(NodeTree *t) {
    BSTNode *node;

    if (t == NULL) return NULL;

    node = malloc(sizeof(BSTNode));
    node->ptLeft = build_ascii_tree_recursive(t->left);
    node->ptRight = build_ascii_tree_recursive(t->right);

    if (node->ptLeft != NULL) {
        node->ptLeft->parentDir = -1;
    }

    if (node->ptRight != NULL) {
        node->ptRight->parentDir = 1;
    }

    sprintf(node->label, "%d", t->number);
    node->element = strlen(node->label);

    return node;
}



// Copia a árvore para a estrutura do nó ascii
BSTNode *build_ascii_tree(NodeTree *t) {
    BSTNode *node;
    if (t == NULL){
      return NULL;
    }
    node = build_ascii_tree_recursive(t);
    node->parentDir = 0;
    return node;
}


// Libera todos os nós da árvore dada
void free_ascii_tree(BSTNode *node) {
    if (node == NULL) return;
    free_ascii_tree(node->ptLeft);
    free_ascii_tree(node->ptRight);
    free(node);
}

// A função a seguir preenche a matriz lprofile da árvore especificada.
// Assume que o centro do rótulo da raiz desta árvore
// está localizado em uma posição (x, y). Assume-se que o edgeLength
// campos foram computados para esta árvore.
void compute_lprofile(BSTNode *node, int x, int y) {
    int i, isleft;
    if (node == NULL) return;
    isleft = (node->parentDir == -1);
    lprofile[y] = MIN(lprofile[y], x - ((node->element - isleft) / 2));
    if (node->ptLeft != NULL) {
        for (i = 1; i <= node->edgeLength && y + i < MAX_HEIGHT; i++) {
            lprofile[y + i] = MIN(lprofile[y + i], x - i);
        }
    }
    compute_lprofile(node->ptLeft, x - node->edgeLength - 1, y + node->edgeLength + 1);
    compute_lprofile(node->ptRight, x + node->edgeLength + 1, y + node->edgeLength + 1);
}

void compute_rprofile(BSTNode *node, int x, int y) {
    int i, notleft;
    if (node == NULL){
      return;
    }
    notleft = (node->parentDir != -1);
    rprofile[y] = MAX(rprofile[y], x + ((node->element - notleft) / 2));
    if (node->ptRight != NULL) {
        for (i = 1; i <= node->edgeLength && y + i < MAX_HEIGHT; i++) {
            rprofile[y + i] = MAX(rprofile[y + i], x + i);
        }
    }
    compute_rprofile(node->ptLeft, x - node->edgeLength - 1, y + node->edgeLength + 1);
    compute_rprofile(node->ptRight, x + node->edgeLength + 1, y + node->edgeLength + 1);
}

// Esta função preenche o edgeLength e
// campos de altura da árvore especificada
void filledge(BSTNode *node) {
    int h, hmin, i, delta;
    if (node == NULL){
      return;
    }
    filledge(node->ptLeft);
    filledge(node->ptRight);

    
    /* preenche primeiro o edgeLength do nó */
    if (node->ptRight == NULL && node->ptLeft == NULL) {
        node->edgeLength = 0;
    }else {
        if (node->ptLeft != NULL) {
            for (i = 0; i < node->ptLeft->height && i < MAX_HEIGHT; i++) {
                rprofile[i] = -INFINITY;
            }
            compute_rprofile(node->ptLeft, 0, 0);
            hmin = node->ptLeft->height;
        }else {
            hmin = 0;
        }
        if (node->ptRight != NULL) {
            for (i = 0; i < node->ptRight->height && i < MAX_HEIGHT; i++) {
                lprofile[i] = INFINITY;
            }
            compute_lprofile(node->ptRight, 0, 0);
            hmin = MIN(node->ptRight->height, hmin);
        }
        else {
            hmin = 0;
        }
        delta = 4;
        for (i = 0; i < hmin; i++) {
            delta = MAX(delta, gap + 1 + rprofile[i] - lprofile[i]);
        }

        // Se o nó tiver dois filhos de altura 1, então permitimos o
        // duas folhas para estar dentro de 1, em vez de 2
        if (((node->ptLeft != NULL && node->ptLeft->height == 1) ||
             (node->ptRight != NULL && node->ptRight->height == 1)) && delta > 4) {
            delta--;
        }

        node->edgeLength = ((delta + 1) / 2) - 1;
    }

    
    // preenche a altura do nó
    h = 1;
    if (node->ptLeft != NULL) {
        h = MAX(node->ptLeft->height + node->edgeLength + 1, h);
    }
    if (node->ptRight != NULL) {
        h = MAX(node->ptRight->height + node->edgeLength + 1, h);
    }
    node->height = h;
}

// Esta função imprime o dado nível da árvore dada, assumindo
// que o nó tenha o x cordinate fornecido.
void printLevel(BSTNode *node, int x, int level) {
    int i, isleft;
    if (node == NULL) return;
    isleft = (node->parentDir == -1);
    if (level == 0) {
        for (i = 0; i < (x - print_next - ((node->element - isleft) / 2)); i++) {
            printf(" ");
        }
        print_next += i;
        printf("%s", node->label);
        print_next += node->element;
    }
    else if (node->edgeLength >= level) {
        if (node->ptLeft != NULL) {
            for (i = 0; i < (x - print_next - (level)); i++) {
                printf(" ");
            }
            print_next += i;
            printf("/");
            print_next++;
        }
        if (node->ptRight != NULL) {
            for (i = 0; i < (x - print_next + (level)); i++) {
                printf(" ");
            }
            print_next += i;
            printf("\\");
            print_next++;
        }
    }
    else {
        printLevel(node->ptLeft,
                   x - node->edgeLength - 1,
                   level - node->edgeLength - 1);
        printLevel(node->ptRight,
                   x + node->edgeLength + 1,
                   level - node->edgeLength - 1);
    }
}


// imprime a árvore ascii para determinada estrutura Tree
void showTree(NodeTree *t) {
    BSTNode *proot;
    int xmin, i;
    if (t == NULL){
      return;
    }
    proot = build_ascii_tree(t);
    filledge(proot);
    for (i = 0; i < proot->height && i < MAX_HEIGHT; i++) {
        lprofile[i] = INFINITY;
    }
    compute_lprofile(proot, 0, 0);
    xmin = 0;
    for (i = 0; i < proot->height && i < MAX_HEIGHT; i++) {
        xmin = MIN(xmin, lprofile[i]);
    }
    for (i = 0; i < proot->height; i++) {
        print_next = 0;
        printLevel(proot, -xmin, i);
        printf("\n");
    }
    if (proot->height >= MAX_HEIGHT) {
        printf("(Esta árvore é mais alta que% d e pode ser desenhada incorretamente.)\n", MAX_HEIGHT);
    }
    free_ascii_tree(proot);
}