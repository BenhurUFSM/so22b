; programa de exemplo para SO
; lê um número do terminal 1
; imprime numeros entre 0 e o número lido nos terminais 1 e 2
; testa somente o primeiro dispositivo para ver se está pronto,
;   mas escreve nos dois

TELA    DEFINE 0
TELA2   DEFINE 1
TELAPL  DEFINE 100
TELAPE  DEFINE 200
naole
        LE TELAPL    ; espera tela ficar disponível para leitura
        DESVZ naole
        LE TELA      ; lê cont
        ARMM cont
        CARGI 0      ; x=0
        MVAX
ali
esperatela
        LE TELAPE    ; espera tela ficar disponível para escrita
        DESVZ esperatela
        MVXA         ; print x
        ESCR TELA
        ESCR TELA2   ; print x na tela 2
        INCX         ; x++
        MVXA         ; if x != cont goto ali
        SUB cont
        DESVNZ ali
        PARA         ; stop
cont    VALOR 10     ; int cont=10
