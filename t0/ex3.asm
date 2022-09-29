     CARGI 15
     MVAX
     PUSHX
     CARGI 128
loop PUSHA
     RESTO dez
     ESCR 0
     POPA
     DIV dez
     CMPA zero
     DESVE fim
     DESV loop
fim  POPA
     ESCR 0
     PARA         ; stop

dez  VALOR 10
zero VALOR 0
