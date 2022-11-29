## t1

### Alterações na implementação em relação ao t0c

- criação de `so`, com o embrião do sistema operacional; na inicialização carrega um programa para a memória
- criação de `contr`, controlador do hardware; centraliza os componentes de hardware
    e implementa o laço principal da simulação.
   O laço principal:
    - executa uma instrução;
    - avança o relógio;
    - atualiza a console.
   Se algum dos passos do laço sinalizar uma interrupção, o controlador chama o SO para tratá-la. O laço é interrompido quando o SO disser que assim deve ser (através da função so_ok()).
- a CPU tem agora 3 modos de execução
  - supervisor - executa qualquer instrução
  - usuário - não executa instruções privilegiadas (LE, ESCR, PARA),
    causa erro ERR_INSTR_PRIV, que é passado pelo controlador ao SO como
    interrupção
  - zumbi - não executa nada, mas não interrompe também; servirá para quando o SO não tiver processo apto a executar
- implementação de chamadas de sistema SO_LE e SO_ESCR para acesso a dispositivos de E/S. A implementação das chamadas está assíncrona, se o dispositivo não estiver pronto retorna com erro, em vez de bloquear a execução do programa.

   Tem ainda a chamada SO_FIM, que serve para um processo pedir para morrer e a chamada SO_CRIA, que serve para criar um novo processo (em A tem o número de identificação do programa a executar). Essas duas chamadas não estão implementadas no SO, o SO entra em pânico (e encerra a execução) caso seja chamado com uma delas. Na verdade, o SO entra em pânoco para qualquer interrupção que não reconheça.
- implementação de interrupção periódica do relógio (o período é escolhido na inicialização do relógio). O SO aceita a interrupção, mas não faz nada.
- tem um novo programa exemplo, ex5, que é uma reimplementação do ex4 com chamadas de sistema.
- tem ainda mais 3 programas exemplo, para uso com processos, init.asm, que cria 2 processos, para executar os programas 1 e 2, e p1 e p2.asm, para serem os programas 1 e 2 (eles são quase iguais ao ex5, mas o p1 só lê e escreve no terminal a e o p2 no b).
- mudaram os comandos da console. Agora além de controlar as filas de E/S dá para controlar a execução. Os comandos aceitos agora são:
  - `etn` entra o número `n` no terminal `t`  ex.: `eb30`
  - `lt`  lê um número do terminal `t` (retira da saída)  ex.: `lc`
  - `zt`  esvazia a saída do terminal `t`  ex: `za`
  - `p`   para a execução
  - `s`   executa uma instrução
  - `c`   continua a execução

   No início a execução está parada. 


### t1 — Implementação de processos

Você deve complementar a implementação fornecida para que tenha suporte a multiprogramação, como descrito a seguir.

O SO manterá toda a informação referente a cada processo em uma tabela de processos. No mínimo, essa tabela conterá o estado da CPU para esse processo, o estado do processo (em execução, pronto, bloqueado), informação que permita saber porque o processo está bloqueado e como/quando desbloqueá-lo. Para facilitar a implementação, manterá inclusive uma cópia de toda a memória principal. A troca de um processo para outro incluirá o salvamento e recuperação de toda a memória do sistema. Mais tarde, quando falarmos sobre gerenciamento de memória, isso será otimizado.

O SO manterá um conjunto de programas que podem ser executados. Um programa é o conteúdo de um arquivo ".maq". Cada programa será designado por um número, e esse número é usado pela chamada de criação de um processo para identificar o programa a executar. Quando um processo for criado, o conteúdo da memória do processo será inicializado a partir do programa.

Na inicialização, o SO deve criar um processo para executar um programa inicial. Os demais processos serão criados por chamadas "SO_CRIA" realizadas pelos processos em execução.

A única forma de bloqueio de um processo será por E/S. As chamadas SO_LE e SO_ESCR devem ser alteradas para chamar es_pronto e bloquear o processo caso o dispositivo não esteja pronto. Cada vez que o SO executa, deve verificar todos os processos bloqueados, e testar se cada um deve desbloquear (chamando es_pronto).

As 4 chamadas de sistema devem ser alteradas (as de E/S para bloquear processos, as demais para criação e término de processo).

O escalonador pode ser o mais simples possível, escolhe qualquer dos processos que esteja pronto.

O funcionamento do SO no atendimento de uma interrupção deve ser algo como:
- identifica o processo que foi interrompido
- salva o contexto (estado do processador, conteúdo da memória) na entrada correspondente ao processo interrompido na tabela de processos (ou não, porque pode ser que nenhum processo estivesse em execução)
- atende à interrupção
- verifica se deve desbloquear algum processo bloqueado
- chama o escalonador (escolhe o processo a executar)
- faz o despacho — recupera o contexto, correspondente ao processo escolhido

Caso o escalonador não tenha conseguido escolher nenhum processo (não tem nenhum processo pronto), o despacho simplesmente coloca a CPU em modo zumbi.

Dá para otimizar realizando o salvamento de contexto logo antes da recuperação, e somente se o processo a executar for diferente do que executou a última vez.

A função so_ok deve causar o final da execução se não houver nenhum processo vivo no sistema.

### Dicas (e respostas a perguntas)

O funcionamento do SO descrito acima é o que se espera que a função `so_int` faça. Atualmente ela faz só a parte de atender á interrupção (parcialmente).

Implementando como descrito (salvando o estado do processador no início e recuperando no final), não esqueça que para alterar o valor de algum registrador de um processo deve-se alterar o estado salvo no descritor do processo.
