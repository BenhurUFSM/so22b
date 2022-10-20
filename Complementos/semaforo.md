### Semáforo

Um semáforo é um mecanismo de sincronização entre processos.
Um semáforo tem um valor inteiro associado a ele, que é inicializado na criação do semáforo.
Tem duas operações básicas, ***down***, que decrementa o valor e ***up***, que o incrementa.
A operação down não decrementa se o valor do semáforo não for positivo, nesse caso, o processo executando o down é bloqueado.
A operação up não incrementa o valor do semáforo se houver algum processo bloqueado no semáforo; nesse caso um processo é desbloqueado.
A implementação de up e down tem que garantir que sua execução seja feita em exclusão mútua em relação a outras operações ne mesmo semáforo.
As operações fazem algo como:
```c
   down(sema s)
     executa em exclusão mútua com up e down em 's'
       se s.valor < 1
         bloqueia o processo corrente, e acrescenta o processo em s.fila
       senão
         s.valor--
     
   up(sema s)
     executa em exclusão mútua com up e down em 's'
       se s.fila não tá vazia
         retira processo da fila e desbloqueia
       senão
         s.valor++
```
