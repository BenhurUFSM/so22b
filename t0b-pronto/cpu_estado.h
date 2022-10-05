#ifndef CPU_E_H
#define CPU_E_H

#include "err.h"

// TAD para manter o estado interno da CPU (valores dos registradores, modo de execução, etc)

typedef struct cpu_estado_t cpu_estado_t;  // estrutura opaca

// cria e inicializa um novo descritor de estado
cpu_estado_t *cpue_cria(void);

// libera a memória ocupada por um descritor de estado
void cpue_destroi(cpu_estado_t *self);

// copia um descritor de estado para outro
void cpue_copia(cpu_estado_t *self, cpu_estado_t *outro);

// imprime o conteúdo de um descritor (para debug)
void cpue_imprime(cpu_estado_t *self);

// retorna o valor do contador de programa
int cpue_PC(cpu_estado_t *self);
// retorna o valor do registrador 'A'
int cpue_A(cpu_estado_t *self);
// retorna o valor do registrador 'X'
int cpue_X(cpu_estado_t *self);
// retorna o valor do erro interno da CPU
err_t cpue_erro(cpu_estado_t *self);
// retorna o valor do complemento do erro (por exemplo, o endereço em que ocorreu um erro
//   de acesso à memória
int cpue_complemento(cpu_estado_t *self);

// funções para alterar partes do estado
void cpue_muda_PC(cpu_estado_t *self, int val);
void cpue_muda_A(cpu_estado_t *self, int val);
void cpue_muda_X(cpu_estado_t *self, int val);
void cpue_muda_erro(cpu_estado_t *self, err_t err, int complemento);
#endif // CPU_E_H
