#ifndef TERM_H
#define TERM_H

// simulador do terminal
// realiza a entrada e saída de valores numéricos
// por enquanto só suporta um terminal

#include "es.h"

typedef struct term_t term_t;

// cria e inicializa um terminal
// retorna NULL em caso de erro
term_t *term_cria(void);

// destrói um terminal
// nenhuma outra operação pode ser realizada no terminal após esta chamada
void term_destroi(term_t *self);

// Funções para implementar o protocolo de acesso a um dispositivo pelo
//   controlador de E/S
err_t term_le(void *disp, int id, int *pvalor);
err_t term_escr(void *disp, int id, int valor);
bool term_pronto(void *disp, int id, acesso_t acesso);

#endif // TERM_H
