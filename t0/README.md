## t0 - simulador de uma CPU

Familiarize-se com o código anexo, que simula uma pequena CPU, que será usada durante o desenvolvimento da disciplina.

Para auxiliar na familiarização com o código, implemente um novo dispositivo, que fornece um número aleatório a cada leitura. **Esse é o E1**.

Para auxiliar na familiarização com a CPU, implemente um programa que lê 10 valores desse dispositivo e imprime os 10 valores no terminal. Pode aumentar o grau de dificuldade imprimindo eles em ordem crescente.

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
|     19 | LE     | 1    | A=es[A1]   | leitura de E/S |
|     20 | ESCR   | 1    | es[A1]=A   | escrita de E/S |

A CPU só executa uma instrução se o registrador de erro indicar que a CPU não está em erro (valor ERR_OK).
A execução de uma instrução pode colocar a CPU em erro, por tentativa de execução de instrução ilegal, acesso a posição inválida de memória, acesso a dispositivo de E/S inexistente, etc. 


A implementação está dividida em vários módulos:
- exec, o executor de instruções
- mem, a memória
- es, o controlador de E/S
- rel, um relógio
- term, um terminal
- cpu_estado, mantém o estado interno da CPU
- err.h, define um tipo para codificar os erros
- teste.c, um programa para testar os módulos acima, executando um programa (tá executando o ex1, para executar o ex2 tem que alterar o fonte)
- ex1 e ex2.asm, dois programinhas de teste em linguagem de montagem
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
