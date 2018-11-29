#ifndef _binaryTree_h
#define _binaryTree_h

typedef struct NodeTree{
 int number;
 struct NodeTree *left;
 struct NodeTree *right;
}NodeTree;


/* Funções obrigatórias */
NodeTree *loadTreeFromFile(char* arquivo);
void showTree(NodeTree *node);
void isFull(NodeTree*);
void searchValue(NodeTree * arv, int num);
int getHeight(NodeTree *root);
NodeTree *removeValue(NodeTree*,int);
void printInOrder(NodeTree *no);
void printPreOrder(NodeTree *no);
void printPostOrder(NodeTree *no);
NodeTree* balanceTree(NodeTree* root);
int isFullTree(NodeTree *root);
NodeTree *NewNode(int number);
NodeTree *insert(NodeTree *node,int number);
void fillLevel(NodeTree *nodes[],NodeTree *node,int targetLevel,int level,int nr);
void printNode(int , int);
void printCentered(int,char*);
void printSlahes(int , int , NodeTree *const *nodes);
void printNodesForLevel(NodeTree *,int, int);
int getLevelUtil(NodeTree *root, int number, int level);
int getLevel(NodeTree *root, int number);
NodeTree* minValueNode(NodeTree *node);
NodeTree *libera(NodeTree *a);
int vazia(NodeTree *a);
void menu();
void pause();
void sair();
NodeTree * setBackbone(NodeTree *root);
int isBalanced(NodeTree *root);
NodeTree* rotationLeft(NodeTree *grandpa, NodeTree *daddy, NodeTree *kid, NodeTree *root);
NodeTree* rotationRight(NodeTree *grandpa, NodeTree *daddy, NodeTree *kid);

int flag;
#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))


#endif
