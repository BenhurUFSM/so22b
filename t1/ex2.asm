; programa de exemplo para SO
; imprime numeros entre 0 e 9, mais o que ler dos dispositivos 1 e 2
;   (no programa de teste, esses dispositivos são conectados ao relógio,
;   o 1 obtém o contador de instruções, o 2 o tempo externo de CPU)

N    DEFINE 10
     CARGI 0
     MVAX         ; x=0
     CARGI N
     ARMM cont    ; cont=10
ali  MVXA
     ESCR 0       ; print x
     LE 1
     ESCR 0
     LE 2
     ESCR 0
     INCX         ; x++
     MVXA
     SUB cont
     DESVNZ ali   ; if x != cont goto ali
     PARA         ; stop
cont ESPACO 1
