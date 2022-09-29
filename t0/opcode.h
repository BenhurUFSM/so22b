#ifndef OPCODE_H
#define OPCODE_H

    typedef enum {
        // pseudo-instruções
        DEFINE = -1,
        VALOR  = -2,
        ESPACO = -3,
        


        NOP    =  0, // 1 não faz nada
        PARA   =  1, // 1 para a CPU           modo=ERR_CPU_PARADA
        CARGI  =  2, // 2 carrega imediato     A=A1
        CARGM  =  3, // 2 carrega da memória   A=mem[A1]
        CARGX  =  4, // 2 carrega indexado     A=mem[A1+X]
        ARMM   =  5, // 2 armazena na memória  mem[A1]=A
        ARMX   =  6, // 2 armazena indexado    mem[A1+X]=A
        MVAX   =  7, // 1 copia A para X       X=A
        MVXA   =  8, // 1 copia X para A       A=X
        INCX   =  9, // 1 incrementa X         X++
        SOMA   = 10, // 2 soma                 A+=mem[A1]
        SUB    = 11, // 2 subtrai              A-=mem[A1]
        MULT   = 12, // 2 multiplica           A*=mem[A1]
        DIV    = 13, // 2 divide               A/=mem[A1]
        RESTO  = 14, // 2 calcula o resto      A%=mem[A1]
        NEG    = 15, // 1 inverte o sinal      A=-A
        DESV   = 16, // 2 desvio               PC=A1
        DESVZ  = 17, // 2 desvio condicional   se A for 0, PC=A1
        DESVNZ = 18, // 2 desvio condicional   se A não for 0, PC=A1
        LE     = 19, // 2 leitura de E/S       A=es[A1]
        ESCR   = 20, // 2 escrita de E/S       es[A1]=A
        
        CMPA   = 21,
        DESVA  = 22,
        DESVB  = 23,
        DESVE  = 24,
    } opcode_t;
#endif
