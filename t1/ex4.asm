; programa de exemplo para SO
; imprime numeros entre 0 e 9
; agora com teste para ver se dispositivo está pronto
;

TELA   DEFINE 0
TELA2  DEFINE 1
TELAPL DEFINE 100
TELAPE DEFINE 200
       CARGI 0
       MVAX         ; x=0
ali
esperatela
       LE TELAPL
       DESVZ naole
       LE TELA
       MVAX
naole
       LE TELAPE
       DESVZ esperatela
       MVXA
       ESCR TELA    ; print x
       ESCR TELA2   ; print x
       INCX         ; x++
       MVXA
       SUB cont
       DESVNZ ali   ; if x != cont goto ali
       PARA         ; stop
cont   VALOR 10     ; int cont=10
