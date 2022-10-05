#ifndef EXEC_H
#define EXEC_H

// simulador do executor de instruções de uma CPU
// executa a instrução no PC se possível, ou retorna erro

// tem acesso a
// - controlador de ES para as instruções de ES
// - memória, onde está o programa e os dados -- alterável pelas instruções
// - estado da CPU, onde estão os registradores -- alterável pelas instruções

#include "err.h"
#include "mem.h"
#include "es.h"
#include "cpu_estado.h"

typedef struct exec_t exec_t; // tipo opaco


// cria uma unidade de execução com acesso à memória e ao
//   controlador de E/S fornecidos
exec_t *exec_cria(mem_t *mem, es_t *es);
// destrói a CPU
void exec_destroi(exec_t *self);

// copia o estado interno da CPU para o local apontado por 'estado'
void exec_copia_estado(exec_t *exec, cpu_estado_t *estado);
// altera o estado interno da CPU com o apontado por 'estado'
void exec_altera_estado(exec_t *exec, cpu_estado_t *estado);

// executa uma instrução
err_t exec_executa_1(exec_t *exec);

#endif // EXEC_H
