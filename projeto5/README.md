## Projeto 5

### Execução

```
gcc proj5.c binaryTree.c binaryTree.h -lm -o proj5
```

### Proposta 

O presente trabalho consiste na implementação de uma biblioteca que
realize as operações básicas sobre árvores binárias de busca que
armazenam valores inteiros. As seguintes funções devem ser
contempladas:

* loadTreeFromFile, que recebe uma string com o nome do arquivo
contendo os elementos a serem inseridos na árvores e retorna o
endereço da raiz da árvore montada;

* showTree, que recebe como entrada o endereço do nó raiz e
imprime na tela a árvore como está atualmente montada conforme
o padrão abaixo. Essa função é obrigatória, ou seja, sem sua
implementação a nota atribuída ao trabalho será zero.

```

         1
        / \
       2   3
      / \ / \
     4  5 6  7
          \  \
           8  9
           
 ```
 
* isFull, que recebe como entrada o endereço do nó raiz e imprime na
tela se a árvore é cheia ou não.

* searchValue, que recebe como entrada o endereço do nó raiz e um
valor inteiro. Deve buscar o valor na árvore e imprimir na tela o
nível do nó encontrado, o valor de seu pai e, caso possua, seu
irmão. Caso não seja encontrado, deve-se imprimir uma mensagem
alertando que o valor não está presente na árvore.

* getHeight, que recebe como entrada o endereço do nó raiz e
imprime na tela a altura da árvore.

* removeValue, que recebe como entrada o endereço do nó raiz e um
valor inteiro. Esse valor inteiro deve ser removido da árvore. Caso
o valor não seja encontrado, deve-se imprimir uma mensagem
alertando que o valor não está presente na árvore.

* printInOrder, que recebe como entrada o endereço do nó raiz e 
imprime a árvore utilizando o algoritmo in order.

* printPreOrder, que recebe como entrada o endereço do nó raiz e
imprime a árvore utilizando o algoritmo pre order.

* printPostOrder, que recebe como entrada o endereço do nó raiz e
imprime a árvore utilizando o algoritmo post order.

* balanceTree, que recebe como entrada o endereço do nó raiz e
realiza o balanceamento da árvore, caso esteja desbalanceada.
Caso a árvore já esteja balanceada, nenhum processamento extra
deve ser realizado. O método utilizado deve ser o de rotações.
Observe que é necessário checar se a árvore está balanceada, não
bastando apenas tentar realizar o balanceamento sem checagem
prévia.

O programa deve apresentar um menu que permita ao usuário escolher
qual ação deve ser executada. Após a execução de cada escolha, o menu
deve ser exibido novamente, até que o usuário escolha pelo encerramento
do programa via menu.

Juntamente com o trabalho, é fornecido um conjunto de arquivos texto
com valores para serem testados no programa.
A avaliação das funcionalidades acima listadas será realizada de forma
binária, ou seja, será dado o ponto integral apenas se seu funcionamento
for correto, resultando em nota zero se o item apresentar alguma falha.
Cada item vale 1 ponto
