## t0 - simulador de uma CPU

Familiarize-se com o código anexo, que simula uma pequena CPU, que será usada durante o desenvolvimento da disciplina.

Para auxiliar na familiarização com o código, implemente um novo dispositivo, que fornece um número aleatório a cada leitura.

Para auxiliar na familiarização com a CPU, implemente um programa que lê 10 valores desse dispositivo e imprime os 10 valores em ordem crescente no terminal.

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
- teste.c, um programa para testar os módulos acima, executando um programa
- ex1 e ex2.asm, dois programinhas de teste em linguagem de montagem
- montador.c, um montador para transformar programas .asm em .maq (em linguagem de máquina)
- Makefile, para facilitar a compilação da tralha toda
