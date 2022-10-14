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

   Tem ainda a chamada SO_FIM, que serve para um processo pedir para morrer. O SO entra em pânico (e encerra a execução) nessa chamada. Na verdade, o SO faz isso para qualquer interrupção que não reconheça.
- implementação de interrupção periódica do relógio (o período é escolhido na inicialização do relógio). O SO aceita a interrupção, mas não faz nada.
- tem um novo programa exemplo, ex5, que é uma reimplementação do ex4 com chamadas de sistema.
