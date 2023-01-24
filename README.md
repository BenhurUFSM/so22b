# so22b
Página da disciplina de Sistemas Operacionais, segundo semestre de 2022

ELC1080, DLSC/CT/UFSM
turmas CC e SI

professor: Benhur Stein ([benhur+so22b@inf.ufsm.br](mailto:benhur%2bso22b@inf.ufsm.br))\
terças e quintas, 10h30, sala 262

## Desenvolvimento da disciplina

Os canais de comunicação entre o professor e os alunos são 
os encontros em sala de aula,
encontros agendados com o professor (por e-mail),
esta página (<https://github.com/BenhurUFSM/so22b>)
e e-mail para [benhur+so22b@inf.ufsm.br](mailto:benhur%2bso22b@inf.ufsm.br).

O e-mail pode ser usado para o envio de perguntas, exercícios, reclamações, sugestões, críticas e o que mais for, durante todo o período em que durar a disciplina.

Esta página concentrará os assuntos vistos em aula, a descrição de exercícios e trabalhos, avaliações, etc. Ela estará sendo aumentada/atualizada durante todo o semestre. Ela é o canal mais oficial de informações sobre a disciplina.

Vou seguir de forma bastante próxima o assunto como ele é visto no livro

```
   Sistemas Operacionais Modernos
   Andrew S Tanenbaum
```

## Avaliação

Breve

## Aulas 

|    N |   data | assunto
| ---: | :----: | :--------
|    1 |  13set | introdução (descrição do [simulador](t0), seção 1.1 do livro)
|    2 |  15set | introdução (seção 1.2–1.2.3 do livro)
|      |  20set | feriado
|    3 |  22set | introdução (1.2.3–1.3.1)
|    4 |  27set | introdução (-1.5.1)
|    5 |  29set | introdução (1.5.2-5, 1.6-1.6.4, 1.7)
|    6 |   4out | processos (2-2.1.6)
|    7 |   6out | processos (2.1.7, 2.4-2.4.1)
|    8 |  11out | processos (2.4.2-4, escalonamento de proc. t. real (cap7 ed3))
|    9 |  13out | threads (2.2) [exemplo](ex-thr.c)
|   10 |  18out | comunicação entre processos (2.3-2.3.3)
|   11 |  20out | comunicação entre processos (2.3.3-2.3.7) (o que é um [semáforo](Complementos/semaforo.md))
|   12 |  25out | comunicação entre processos (2.5)
|   13 |  27out | comunicação entre processos (2.5)
|   14 |   1nov | gerenciamento de memória (3-3.2)
|   15 |   3nov | gerenciamento de memória (3.3-3.3.2,3.4-3.4.7)
|      |   8nov | JAI
|      |  10nov | JAI
|      |  15nov | feriado
|      |  17nov | SAINF
|   16 |  22nov | ger. memória
|   17 |  24nov | ger. memória
|   18 |  29nov | e/s
|   19 |   1dez | e/s
|   20 |   6dez | e/s
|      |   8dez | feriado
|      |  13dez | não tem aula
|      |  15dez | não tem aula
|      |  20dez | recesso
|      |  22dez | recesso
|      |  27dez | recesso
|      |  29dez | recesso
|   21 |   3jan | sist. arquivos
|   22 |   5jan | sist. arquivos
|   23 |  10jan | sist. arquivos
|   24 |  12jan | sist. arquivos
|   25 |  17jan | deadlocks
|   26 |  19jan | deadlocks
|   27 |  24jan |
|   28 |  26jan |
|   29 |  31jan |
|   30 |   2fev |
|      | 7ou9fev | exame

## Trabalhos, provas, exercícios

|    id |      prazo | assunto
| ----: | ---------: | :-----------
|    T0 |            | [simulador de CPU](t0)
|    E1 |      28set | simulador de dispositivo de leitura de números aleatórios
|    E2 |            | altere o E1 para ficar ocupado durante 10 instruções após cada leitura
|    T1 |            | [implementação de processos](t1)
|    T2 |            | [implementação de escalonador](t2)
|    T3 |            | [implementação de paginação](t3)
| final |      27jan | entrega final
|       | 31jan,2fev | entrevistas

Entrega do E1: junte os arquivos em um tar ou zip, envie por mail para benhur+so22b@inf.ufsm.br com assunto "SO-E1".

#### Entrega final

Envie um mail com:
- versão final dos trabalhos implementados (com relatório de execução)
- texto com a nota de auto-avaliação, com justificativa

A nota deve medir duas coisas, mais ou menos com mesmo peso: os trabalhos (foi feito o que foi pedido? funciona? serviu para aprender os conceitos relacionados?) e a aprendizagem do conteúdo da disciplina (coloquei 20 conceitos abaixo, dá pra pensar neles +- com o mesmo peso).

Os principais conceitos da disciplina são (veja ementa):
- gerência de processos (programa x processo; modo supervisor + usuário; interrupções; quando o estado de um processo é trocado; exemplos de escalonador em cada classificação de SO)
- comunicação entre processos/threads (condição de corrida; região crítica; exclusão mútua; mecanismos de sincronização)
- gerência de memória (proteção + relocação; memória virtual; algoritmos de substituição de páginas)
- gerência de E/S (dispositivo + controladores; formas de comunicação; camadas de sw de e/s)
- sistemas de arquivos (arquivos + diretórios; principais idéias de implementação)
- deadlocks (recursos; condições para um deadlock; estratégias para lidar com deadlocks)

Depois de receber o mail, envio uma resposta para marcar horário da conversa, que vai ser na minha sala (sala 376, 3o andar do anexo B).

Em caso de desespero, dá para enviar até segunda de manhã.

## Ementa

Ver [aqui](https://www.ufsm.br/ementario/disciplinas/ELC1080/).

