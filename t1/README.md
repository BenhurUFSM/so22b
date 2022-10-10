## t0 - simulador de uma CPU

**t0b-pronto**

Adição de um controlador de tela.

O controlador concentra a E/S de vários terminais (`term`) na mesma tela.
Cada terminal ocupa duas linhas da tela, uma com a saída e outra com a entrada.
Uma linha é usada para a linha de comando do operador.
A tela tem ainda algumas linhas que são usadas para mensagens gerais do programa.

A saída e entrada de cada terminal são somente números, e são implementadas como filas. O controlador imprime o conteúdo dessas filas na linha correspondente da tela.
Quando uma fila de saída está cheia, o dispositivo correspondente fica ocupado e não aceita mais operações até que seja esvaziado pelo operador.
O operador pode também digitar valores para serem colocados na fila de entrada de algum terminal.

Na tela, os terminais são identificados como 'a', 'b', 'c' etc. 
O operador pode esvaziar uma fila de saída digitando a identificação do terminal seguida por 'z' ('az' esvazia a fila do primeiro terminal).
Para inserir um valor na fila de entrada de um terminal, digita a identificação e o valor a ser inserido ('b52' insere o valor 52 na fila de entrada do segundo terminal).

A tela é inicializada chamando `t_inicio()`, e encerrada chamando `t_fim()`. Entre essas duas chamadas, pode-se usar `t_printf()` para imprimir na tela.
A função `t_atualiza()` deve ser chamada periodicamente, para atualizar a tela e ler o teclado.

A implementação da tela foi feita usando a biblioteca `ncurses`.

As filas de saída estão com espaço para 5 inteiros.
O programa exemplo coloca 10 valores na saída 0 (que está sendo conectada ao terminal 'a') de forma controlada (testando se entá ocupado) e 10 valores na saída 3 (conectada ao terminal 'b'), de forma não controlada (vai dar erro se a fila estiver cheia). Para que o programa funcione corretamente até o final, o operador deve esvaziar a fila 'b' antes da fila 'a'.

O programa deve ser executado em um terminal com pelo menos 24 linhas de 80 colunas.
