#include "contr.h"
#include "mem.h"
#include "exec.h"
#include "rel.h"
#include "term.h"
#include "es.h"
#include "so.h"
#include "tela.h"
#include "instr.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>



struct contr_t {
  mem_t *mem;
  exec_t *exec;
  rel_t *rel;
  term_t *term;
  es_t *es;
  so_t *so;
};

// funções auxiliares
static void contr_atualiza_estado(contr_t *self);


contr_t *contr_cria(void)
{
  contr_t *self = malloc(sizeof(*self));
  if (self == NULL) return NULL;
  // cria a memória
  self->mem = mem_cria(MEM_TAM);
  // cria dispositivos de E/S (o relógio e um terminal)
  self->term = term_cria();
  self->rel = rel_cria(0);
  t_inicio();
  // cria o controlador de E/S e registra os dispositivos
  self->es = es_cria();
  es_registra_dispositivo(self->es, 0, self->term, 0, term_le, term_escr, term_pronto);
  es_registra_dispositivo(self->es, 1, self->term, 1, term_le, term_escr, term_pronto);
  es_registra_dispositivo(self->es, 2, self->rel, 0, rel_le, NULL, NULL);
  es_registra_dispositivo(self->es, 3, self->rel, 1, rel_le, NULL, NULL);
  // cria a unidade de execução e inicializa com a memória e E/S
  self->exec = exec_cria(self->mem, self->es);
  self->so = NULL;
  return self;
}

void contr_destroi(contr_t *self)
{
  // destroi todo mundo!
  exec_destroi(self->exec);
  es_destroi(self->es);
  term_destroi(self->term);
  rel_destroi(self->rel);
  t_fim();
  mem_destroi(self->mem);
  free(self);
}

void contr_informa_so(contr_t *self, so_t *so)
{
  self->so = so;
}

mem_t *contr_mem(contr_t *self)
{
  return self->mem;
}

exec_t *contr_exec(contr_t *self)
{
  return self->exec;
}

es_t *contr_es(contr_t *self)
{
  return self->es;
}

void contr_laco(contr_t *self)
{
  // executa uma instrução por vez até SO dizer que chega
  do {
    err_t err;
    err = exec_executa_1(self->exec);
    if (err != ERR_OK) so_int(self->so, err);
    err = rel_tictac(self->rel);
    if (err != ERR_OK) so_int(self->so, err);
    contr_atualiza_estado(self);
    t_atualiza();
  } while (so_ok(self->so));
      
  t_printf("Fim da execução.");
  t_printf("relógio: %d\n", rel_agora(self->rel));
}
 

static void str_estado(char *txt, exec_t *exec, mem_t *mem)
{
  // pega o estado da CPU, imprime registradores, opcode, instrução
  cpu_estado_t *estado = cpue_cria();
  exec_copia_estado(exec, estado);
  int pc, opcode = -1;
  pc = cpue_PC(estado);
  mem_le(mem, pc, &opcode);
  sprintf(txt, "PC=%04d A=%06d X=%06d %02d %s",
                pc, cpue_A(estado), cpue_X(estado), opcode, instr_nome(opcode));
  // imprime argumento da instrução, se houver
  if (instr_num_args(opcode) > 0) {
    char aux[40];
    int A1;
    mem_le(mem, pc+1, &A1);
    sprintf(aux, " %d", A1);
    strcat(txt, aux);
  }
  // imprime estado de erro da CPU, se for o caso
  err_t err = cpue_erro(estado);
  if (err != ERR_OK) {
    char aux[40];
    sprintf(aux, " E=%d(%d) %s", err, cpue_complemento(estado), err_nome(err));
    strcat(txt, aux);
  }
  cpue_destroi(estado);
}

void contr_atualiza_estado(contr_t *self)
{
  char s[N_COL+1];
  str_estado(s, self->exec, self->mem);
  t_status(s);
}
