; programa de exemplo para SO
; gera 10 números aleatórios em um vetor, ordena o vetor, imprime o primeiro e o último valores no vetor

; chamadas de sistema
SO_LE   define 1
SO_ESCR define 2
SO_FIM  define 3
; dispositivos de E/S
TELA    DEFINE 1
RANDOM  DEFINE 3  ; altere para o seu dispositivo de números aleatórios

TAMANHO DEFINE 10
TAM_1   DEFINE 9 ; um a menos que o tamanho

main
        cargi TAMANHO
        armm tam_vet
        chama enche_vet
        chama imprime_vet
        chama ordena_vet
        chama imprime_vet
        ; termina
        sisop SO_FIM

tam_vet espaco 1
vet     espaco TAMANHO

; le_int: lê um inteiro do teclado, retorna em A
le_int  espaco 1
le_de_novo
        cargi TELA
        sisop SO_LE       ; retorna A=err, X=dado
        desvnz le_de_novo ; se der erro, tenta de novo
        mvxa
        ret le_int

; enche_vet: preenche o vetor vet com tam_vet valores aleatórios
enche_vet espaco 1
        ; e_ind = 0
        cargi 0
        armm e_ind
e_laco
        ; e_tmp = número aleatório entre 0 e 999
        cargi 1000
        chama aleat
        armm e_tmp
        ; vet[e_ind] = e_tmp
        cargm e_ind
        mvax
        cargm e_tmp
        armx vet
        ; e_ind++ (e_ind tá no X)
        incx
        mvxa
        armm e_ind
        ; if e_ind < tam_vet goto e_laco
        sub tam_vet
        desvn e_laco
        ret enche_vet
e_ind   espaco 1
e_tmp   espaco 1

; imp_int: imprime o valor em A na TELA
imp_int espaco 1
        armm ii_tmp
ii_de_novo
        cargm ii_tmp
        mvax
        cargi TELA
        sisop SO_ESCR     ; impr X em A, retorna A=err
        desvnz ii_de_novo
        ret imp_int
ii_tmp  espaco 1

; imprime_vet  imprime os tam_vet valores de vet na TELA
imprime_vet espaco 1
        ; i_ind = 0
        cargi 0
        armm i_ind
i_laco
        ; imprime vet[e_ind]
        cargm i_ind
        mvax
        cargx vet
        chama imp_int
        ; i_ind++
        cargm i_ind
        soma um
        armm i_ind
        ; if i_ind < tam_vet goto i_laco
        sub tam_vet
        desvn i_laco
        ret imprime_vet
i_ind   espaco 1
um      valor TAM_1  ; mudar pra 1 pra imprimir o vetor inteiro

; retorna em A um número "aleatório" entre 0 e A-1
; usa o código exemplificado no manual do rand do linux
aleat   espaco 1
        armm a_mod
        cargm a_semente
        mult a_mult
        soma a_soma
        armm a_semente
        desvp a_pos    ; se semente < 0, usa -semente
        neg
a_pos   resto a_mod
        ret aleat

a_semente valor 1
a_mod   espaco 1
a_mult  valor 1103515245
a_soma  valor 12345

; ordena_vet: ordena os tam_vet valores em vet
; usa o algoritmo da bolha
ordena_vet espaco 1
o_laco_ext
        ; do {
        ;   o_ind = 1
        cargi 1
        armm o_ind
        ;   o_trocou=0
        cargi 0
        armm o_trocou
o_laco_int
        ;   while o_ind < tam_vet {
        cargm o_ind
        sub tam_vet
        desvz o_lacoi_fim
        desvp o_lacoi_fim
        ;     o_tmp = vet[o_ind]
        cargm o_ind
        mvax
        cargx vet
        armm o_tmp
        ;     if vet[o_ind-1] > o_tmp {
        ;decx   como assim não tem decx???
        mvxa
        sub um
        mvax
        cargx vet
        sub o_tmp
        desvz o_n_troca
        desvn o_n_troca
        ;       valores estão fora de ordem, troca um pelo outro
        ;       vet[o_ind] = vet[o_ind-1]
        ;       X tem o_ind-1
        cargx vet
        incx
        armx vet
        ;       vet[o_ind-1] = o_tmp
        ;decx
        mvxa
        sub um
        mvax
        cargm o_tmp
        armx vet
        ;       o_trocou = 1
        cargi 1
        armm o_trocou
        ;     }
o_n_troca
        ;     o_ind++
        cargm o_ind
        soma um
        armm o_ind
        ;   }
        desv o_laco_int
o_lacoi_fim
        ; } while trocou
        cargm o_trocou
        desvnz o_laco_ext
        ret ordena_vet
o_ind    espaco 1
o_tmp    espaco 1
o_trocou espaco 1
