#ifndef REL_H
#define REL_H

// simulador do relógio
// registra a passagem do tempo

#include "err.h"

typedef struct rel_t rel_t;

// cria e inicializa um relógio
// o relógio causa uma interrupção a cada 'periodo' chamadas a tictac
// retorna NULL em caso de erro
rel_t *rel_cria(int periodo);

// destrói um relógio
// nenhuma outra operação pode ser realizada no relógio após esta chamada
void rel_destroi(rel_t *self);

// registra a passagem de uma unidade de tempo
// esta função é chamada pelo controlador após a execução de cada instrução
// retorna ERR_TIC se for hora de interromper, ou ERR_OK
err_t rel_tictac(rel_t *self);

// retorna a hora atual do sistema, em unidades de tempo
int rel_agora(rel_t *self);

// Funções para acessar o relógio como um dispositivo de E/S
//   só tem leitura, e dois dispositivos, '0' para ler o relógio local
//   (contador de instruções) e '1' para ler o relógio de tempo de CPU
//   consumido pelo simulador (em ms)
err_t rel_le(void *disp, int id, int *pvalor);
#endif // REL_H
