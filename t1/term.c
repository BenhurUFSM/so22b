#include "term.h"
#include "tela.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

// TODO: implementar suporte a múltiplos terminais

struct term_t {
  // por enquanto não tem muito o que colocar aqui
};

term_t *term_cria(void)
{
  term_t *self = malloc(sizeof(*self));
  return self;
}

void term_destroi(term_t *self)
{
  free(self);
  return;
}

err_t term_le(void *disp, int id, int *pvalor)
{
  if (!term_pronto(disp, id, leitura)) return ERR_OCUP;
  *pvalor = t_le(id);
  return ERR_OK;
}

err_t term_escr(void *disp, int id, int valor)
{
  if (!term_pronto(disp, id, escrita)) return ERR_OCUP;
  t_print(id, valor);
  return ERR_OK;
}

bool term_pronto(void *disp, int id, acesso_t acesso)
{
  if (acesso == leitura) {
    return t_tem(id);
  } else if (acesso == escrita) {
    return t_livre(id);
  }
  return false;
}
