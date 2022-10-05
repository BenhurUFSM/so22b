; programa de exemplo para SO
; lê N números, imprime-os na ordem inversa

N       DEFINE 5
teclado DEFINE 0
video   DEFINE 0
        CARGI 0      ; x=0
        MVAX
i_leit  MVXA         ; while x != cont
        SUB cont
        DESVZ f_leit
        LE teclado   ;   le vet[x]
        ARMX vet
        INCX         ;   x++
        DESV i_leit  ; fim while
f_leit
        CARGM cont   ; x=cont
        MVAX
i_escr  MVXA         ; while x > 0
        DESVP m_escr
        DESV f_escr
m_escr  CHAMA decx   ;   x--
        CARGX vet    ;   escreve vet[x]
        ESCR video
        DESV i_escr  ; fim while
f_escr
        PARA         ; stop

decx    ESPACO 1     ; subrotina para decrementar o X
        MVXA
        SUB um
        MVAX
        RET decx
um      VALOR 1

cont    VALOR N
vet     ESPACO N
