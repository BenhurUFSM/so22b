#include "tab_pag.h"
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
  bool valida;    // esta entrada é válida
  int quadro;     // em que quadro está esta página
  bool acessada;  // esta página foi acessada
  bool alterada;  // esta página foi alterada
} descr_pag_t;

struct tab_pag_t {
  int num_pag;
  int tam_pag;
  descr_pag_t *tab;
};

tab_pag_t *tab_pag_cria(int num_pag, int tam_pag)
{
  tab_pag_t *self;
  self = malloc(sizeof(*self));
  if (self != NULL) {
    self->num_pag = num_pag;
    self->tam_pag = tam_pag;
    // calloc zera a memória, os descritores terão 'false' em 'valida'
    self->tab = calloc(num_pag, sizeof(descr_pag_t));
    if (self->tab == NULL) {
      free(self);
      return NULL;
    }
  }
  return self;
}

void tab_pag_destroi(tab_pag_t *self)
{
  if (self != NULL) {
    free(self->tab);
    free(self);
  }
}

err_t tab_pag_traduz(tab_pag_t *self, int end_v,
                     int *pend_f, int *ppag, int *pdesl, int *pquadro)
{
  int pagina = end_v / self->tam_pag;
  int deslocamento = end_v % self->tam_pag;
  if (ppag != NULL) {
    *ppag = pagina;
  }
  if (pdesl != NULL) {
    *pdesl = deslocamento;
  }
  if (pagina < 0 || pagina >= self->num_pag) {
    return ERR_PAGINV;
  }
  if (!self->tab[pagina].valida) {
    return ERR_FALPAG;
  }
  int quadro = self->tab[pagina].quadro;
  if (pquadro != NULL) {
    *pquadro = quadro;
  }
  if (pend_f != NULL) {
    *pend_f = quadro * self->tam_pag + deslocamento;
  }
  return ERR_OK;
}

bool tab_pag_valida(tab_pag_t *self, int pag)
{
  return self->tab[pag].valida;
}


int tab_pag_quadro(tab_pag_t *self, int pag)
{
  return self->tab[pag].quadro;
}


bool tab_pag_acessada(tab_pag_t *self, int pag)
{
  return self->tab[pag].acessada;
}


bool tab_pag_alterada(tab_pag_t *self, int pag)
{
  return self->tab[pag].alterada;
}



// altera informação sobre uma página da tabela
void tab_pag_muda_valida(tab_pag_t *self, int pag, bool val)
{
  self->tab[pag].valida = val;
}


void tab_pag_muda_quadro(tab_pag_t *self, int pag, int val)
{
  self->tab[pag].quadro = val;
}


void tab_pag_muda_acessada(tab_pag_t *self, int pag, bool val)
{
  self->tab[pag].acessada = val;
}


void tab_pag_muda_alterada(tab_pag_t *self, int pag, bool val)
{
  self->tab[pag].alterada = val;
}
