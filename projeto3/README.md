## Projeto 3

### Execução

```
gcc proj3.c -o proj3
./proj3
```
### Proposta

Uma agenda de contatos consiste em um conjunto de registros que
possuem as seguintes informações a respeito de cada um de seus
elementos:

* Nome completo (string de até 100 caracteres);
* Telefone celular (string no formato xxxxx-xxxx);
* Endereço (string de até 100 caracteres);
* CEP (inteiro sem sinal); e
* Data de nascimento (string no formato dd/mm/aaaa).

Tal conjunto deve suportar as seguintes funcionalidades:
* Inserir novo registro;
* Remover registros que contenham certa string no nome;
* Visualizar registros que contenham certa string no nome;
* Visualizar todos os registros em ordem alfabética de acordo com o
nome; e
* Sair.

Escreva um programa na linguagem de programação C que utiliza apenas
listas duplamente encadeadas e que implementa uma lista de contatos.

Inicialmente, o programa deve procurar por um arquivo texto chamado
“contatos.txt”, que possui os contatos previamente cadastrados. Os
contatos devem ser carregados na lista e, ao término da execução do
programa, o arquivo deve ser atualizado com os registros removidos e os
adicionados.

Caso o arquivo seja inexistente, deve ser criado um novo arquivo com os
registros inseridos no decorrer do programa.

Junto com a descrição do presente trabalho, há um arquivo “contatos.txt”
de exemplo. O seu formato deve ser seguido.

O programa deve exibir um menu que permita ao usuário utilizar as
funções apresentadas anteriormente. Após a realização de cada operação,
o menu deverá ser exibido novamente, encerrando a execução do
programa apenas se o usuário selecionar a opção “Sair”. É importante
seguir o seguinte requisito: a lista deve sempre estar ordenada por nome
e o único método de ordenação que pode ser utilizado é o insertion sort
[1].

Referências

[1] Wikipedia: https://pt.wikipedia.org/wiki/Insertion_sort, em 08 de maio de
2018.
