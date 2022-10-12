#include "err.h"

static char *nomes[N_ERR] = {
  [ERR_OK]         = "OK",
  [ERR_END_INV]    = "Endereço inválido",
  [ERR_OP_INV]     = "Operação inválida",
  [ERR_OCUP]       = "Dispositivo ocupado",
  [ERR_CPU_PARADA] = "CPU parada",
  [ERR_INSTR_PRIV] = "Instrução privilegiada",
  [ERR_INSTR_INV]  = "Instrução inválida",
  [ERR_SISOP]      = "Chamada de sistema",
  [ERR_TIC]        = "Interrupção de relógio"
};

// retorna o nome de erro
char *err_nome(err_t err)
{
  if (err < ERR_OK || err >= N_ERR) return "DESCONHECIDO";
  return nomes[err];
}
