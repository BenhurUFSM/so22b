## t0 - simulador de uma CPU

Familiarize-se com o código anexo, que simula uma pequena CPU, que será usada durante o desenvolvimento da disciplina.

Para auxiliar na familiarização com o código, implemente um novo dispositivo, que fornece um número aleatório a cada leitura. **Esse é o E1**

Para auxiliar na familiarização com a CPU, implemente um programa que lê 10 valores desse dispositivo e imprime os 10 valores no terminal. Pode aumentar o grau de dificuldade imprimindo eles em ordem crescente.

### Descrição sucinta

A CPU tem 3 registradores:
- PC, o contador de programa, tem o endereço da próxima instrução
- A, acumulador, é usado nas instruções aritméticas, e meio que pra todo o resto
- X, registrador auxiliar, usado para acessos indexados à memória

Além desse, tem um registrador de erro, para quando a CPU detecta algum problema.

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
