; programa de exemplo para SO
; imprime numeros entre 0 e 9, mais o que ler dos dispositivos 1 e 2
;   (no programa de teste, esses dispositivos são conectados ao relógio,
;   o 1 obtém o contador de instruções, o 2 o tempo externo de CPU)

N    DEFINE 4
     CARGI 0
     MVAX         ; x=0
     CARGI N
     ARMM cont    ; cont=4
ali  MVXA
     ESCR 0       ; print x
     LE 1
     ESCR 0
     LE 2
     ESCR 0
     INCX         ; x++
     MVXA
     CMPA cont  ; faz cmp A,[A1]
     DESVE ali   ; if A = [cont] goto ali
     DESVB ali   ; if A < [cont] goto ali
     PARA         ; stop
cont ESPACO 1
