#include "exec.h"
#include <stdbool.h>
#include <stdlib.h>

// uma CPU tem estado, memoria, controlador de ES
struct exec_t {
  cpu_estado_t *estado;
  mem_t *mem;
  es_t *es;
};

exec_t *exec_cria(mem_t *mem, es_t *es)
{
  exec_t *self;
  self = malloc(sizeof(*self));
  if (self != NULL) {
    self->estado = cpue_cria();
    cpue_muda_SP(self->estado,mem_heap(mem));
    self->mem = mem;
    self->es = es;
  }
  return self;
}

void exec_destroi(exec_t *self)
{
  // eu nao criei memoria, es; quem criou que destrua!
  cpue_destroi(self->estado);
  free(self);
}

void exec_copia_estado(exec_t *self, cpu_estado_t *estado)
{
  cpue_copia(self->estado, estado);
}

void exec_altera_estado(exec_t *self, cpu_estado_t *estado)
{
  cpue_copia(estado, self->estado);
}


// ---------------------------------------------------------------------
// funções auxiliares para usar durante a execução das instruções
// alteram o estado da CPU caso ocorra erro

// lê um valor da memória
static bool pega_mem(exec_t *self, int endereco, int *pval)
{
  err_t err = mem_le(self->mem, endereco, pval);
  if (err != ERR_OK) {
    cpue_muda_erro(self->estado, err, endereco);
  }
  return err == ERR_OK;
}

// lê o opcode da instrução no PC
static bool pega_opcode(exec_t *self, int *popc)
{
  return pega_mem(self, cpue_PC(self->estado), popc);
}

// lê o argumento 1 da instrução no PC
static bool pega_A1(exec_t *self, int *pA1)
{
  return pega_mem(self, cpue_PC(self->estado) + 1, pA1);
}

static void incrementa_PC(exec_t *self)
{
   cpue_muda_PC(self->estado, cpue_PC(self->estado) + 1);
}

static void incrementa_PC2(exec_t *self)
{
   cpue_muda_PC(self->estado, cpue_PC(self->estado) + 2);
}

// escreve um valor na memória
static bool poe_mem(exec_t *self, int endereco, int val)
{
  err_t err = mem_escreve(self->mem, endereco, val);
  if (err != ERR_OK) {
    cpue_muda_erro(self->estado, err, endereco);
  }
  return err == ERR_OK;
}

// lê um valor da E/S
static bool pega_es(exec_t *self, int dispositivo, int *pval)
{
  err_t err = es_le(self->es, dispositivo, pval);
  if (err != ERR_OK) {
    cpue_muda_erro(self->estado, err, dispositivo);
  }
  return err == ERR_OK;
}

// escreve um valor na E/S
static bool poe_es(exec_t *self, int dispositivo, int val)
{
  err_t err = es_escreve(self->es, dispositivo, val);
  if (err != ERR_OK) {
    cpue_muda_erro(self->estado, err, dispositivo);
  }
  return err == ERR_OK;
}

// ---------------------------------------------------------------------
// funções auxiliares para implementação de cada instrução

static void op_NOP(exec_t *self) // não faz nada
{
  incrementa_PC(self);
}

static void op_PARA(exec_t *self) // para a CPU
{
  cpue_muda_erro(self->estado, ERR_CPU_PARADA, 0);
}

static void op_CARGI(exec_t *self) // carrega imediato
{
  int A1;
  if (pega_A1(self, &A1)) {
    cpue_muda_A(self->estado, A1);
    incrementa_PC2(self);
  }
}

static void op_CARGM(exec_t *self) // carrega da memória
{
  int A1, mA1;
  if (pega_A1(self, &A1) && pega_mem(self, A1, &mA1)) {
    cpue_muda_A(self->estado, mA1);
    incrementa_PC2(self);
  }
}

static void op_CARGX(exec_t *self) // carrega indexado
{
  int A1, mA1mX;
  int X = cpue_X(self->estado);
  if (pega_A1(self, &A1) && pega_mem(self, A1+X, &mA1mX)) {
    cpue_muda_A(self->estado, mA1mX);
    incrementa_PC2(self);
  }
}

static void op_ARMM(exec_t *self) // armazena na memória
{
  int A1;
  if (pega_A1(self, &A1) && poe_mem(self, A1, cpue_A(self->estado))) {
    incrementa_PC2(self);
  }
}

static void op_ARMX(exec_t *self) // armazena indexado
{
  int A1;
  int X = cpue_X(self->estado);
  if (pega_A1(self, &A1) && poe_mem(self, A1+X, cpue_A(self->estado))) {
    incrementa_PC2(self);
  }
}

static void op_MVAX(exec_t *self) // copia A para X
{
  cpue_muda_X(self->estado, cpue_A(self->estado));
  incrementa_PC(self);
}

static void op_MVXA(exec_t *self) // copia X para A
{
  cpue_muda_A(self->estado, cpue_X(self->estado));
  incrementa_PC(self);
}

static void op_INCX(exec_t *self) // incrementa X
{
  cpue_muda_X(self->estado, cpue_X(self->estado)+1);
  incrementa_PC(self);
}

static void op_SOMA(exec_t *self) // soma
{
  int A1, mA1;
  if (pega_A1(self, &A1) && pega_mem(self, A1, &mA1)) {
    cpue_muda_A(self->estado, cpue_A(self->estado) + mA1);
    incrementa_PC2(self);
  }
}

static void op_SUB(exec_t *self) // subtração
{
  int A1, mA1;
  if (pega_A1(self, &A1) && pega_mem(self, A1, &mA1)) {
    cpue_muda_A(self->estado, cpue_A(self->estado) - mA1);
    incrementa_PC2(self);
  }
}

static void op_MULT(exec_t *self) // multiplicação
{
  int A1, mA1;
  if (pega_A1(self, &A1) && pega_mem(self, A1, &mA1)) {
    cpue_muda_A(self->estado, cpue_A(self->estado) * mA1);
    incrementa_PC2(self);
  }
}

static void op_DIV(exec_t *self) // divisão
{
  int A1, mA1;
  if (pega_A1(self, &A1) && pega_mem(self, A1, &mA1)) {
    cpue_muda_A(self->estado, cpue_A(self->estado) / mA1);
    incrementa_PC2(self);
  }
}

static void op_RESTO(exec_t *self) // resto
{
  int A1, mA1;
  if (pega_A1(self, &A1) && pega_mem(self, A1, &mA1)) {
    cpue_muda_A(self->estado, cpue_A(self->estado) % mA1);
    incrementa_PC2(self);
  }
}

static void op_NEG(exec_t *self) // inverte sinal
{
  cpue_muda_A(self->estado, -cpue_A(self->estado));
  incrementa_PC(self);
}

static void op_DESV(exec_t *self) // desvio incondicional
{
  int A1;
  if (pega_A1(self, &A1)) {
    cpue_muda_PC(self->estado, A1);
  }
}

static void op_DESVZ(exec_t *self) // desvio condicional
{
  if (cpue_A(self->estado) == 0) {
    op_DESV(self);
  } else {
    incrementa_PC2(self);
  }
}

static void op_DESVNZ(exec_t *self) // desvio condicional
{
  if (cpue_A(self->estado) != 0) {
    op_DESV(self);
  } else {
    incrementa_PC2(self);
  }
}

static void op_LE(exec_t *self) // leitura de E/S
{
  int A1, dado;
  if (pega_A1(self, &A1) && pega_es(self, A1, &dado)) {
    cpue_muda_A(self->estado, dado);
    incrementa_PC2(self);
  }
}

static void op_ESCR(exec_t *self) // escrita de E/S
{
  int A1;
  if (pega_A1(self, &A1) && poe_es(self, A1, cpue_A(self->estado))) {
    incrementa_PC2(self);
  }
}

static void op_CMPA(exec_t *self) // compara A com A1
{
  int A1, mA1;
  if (pega_A1(self, &A1) && pega_mem(self, A1, &mA1)) {
    cpue_define_status_flag(self->estado,cpue_A(self->estado)-mA1);
    incrementa_PC2(self);
  }
}

static void op_DESVA(exec_t *self) // desvio condicional
{
  if (cpue_verifica_maior_flag(self->estado)!=0) {
    op_DESV(self);
  } else {
    incrementa_PC2(self);
  }
}
static void op_DESVB(exec_t *self) // desvio condicional
{
  if (cpue_verifica_menor_flag(self->estado)!=0) {
    op_DESV(self);
  } else {
    incrementa_PC2(self);
  }
}
static void op_DESVE(exec_t *self) // desvio condicional
{
  if (cpue_verifica_igual_flag(self->estado)!=0) {
    op_DESV(self);
  } else {
    incrementa_PC2(self);
  }
}
static void op_PUSHA(exec_t *self)
{
  int sp = cpue_SP(self->estado);
  if(poe_mem(self, sp,cpue_A(self->estado))){
    cpue_muda_SP(self->estado,sp+1);
    incrementa_PC(self);
  }else{
    cpue_muda_erro(self->estado, ERR_ESTOURO_PILHA, sp);
  }
}
static void op_POPA(exec_t *self)
{
  int sp = cpue_SP(self->estado);
  int val;
  if(mem_heap(self->mem)<sp && pega_mem(self, sp-1,&val)){
    cpue_muda_SP(self->estado,sp-1);
    cpue_muda_A(self->estado,val);
    incrementa_PC(self);
  }else{
    cpue_muda_erro(self->estado, ERR_ESTOURO_PILHA, sp);
  }
}

static void op_PUSHX(exec_t *self)
{
  int sp = cpue_SP(self->estado);
  if(poe_mem(self, sp,cpue_X(self->estado))){
    cpue_muda_SP(self->estado,sp+1);
    incrementa_PC(self);
  }else{
    cpue_muda_erro(self->estado, ERR_ESTOURO_PILHA, sp);
  }
}
static void op_POPX(exec_t *self)
{
  int sp = cpue_SP(self->estado);
  int val;
  if(mem_heap(self->mem)<sp && pega_mem(self, sp-1,&val)){
    cpue_muda_SP(self->estado,sp-1);
    cpue_muda_X(self->estado,val);
    incrementa_PC(self);
  }else{
    cpue_muda_erro(self->estado, ERR_ESTOURO_PILHA, sp);
  }
}


err_t exec_executa_1(exec_t *self)
{
  // não executa se CPU já estiver em erro
  if (cpue_erro(self->estado) != ERR_OK) return cpue_erro(self->estado);

  int opcode;
  if (!pega_opcode(self, &opcode)) return cpue_erro(self->estado);

  switch (opcode) {
    case NOP:    op_NOP(self);    break;
    case PARA:   op_PARA(self);   break;
    case CARGI:  op_CARGI(self);  break;
    case CARGM:  op_CARGM(self);  break;
    case CARGX:  op_CARGX(self);  break;
    case ARMM:   op_ARMM(self);   break;
    case ARMX:   op_ARMX(self);   break;
    case MVAX:   op_MVAX(self);   break;
    case MVXA:   op_MVXA(self);   break;
    case INCX:   op_INCX(self);   break;
    case SOMA:   op_SOMA(self);   break;
    case SUB:    op_SUB(self);    break;
    case MULT:   op_MULT(self);   break;
    case DIV:    op_DIV(self);    break;
    case RESTO:  op_RESTO(self);  break;
    case NEG:    op_NEG(self);    break;
    case DESV:   op_DESV(self);   break;
    case DESVZ:  op_DESVZ(self);  break;
    case DESVNZ: op_DESVNZ(self); break;
    case LE:     op_LE(self);     break;
    case ESCR:   op_ESCR(self);   break;
    case CMPA:   op_CMPA(self);   break;
    case DESVA:  op_DESVA(self);  break;
    case DESVB:  op_DESVB(self);  break;
    case DESVE:  op_DESVE(self);  break;
    case POPA:   op_POPA(self);   break;
    case PUSHA:  op_PUSHA(self);  break;
    case POPX:   op_POPX(self);   break;
    case PUSHX:  op_PUSHX(self);  break;
    default:     cpue_muda_erro(self->estado, ERR_INSTR_INV, 0);
  }

  return cpue_erro(self->estado);
}
