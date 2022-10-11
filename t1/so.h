#ifndef SO_H
#define SO_H

// SO
// Simula o sistema operacional
// É chamado na inicialização (quando deve colocar um programa na memória), e
//   depois só quando houver interrupção
//
// Por enquanto não faz quase nada


typedef struct so_t so_t;

#include "contr.h"
#include "err.h"
#include <stdbool.h>

so_t *so_cria(contr_t *contr);

void so_destroi(so_t *self);

// houve uma interrupção do tipo err — trate-a
void so_int(so_t *self, err_t err);

// retorna false se o sistema deve ser desligado
bool so_ok(so_t *self);

#endif // SO_H
