#include "mmu.h"
#include "tab_pag.h"
#include <stdlib.h>

// tipo de dados opaco para representar o controlador de memória
struct mmu_t {
  mem_t *mem;          // a memória física
  tab_pag_t *tab_pag;  // a tabela de páginas
  int ultimo_endereco; // o último endereço virtual traduzido pela MMU
};

mmu_t *mmu_cria(mem_t *mem)
{
  mmu_t *self;
  self = malloc(sizeof(*self));
  if (self != NULL) {
    self->mem = mem;
    self->tab_pag = NULL;
  }
  return self;
}

void mmu_destroi(mmu_t *self)
{
  if (self != NULL) {
    free(self);
  }
}

void mmu_usa_tab_pag(mmu_t *self, tab_pag_t *tab_pag)
{
  self->tab_pag = tab_pag;
}

// função auxiliar, traduz um endereço virtual em físico
static err_t traduz_endereco(mmu_t *self, int end_v, int *end_f)
{
  self->ultimo_endereco = end_v;
  // se não tem tabela de páginas, não traduz
  if (self->tab_pag == NULL) {
    *end_f = end_v;
    return ERR_OK;
  }
  return tab_pag_traduz(self->tab_pag, end_v, end_f);
}

err_t mmu_le(mmu_t *self, int endereco, int *pvalor)
{
  int end_fis;
  err_t err = traduz_endereco(self, endereco, &end_fis);
  if (err != ERR_OK) {
    return err;
  }
  return mem_le(self->mem, end_fis, pvalor);
}

err_t mmu_escreve(mmu_t *self, int endereco, int valor)
{
  int end_fis;
  err_t err = traduz_endereco(self, endereco, &end_fis);
  if (err != ERR_OK) {
    return err;
  }
  return mem_escreve(self->mem, end_fis, valor);
}

int mmu_ultimo_endereco(mmu_t *self)
{
  return self->ultimo_endereco;
}
