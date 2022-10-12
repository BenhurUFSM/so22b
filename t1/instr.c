#include <stddef.h>
#include <string.h>

#include "instr.h"

struct {
  char *nome;
  int num_args;
  opcode_t opcode;
} instrucoes[] = {
  { "NOP",    0,  NOP    },
  { "PARA",   0,  PARA   },
  { "CARGI",  1,  CARGI  },
  { "CARGM",  1,  CARGM  },
  { "CARGX",  1,  CARGX  },
  { "ARMM",   1,  ARMM   },
  { "ARMX",   1,  ARMX   },
  { "MVAX",   0,  MVAX   },
  { "MVXA",   0,  MVXA   },
  { "INCX",   0,  INCX   },
  { "SOMA",   1,  SOMA   },
  { "SUB",    1,  SUB    },
  { "MULT",   1,  MULT   },
  { "DIV",    1,  DIV    },
  { "RESTO",  1,  RESTO  },
  { "NEG",    0,  NEG    },
  { "DESV",   1,  DESV   },
  { "DESVZ",  1,  DESVZ  },
  { "DESVNZ", 1,  DESVNZ },
  { "DESVN",  1,  DESVN  },
  { "DESVP",  1,  DESVP  },
  { "CHAMA",  1,  CHAMA  },
  { "RET",    1,  RET    },
  { "LE",     1,  LE     },
  { "ESCR",   1,  ESCR   },
  { "SISOP",  1,  SISOP  },
  // pseudo-instrucoes
  { "VALOR",  1,  VALOR  },
  { "ESPACO", 1,  ESPACO },
  { "DEFINE", 1,  DEFINE },
};

opcode_t instr_opcode(char *nome)
{
  if (nome == NULL) return -1;
  for (int i=0; i<N_OPCODE; i++) {
    if (strcasecmp(instrucoes[i].nome, nome) == 0) {
      return instrucoes[i].opcode;
    }
  }
  return -1;
}

char *instr_nome(int opcode)
{
  for (int i=0; i<N_OPCODE; i++) {
    if (instrucoes[i].opcode == opcode) {
      return instrucoes[i].nome;
    }
  }
  return NULL;
}

int instr_num_args(int opcode)
{
  for (int i=0; i<N_OPCODE; i++) {
    if (instrucoes[i].opcode == opcode) {
      return instrucoes[i].num_args;
    }
  }
  return -1;
}

