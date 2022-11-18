## t0 - simulador de uma CPU

Familiarize-se com o código anexo, que simula uma pequena CPU, que será usada durante o desenvolvimento da disciplina.

Para auxiliar na familiarização com o código, implemente um novo dispositivo, que fornece um número aleatório a cada leitura. **Esse é o E1**.

Para auxiliar na familiarização com a CPU, implemente um programa que lê 10 valores desse dispositivo e imprime os 10 valores no terminal. Pode aumentar o grau de dificuldade imprimindo eles em ordem crescente.

**Alterações em 5out**

- adição das instruções DESVN, DESVP, CHAMA, RET
- adição de um programa asm para testar as novas instruções
- impressão da instrução e do erro durante a execução
- o montador agora aceita as instruções em minúsculas

### Descrição sucinta

A CPU tem 3 registradores:
- PC, o contador de programa, tem o endereço da próxima instrução
- A, acumulador, é usado nas instruções aritméticas, e meio que pra todo o resto
- X, registrador auxiliar, usado para acessos indexados à memória

Além desse, tem um registrador de erro, para quando a CPU detecta algum problema.
Todos os registradores são inicializados em 0.

As instruções que o processador reconhece (por enquanto) estão na tabela abaixo.

Uma intrução pode ocupar uma ou duas posições de memória. A primeira é o código da instrução (campo `código`, entre 0 e 20 na tabela abaixo, o o valor em `mem[PC]`), a segunda é o argumento da instrução (o valor em mem[PC+1], chamado A1 na tabela). O campo `#arg` contém 0 para instruções sem argumento e 1 para as que ocupam duas posições.

Ao final da execução bem sucedida de uma instrução, caso não seja uma instrução de desvio que causou a alteração do PC, o PC é incrementado para apontar para a instrução seguinte (levando em consideração o número de argumentos da instrução).

| código |   nome | #arg | operação  | descrição |
| -----: | :----- | :--: | :-------- | :-------- |
|      0 | NOP    | 0    | -         | não faz nada |
|      1 | PARA   | 0    | err=ERR_CPU_PARADA | para a CPU |
|      2 | CARGI  | 1    | A=A1      | carrega imediato |
|      3 | CARGM  | 1    | A=mem[A1] | carrega da memória |
|      4 | CARGX  | 1    | A=mem[A1+X] | carrega indexado |
|      5 | ARMM   | 1    | mem[A1]=A | armazena na memória |
|      6 | ARMX   | 1    | mem[A1+X]=A | armazena indexado |
|      7 | MVAX   | 0    | X=A       | inicializa X |
|      8 | MVXA   | 0    | A=X       | recupera X |
|      9 | INCX   | 0    | X++       | incrementa X |
|     10 | SOMA   | 1    | A+=mem[A1] | soma |
|     11 | SUB    | 1    | A-=mem[A1] | subtração |
|     12 | MULT   | 1    | A*=mem[A1] | multiplicação |
|     13 | DIV    | 1    | A/=mem[A1] | quociente da divisão |
|     14 | RESTO  | 1    | A%=mem[A1] | resto da divisão |
|     15 | NEG    | 0    | A=-A       | negação |
|     16 | DESV   | 1    | PC=A1      | desvio |
|     17 | DESVZ  | 1    | se A for 0, PC=A1 | desvio condicional |
|     18 | DESVNZ | 1    | se A não for 0, PC=A1 | desvio condicional |
|     19 | DESVN  | 1    | se A < 0, PC=A1 | desvio condicional |
|     20 | DESVP  | 1    | se A > 0, PC=A1 | desvio condicional |
|     21 | CHAMA  | 1    | mem[A1]=PC+2; PC=A1+1 | chama subrotina |
|     22 | RET    | 1    | PC=mem[A1] | retorna de subrotina |
|     23 | LE     | 1    | A=es[A1]   | leitura do dispositivo A1 |
|     24 | ESCR   | 1    | es[A1]=A   | escrita no dispositivo A1 |

A CPU só executa uma instrução se o registrador de erro indicar que a CPU não está em erro (valor ERR_OK).
A execução de uma instrução pode colocar a CPU em erro, por tentativa de execução de instrução ilegal, acesso a posição inválida de memória, acesso a dispositivo de E/S inexistente, etc. 


A implementação está dividida em vários módulos:
- exec, o executor de instruções
- mem, a memória
- es, o controlador de E/S
- rel, um relógio
- term, um terminal
- cpu_estado, mantém o estado interno da CPU
- err, define um tipo para codificar os erros
- instr, com nomes e códigos das instuções
- teste.c, um programa para testar os módulos acima, executando um programa (tá executando o ex1, para executar o ex2 tem que alterar o fonte)
- ex[123].asm, programinhas de teste em linguagem de montagem
- montador.c, um montador para transformar programas .asm em .maq (em linguagem de máquina)
- Makefile, para facilitar a compilação da tralha toda (coloque todos esses arquivos em um diretório e execute o programa 'make' nesse diretório, se tudo der certo, um executável 'teste' será gerado)

O make é meio exigente com o formato do Makefile, as linhas que não iniciam na coluna 1 tem que iniciar com um caractere tab.
Se tiver tendo problemas pra compilar, aqui tá o que o make faz:
```
[benhur@nababinho t0]$ make
gcc -Wall -Werror    montador.c   -o montador
./montador ex1.asm > ex1.maq
./montador ex2.asm > ex2.maq
gcc -Wall -Werror   -c -o teste.o teste.c
gcc -Wall -Werror   -c -o exec.o exec.c
gcc -Wall -Werror   -c -o cpu_estado.o cpu_estado.c
gcc -Wall -Werror   -c -o es.o es.c
gcc -Wall -Werror   -c -o mem.o mem.c
gcc -Wall -Werror   -c -o rel.o rel.c
gcc -Wall -Werror   -c -o term.o term.c
gcc   teste.o exec.o cpu_estado.o es.o mem.o rel.o term.o   -o teste
[benhur@nababinho t0]$ 
```


### Descrição menos sucinta

São dois programas, o montador e o simulador.
O montador traduz um programa escrito em linguagem de montagem em um programa equivalente em linguagem de máquina (um arquivo com os valores que devem ser colocados na memória da máquina simulada).
O simulador, tendo a memória inicializada com o programa, executa as instruções, simulando o comportamento de um computador.

#### Montador

O código do montador está no arquivo `montador.c`.

O montador lê cada linha do arquivo de entrada e traduz nos códigos equivalentes.
Por exemplo, se a linha contiver ` PARA `, ele vai gerar ` 1 ` (o código da instrução PARA, veja a tabela acima); se a linha contiver ` LE 3 ` ele vai gerar ` 19 3 `.

Além dessas conversões diretas, o montador também pode dar valores a símbolos. Tem duas formas de se fazer isso, definindo explicitamente um símbolo com a pseudo instrução `DEFINE` ou com o uso de labels.

Com `DEFINE` pode-se dar nomes a valores constantes. Por exemplo, a instrução ` LE 3 ` pode ser mais facilmente entendida se for escrita ` LE teclado `. Isso pode ser feito definindo `teclado` com o valor `3` com a pseudo instrução ` teclado DEFINE 3 `. É chamada de pseudo instrução porque não é uma instrução do processador, mas uma instrução interna para o montador.

Labels servem para dar nomes para posições de memória. Por exemplo, se quizermos colocar uma instrução que desvie para a instrução ` LE ` acima, temos que saber em que endereço essa instrução está. Com um label, o montador calcula esse endereço. O código abaixo implementa um laço, que executará até que seja lido um valor diferente de zero do dispositivo 2. O label `denovo` será definido com o endereço onde será colocada a instrução `LE`.
```
   ...
   denovo LE 2
          DESVZ denovo
   ...
```

Além de `DEFINE`, o montador reconhece outras duas pseudo instruções, `VALOR` e `ESPACO`. Elas são usadas para facilitar a inicialização e a reserva de espaço para variáveis do programa. `VALOR` tem um número como argumento, e coloca esse valor na próxima posição da memória. `ESPACO` também tem um número como argumento, que diz quantos zeros serão colocador nas próximas posições da memória.
Por exemplo, se o código abaixo for montado no endereço 0, vai colocar o valor 19 (o código de LE) no endereço 0, 5 no endereço 1, 7 no 3, 9 no 4 (INCX), 0 em 5, 6 e 7 (ESPACO), 10 e 8 em 8 e 9 (SOMA).
```
   LE 5
   VALOR 7
   INCX
   ESPACO 3
   SOMA 8
```
A saída do montador para a entrada acima é:
```
   /*   0 */ 19, 5, 7, 9, 0, 0, 0, 10, 8,
```
Esse formato foi escolhido porque pode ser usado diretamente para inicializar um vetor em C:
```
   int memoria[] = {
   /*   0 */ 19, 5, 7, 9, 0, 0, 0, 10, 8,
   };
```

#### Simulador

O código do simulador é formado pelos demais arquivos .c e .h.

O componente principal do simulador é o executor, cuja função `exec_executa_1` simula a execução de uma instrução. Para isso, ela pega na memória o valor que está na posição do PC (que contém o código da próxima instrução a executar), e dependendo chama a função correspondente a esse valor, que será responsável pela simulação dessa instrução. Essas funções têm acesso aos registradores e à memória para realizar essa simulação. As instruções que tem argumento (A1 na tabela de instruções) podem obtê-lo na posição PC+1 da memória. Cada função é também responsável por atualizar o valor do PC caso a execução da instrução tenha transcorrido sem erro.

As instruções de E/S (LE e ESCR) acessam os dispositivos através do módulo `es`.
Para serem acessíveis os dispositivos devem antes ser registrados no módulo `es`. 
Isso é feito na inicialização do programa, em `teste.c`, com chamadas a `es_registra_dispositivo`, contendo como argumentor o número com que esse dispositivo vai ser identificado nas instruções de E/S, o controlador desse dispositivo, o número com que esse dispositivo é identificado pelo controlador, e as funções que devem ser usadas para ler ou escrever nesse dispositivo.
Tem dois controladores implementados, um para ler e escrever números no terminal (`term`) e um para ler o valor do relógio (`rel`). Esse último controla dois dispositivos, um relógio que conta as instruções executadas e outro que conta milisegundos.
