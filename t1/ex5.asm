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
        cargi TELA   ; lê cont
        sisop SO_LE
        armm cont
ali
        cargm xis    ; print xis
        mvax
        cargi TELA
        sisop SO_ESCR
        cargi TELA2  ; print xis na tela 2
        sisop SO_ESCR
        incx         ; xis++   (o xis ainda tá em X)
        mvxa
        armm xis
        sub cont     ; if xis <= cont goto ali
        desvn ali
        desvz ali
        sisop SO_FIM ; stop
cont    espaco 1     ; int cont
xis     valor 1      ; int xis=1
