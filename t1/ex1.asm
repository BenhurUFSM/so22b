; programa de exemplo para SO
; imprime numeros entre 0 e 9
;
; um programa asm tem um comando por linha
; a partir do caractere ';' é comentário (ignorado pelo montador)
; um comando tem 3 partes:   [label][ instrução[ argumento]]
; essas partes são separadas por um ou mais espaços
; não pode ter espaço antes do label
; o argumento pode ser um número ou um label
; o valor de um label é definido quando ele aparece no início da linha,
; geralmente com o valor correspondente ao endereço onde a instrução dessa
; linha será colocada na memória. Com a pseudo-instrução DEFINE, pode-se
; definir um valor qualquer ara um label.
; o que está entre [] é opcional (ou depende da instrução)
; 'instrução' pode ser qualquer instrução do processador, ou uma das
; pseudo-instruções:
;     VALOR  x   -> coloca o valor x na prõxima posição de memõria
;     ESPACO x   -> coloca 'x' valores 0 nas próximas posições de memória
; lab DEFINE x   -> define o label 'lab' com o valor x e não com o end. atual

     CARGI 0
     MVAX         ; x=0
ali  MVXA
     ESCR 0       ; print x
     INCX         ; x++
     MVXA
     SUB cont
     DESVNZ ali   ; if x != cont goto ali
     PARA         ; stop
cont VALOR 10     ; int cont=10
