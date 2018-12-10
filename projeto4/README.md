## Proposta

Uma simulação controlada por eventos é um programa de computador
que mimetiza o comportamento de pessoas ou objetos em um sistema,
em resposta a eventos que ocorrem em certos instantes de tempo. O
programa deve manter uma estrutura de dados para cada pessoa ou
objeto e colocá-lo em uma fila de acordo com o tempo e/ou prioridade do
evento. O objetivo deste projeto é escrever um programa de simulação
que gerencia o uso das pistas de um grande aeroporto. As pistas são
usadas para pousos e decolagens e os requisitos e parâmetros desejados
são descritos a seguir.

• O aeroporto possui três pistas: 1, 2 e 3, sendo que a pista 3
somente é usada para decolagens, a menos que ocorra uma
emergência;

• As pistas 1 e 2 são usadas tanto para pousos quanto para
decolagens.

• A cada execução do programa (Uma UnidadeTempo é igual a 5min),
de 20 a 64 voos requerem pousos ou decolagens ao aeroporto. Os
voos são identificados por duas letras maiúsculas, seguidas por 4
números inteiros. Uma lista com 64 códigos de voos é fornecida
abaixo.

• A letra A, indicando Aproximação, seguida de um valor inteiro de 0
a 12, onde o valor 0 indica prioridade máxima de pouso (0 de
combustível restante, sendo que a cada 10*UnidadeTempo a
quantidade de combustível deve decrescer em um em todas as
aeronaves em aproximação), ou a letra D, de Decolagem (sem
valores marcados de combustível).

• Cada voo é composto por:
o um código de voo contendo 2 letras maiúsculas e 4 números
inteiros (esses códigos são somente para identificação, use
somente os códigos de voo fornecidos neste documento, é
fornecido 64 códigos, o máximo alcance do seu número
aleatório de voos);o o modo de voo (aproximação ‘A’ ou decolagem ‘D’);
o nível de combustível caso o modo de voo seja ‘A’;

• Os voos devem ser atendidos em uma estratégia de fila. Quando
uma emergência (0 de combustível para qualquer Aproximação)
acontecer, a aeronave em questão tomará a frente da fila de espera,
ganhando prioridade.

• Se ocorrer de 3 ou mais aeronaves se aproximarem com 0 nível de
combustível, uma mensagem de “ALERTA GERAL DE DESVIO DE
AERONAVE” deve ser emitida. Nesse caso, a pista 3 deve ser
utilizada para realizar um POUSO caso esteja disponível. Caso não
esteja disponível, a aeronave deve esperar mais uma unidade de
tempo em aproximação para que caia (aeronaves com nível de
combustível menor que zero, devem cair), deve ser exibida uma
mensagem de “ALERTA CRÍTICO, AERONAVE IRÁ CAIR” e
simplesmente removê-la imediatamente da fila, tratando as
aeronaves restantes.

• Caso alguma pista seja liberada enquanto uma aeronave está
planando, isto é, com nível de combustível igual a zero, esta poderá
pousar, entretanto, caso o nível de combustível se torne menor que
zero (decrescendo mais um nível de combustível ao final de
10*UnidadeTempo) a aeronave deverá cair imediatamente.

• Um relógio global deve ser inicializado (o horário de início é de livre
escolha) e toda a lista deve ser gerada aleatoriamente no início da
execução.

• O programa de simulação deverá gerar aleatoriamente os valores
das seguintes variáveis: NVoos (20 a 64), NAproximações (10 a 32),
NDecolagens (10 a 32), CombA (0 a 12), sendo que NAproximações
+ NDecolagens = NVoos e CombA é o combustível das aeronaves
em aproximação. Após gerar os valores, o programa deve
selecionar os códigos dos voos da lista, e montar a fila de
atendimento. A simulação deverá cobrir todos os pedidos gerados,
um a um, e imprimir a sequência de atendimento na tela. Devem
ser considerados os tempos nos quais as pistas ficam indisponíveis
para novos voos em cada procedimento. O tempo gasto durante a
aproximação é de 1*UnTempo; um pouso, 3*UnTempo e o
tempo gasto durante uma decolagem é igual a 2*UnTempo.

• É importante lembrar que as aeronaves que irão decolar, não
precisarão ter nível de combustível.
Elementos a serem mostrados na tela:
---------------------------------------------------------------------------------
“Aeroporto Internacional de Brasília”
Hora Inicial:
Fila de Pedidos: [código do voo – P/D – prioridade]
NVoos:
Naproximações:
NDecolagens:
---------------------------------------------------------------------------------
Listagem de eventos:
Código do voo:
Status: [“aeronave decolou” ou “aeronave pousou”]
Horário do início do procedimento:
Número da pista:
Código do voo:
Status: [“aeronave decolou” ou “aeronave pousou”]
Horário do início do procedimento:
Número da pista:
Código do voo:
Status: [“aeronave decolou” ou “aeronave pousou”]
Horário do início do procedimento:
Número da pista:
.
.
.
Lista de sequências de códigos de voos para o programa: [“VG3001”,
“JJ4404”, “LN7001”, “TG1501”, “GL7602”, “TT1010”, “AZ1009”, “AZ1008”,
“AZ1010”, “TG1506”, “VG3002”, “JJ4402”, “GL7603”, “RL7880”, “AL0012”,
“TT4544”, “TG1505”, “VG3003”, “JJ4403”, “JJ4401”, “LN7002”, “AZ1002”,
“AZ1007”, “GL7604”, “AZ1006”, “TG1503”, “AZ1003”, “JJ4403”, “AZ1001”,
“LN7003”, “AZ1004”, “TG1504”, “AZ1005”, “TG1502”, “GL7601”,
“TT4500”, “RL7801”, “JJ4410”, “GL7607”, “AL0029”, “VV3390”, “VV3392”,
“GF4681”, GF4690”, “AZ1020”, “JJ4435”, “VG3010”, “LF0920”, “AZ1065”,
“LF0978”, “RL7867”, “TT4502”, “GL7645”, “LF0932”, “JJ4434”, “TG1510”,
“TT1020”, “AZ1098”, “BA2312”, “VG3030”, “BA2304”, “KL5609”,
“KL5610”, KL5611”]
Escreva um programa, em linguagem de programação C, que deverá
simular o controle de prioridade de pousos e decolagens no aeroporto
(parâmetros como fornecidos). A prioridade deve ser implementada como
fila (implementada com listas de encadeamento simples) e os parâmetros
gerados aleatoriamente a cada chamada do programa.