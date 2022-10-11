#include "so.h"
#include "tela.h"
#include <stdlib.h>

struct so_t {
  contr_t *contr;
  bool paniquei;
};

// funções auxiliares
static void init_mem(so_t *self);
static void panico(so_t *self);

so_t *so_cria(contr_t *contr)
{
  so_t *self = malloc(sizeof(*self));
  if (self == NULL) return NULL;
  self->contr = contr;
  self->paniquei = false;
  init_mem(self);
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


// carrega um programa na memória
static void init_mem(so_t *self)
{
  // programa para executar na nossa CPU
  int progr[] = {
  #include "ex4.maq"
  };
  int tam_progr = sizeof(progr)/sizeof(progr[0]);

  // inicializa a memória com o programa 
  mem_t *mem = contr_mem(self->contr);
  for (int i = 0; i < tam_progr; i++) {
    if (mem_escreve(mem, i, progr[i]) != ERR_OK) {
      t_printf("so.init_mem: erro de memória, endereco %d\n", i);
      panico(self);
    }
  }
}
  
static void panico(so_t *self) 
{
  t_printf("Problema irrecuperável no SO");
  self->paniquei = true;
}
