#ifndef TAB_PAG_H
#define TAB_PAG_H

// simulador de tabela de páginas
// contém uma tabela com informação para a tradução de um endereço
//   virtual em físico

#include "err.h"
#include <stdbool.h>

// tipo opaco que representa a tabela de páginas
typedef struct tab_pag_t tab_pag_t;

// cria uma tabela de páginas com suporte a 'num_pag' páginas
//   de tamanho 'tam_pag' cada
// retorna NULL em caso de erro
tab_pag_t *tab_pag_cria(int num_pag, int tam_pag);

// destrói um tabela de páginas
// nenhuma outra operação pode ser realizada na tabela após esta chamada
void tab_pag_destroi(tab_pag_t *self);

// traduz o endereço virtual 'end_v' em endereço físico
// coloca o resultado da tradução em '*pend_f' e retorna ERR_OK, ou,
//   caso a tradução não seja possível, retorna:
//   ERR_FALPAG a tabela diz que a página é inválida
//   ERR_PAGINV a tabela não contém a página
// se não forem NULL, coloca a página em *ppag, o deslocamento em *pdesl,
//   e se a tradução foi OK, o quadro em *pquadro
err_t tab_pag_traduz(tab_pag_t *self, int end_v,
                     int *pend_f, int *ppag, int *pdesl, int *pquadro);

// obtém informação sobre uma página da tabela
bool tab_pag_valida(tab_pag_t *self, int pag);
int tab_pag_quadro(tab_pag_t *self, int pag);
bool tab_pag_acessada(tab_pag_t *self, int pag);
bool tab_pag_alterada(tab_pag_t *self, int pag);

// altera informação sobre uma página da tabela
void tab_pag_muda_valida(tab_pag_t *self, int pag, bool val);
void tab_pag_muda_quadro(tab_pag_t *self, int pag, int val);
void tab_pag_muda_acessada(tab_pag_t *self, int pag, bool val);
void tab_pag_muda_alterada(tab_pag_t *self, int pag, bool val);
#endif  // TAB_PAG_H
