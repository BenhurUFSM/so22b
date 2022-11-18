#ifndef CONTR_H
#define CONTR_H

// contr
// controla o hardware simulado
// em especial, contém o laço de execução de instruções e verificação de
//   interrupções, com chamada ao SO para tratá-las
// concentra os dispositivos de hardware


#define MEM_TAM 2000        // tamanho da memória principal

typedef struct contr_t contr_t;

#include "mem.h"
#include "mmu.h"
#include "so.h"
#include "exec.h"

contr_t *contr_cria(void);
void contr_destroi(contr_t *self);

// o laço principal da simulação
void contr_laco(contr_t *self);

// informa ao controlador quem é o SO
void contr_informa_so(contr_t *self, so_t *so);

// funções de acesso aos componentes do hardware
mem_t *contr_mem(contr_t *self);
mmu_t *contr_mmu(contr_t *self);
exec_t *contr_exec(contr_t *self);
es_t *contr_es(contr_t *self);

#endif // CONTR_H
