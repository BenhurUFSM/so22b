#ifndef _TELA_H_
#define _TELA_H_

// entrada e saída de números, simulando vários terminais independentes
//
// a entrada pode ser feita programaticamente (com a função t_ins) ou
//   interativamente, digitando uma letra (a para o primeiro terminal, 
//   b para o segundo) e o número a entrar
//
// além da saída em cada terminal (só números), tem a saída da console,
//   em formato livre (para debug)

#include <stdbool.h>

#define N_LIN 24  // número de linhas na tela
#define N_COL 80  // número de colunas na tela
#define N_TERM 8  // número de terminais, cada um ocupa 2 linhas na tela

// inicializa a tela
void t_inicio(void);

// finaliza a utilização da tela
void t_fim(void);

// retorna true se o terminal t estiver livre (para ser escrito)
bool t_livre(int t);

// escreve o número n no terminal t
// só deve ser chamada quando o terminal tiver livre
void t_print(int t, int n);

// retorna true se tiver número pronto para ser lido no terminal t
bool t_tem(int t);

// lê um número do terminal t
// só deve ser chamada quando tiver número pronto no terminal t
int t_le(int t);

// insere um número a ser lido do terminal t
void t_ins(int t, int n);

// imprime na linha de status
void t_status(char *txt);

// imprime no console
int t_printf(char *formato, ...);

// esta função deve ser chamada periodicamente para que tela funcione
void t_atualiza(void);

#endif // _TELA_H_
