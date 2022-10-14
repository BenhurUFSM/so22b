; programa de exemplo para SO
; lê um número do terminal 1
; imprime numeros entre 1 e o número lido nos terminais 1 e 2
; agora com chamadas ao SO

; chamadas de sistema
SO_LE   define 1
SO_ESCR define 2
SO_FIM  define 3
; dispositivos de E/S
TELA    DEFINE 0
TELA2   DEFINE 1

naole
        ; lê cont
        cargi TELA
        sisop SO_LE       ; retorna A=err, X=dado
        desvnz naole      ; se der erro, tenta de novo
        mvxa
        armm cont
ali
        ; print xis
        cargm xis
        mvax
denovo  cargi TELA
        sisop SO_ESCR     ; impr X em A, retorna A=err
        desvnz denovo     ; se der erro, tenta de novo
        ; print xis na tela 2
denovo2 cargi TELA2
        sisop SO_ESCR
        desvnz denovo2
        ; xis++   (xis ainda tá em X)
        incx
        mvxa
        armm xis
        ; if xis <= cont goto ali
        sub cont
        desvn ali
        desvz ali
        ; termina
        sisop SO_FIM
cont    espaco 1     ; int cont
xis     valor 1      ; int xis=1
