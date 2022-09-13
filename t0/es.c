#include "es.h"
#include <stdio.h>
#include <stdlib.h>

// estrutura para definir um dispositivo
typedef struct {
   f_le_t f_le;     // função para ler um inteiro do dispositivo
   f_escr_t f_escr; // função para escrever um inteiro no dispositivo
   void *contr;     // descritor do dispositivo (arg das f acima)
   int id;          // identificador do (sub)dispositivo (arg das f acima)
} dispositivo_t;

#define N_DISPO 10 // número máximo de dispositivos suportados

// define a estrutura opaca
struct es_t {
  dispositivo_t dispositivo[N_DISPO];
};

es_t *es_cria(void)
{
  es_t *self = calloc(1, sizeof(*self)); // com calloc já zera todos os ptr
  return self;
}

void es_destroi(es_t *self)
{
  free(self);
}

bool es_registra_dispositivo(es_t *self, int dispositivo,
                             void *contr, int id,
                             f_le_t f_le, f_escr_t f_escr)
{
  if (dispositivo < 0 || dispositivo >= N_DISPO) return false;
  self->dispositivo[dispositivo].f_le = f_le;
  self->dispositivo[dispositivo].f_escr = f_escr;
  self->dispositivo[dispositivo].contr = contr;
  self->dispositivo[dispositivo].id = id;
  return true;
}

// função auxiliar, para verificar se tal acesso a tal dispositivo é ok
static err_t verif_acesso(es_t *self, int dispositivo, acesso_t tipo)
{
  if (dispositivo < 0 || dispositivo >= N_DISPO) return ERR_END_INV;
  if (tipo == leitura && self->dispositivo[dispositivo].f_le == NULL) {
    return ERR_OP_INV;
  }
  if (tipo == escrita && self->dispositivo[dispositivo].f_escr == NULL) {
    return ERR_OP_INV;
  }
  return ERR_OK;
}

err_t es_le(es_t *self, int dispositivo, int *pvalor)
{
  err_t err = verif_acesso(self, dispositivo, leitura);
  if (err != ERR_OK) return err;
  void *contr = self->dispositivo[dispositivo].contr;
  int id = self->dispositivo[dispositivo].id;
  return self->dispositivo[dispositivo].f_le(contr, id, pvalor);
}

err_t es_escreve(es_t *self, int dispositivo, int valor)
{
  err_t err = verif_acesso(self, dispositivo, escrita);
  if (err != ERR_OK) return err;
  void *contr = self->dispositivo[dispositivo].contr;
  int id = self->dispositivo[dispositivo].id;
  return self->dispositivo[dispositivo].f_escr(contr, id, valor);
}
