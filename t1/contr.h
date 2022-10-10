#ifndef CONTR_H
#define CONTR_H

// contr
// controla o hardware simulado
// em especial, contém o laço de execução de instruções e verificação de
//   interrupções, com chamada ao SO para tratá-las
// concentra os dispositivos de hardware

typedef struct contr_t contr_t;

contr_t *contr_cria(void);
void contr_destroi(contr_t *self);

// o laço principal da simulação
void contr_laco(contr_t *self);

#endif // CONTR_H
