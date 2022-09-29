#include "exec.h"
#include "term.h"
#include "rel.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MEMORIA_HEAP 64

// funções auxiliares
mem_t *init_mem(void);
void imprime_estado(exec_t *exec);


int main()
{
  // cria o hardware
  // cria a memória
  mem_t *mem = init_mem();
  // cria dispositivos de E/S (o relógio e um terminal)
  term_t *term = term_cria();
  rel_t *rel = rel_cria();
  // cria o controlador de E/S e registra os dispositivos
  es_t *es = es_cria();
  es_registra_dispositivo(es, 0, term, 0, term_le, term_escr);
  es_registra_dispositivo(es, 1, rel, 0, rel_le, NULL);
  es_registra_dispositivo(es, 2, rel, 1, rel_le, NULL);
  // cria a unidade de execução e inicializa com a memória e E/S
  exec_t *exec = exec_cria(mem, es);
  
  // executa uma instrução por vez até CPU acusar erro
  err_t err;
  do {
    imprime_estado(exec);
    err = exec_executa_1(exec);
    rel_tictac(rel);
  } while (err == ERR_OK);
      
  printf("Fim da execução. Estado final:\n");
  imprime_estado(exec);
  
  // destroi todo mundo!
  exec_destroi(exec);
  es_destroi(es);
  term_destroi(term);
  rel_destroi(rel);
  mem_destroi(mem);
  return 0;
}


// cria memória e inicializa com o conteúdo do programa
mem_t *init_mem(void)
{
  // programa para executar na nossa CPU
  int progr[] = {
  #include "ex1.maq"
  };
  int tam_progr = sizeof(progr)/sizeof(progr[0]);
                
  // cria uma memória e inicializa com o programa 
  mem_t *mem = mem_cria(tam_progr,TAM_PILHA);
  for (int i = 0; i < tam_progr; i++) {
    if (mem_escreve(mem, i, progr[i]) != ERR_OK) {
      printf("Erro de memória, endereco %d\n", i);
      exit(1);
    }
  }
  return mem;
}

void imprime_estado(exec_t *exec)
{
  cpu_estado_t *estado = cpue_cria();
  exec_copia_estado(exec, estado);
  printf("PC=%04d A=%06d X=%06d E=%d.%d\n",
         cpue_PC(estado), cpue_A(estado), cpue_X(estado),
         cpue_erro(estado), cpue_complemento(estado));
  cpue_destroi(estado);
}

