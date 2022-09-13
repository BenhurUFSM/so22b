#include "term.h"
#include <stdlib.h>
#include <stdio.h>

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
  // quando tiver suporte a múltiplos terminais, 'id' será usado para discriminar qual dos
  //   terminais está sendo acessado, e 'disp' dará acesso ao nosso descritor (term_t).
  // por enquanto, são ignorados.
  printf("Digite um valor: ");
  scanf("%d", pvalor);
  return ERR_OK;
}

err_t term_escr(void *disp, int id, int valor)
{
  printf("[SAÍDA: %d]\n", valor);
  return ERR_OK;
}
