#include "rel.h"
#include <stdlib.h>
#include <time.h>

struct rel_t {
  int agora;
  int periodo;
};

rel_t *rel_cria(int periodo)
{
  rel_t *self;
  self = malloc(sizeof(rel_t));
  if (self != NULL) {
    self->agora = 0;
    self->periodo = periodo;
  }
  return self;
}

void rel_destroi(rel_t *self)
{
  free(self);
}

err_t rel_tictac(rel_t *self)
{
  self->agora++;
  if (self->periodo != 0 && self->agora % self->periodo == 0) {
    return ERR_TIC;
  }
  return ERR_OK;
}

int rel_agora(rel_t *self)
{
  return self->agora;
}

err_t rel_le(void *disp, int id, int *pvalor)
{
  rel_t *self = disp;
  err_t err = ERR_OK;
  switch (id) {
    case 0:
      *pvalor = self->agora;
      break;
    case 1:
      *pvalor = clock()/(CLOCKS_PER_SEC/1000);
      break;
    default: 
      err = ERR_END_INV;
  }
  return err;
}
