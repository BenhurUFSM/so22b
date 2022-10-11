#include "so.h"
#include "tela.h"
#include <stdlib.h>

struct so_t {
  contr_t *contr;
  bool paniquei;
};

so_t *so_cria(contr_t *contr)
{
  so_t *self = malloc(sizeof(*self));
  if (self == NULL) return NULL;
  self->contr = contr;
  self->paniquei = false;
  return self;
}

void so_destroi(so_t *self)
{
  free(self);
}

// houve uma interrupção do tipo err — trate-a
void so_int(so_t *self, err_t err)
{
  t_printf("SO: interrupção");
  self->paniquei = true;
}

// retorna false se o sistema deve ser desligado
bool so_ok(so_t *self)
{
  return !self->paniquei;
}
