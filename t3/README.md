## t3 — Memória Virtual

Implemente um sistema simples de paginação.

### Alterações na implementação em relação ao t1

Foram adicionados os seguintes arquivos:
- `mmu.h` e `mmu.c` — implementação da unidade de gerenciamento de memória. Tem uma API semelhante à da memória.
- `tab_pag.h` e `tab_tag.c` — implementa uma tabela de páginas; usada pela MMU para fazer a tradução de endereços lógicos em físicos. Deve existir uma dessas por processo, e a MMU deve receber a tabela correta a cada troca de processo.

Foram alterados:
- `err.h` — adição de dois erros relacionados à tradução de endereços
- `exec.h` e `exec.c` — acesso à memória via MMU, não mais de forma direta
- `contr.h` e `contr.c` — inicialização da MMU, alteração na inicialização de exec, API para permitir que o SO acesse a MMU.

Foi adicionado ainda o arquivo `a1.asm`, que preenche um vetor com números aleatórios e ordena os números.
Esse programa pode ser facilmente alterado para mudar entre um programa que usa bastante CPU e/ou E/S.
Alterando o valor de TELA, dá para fazer ele usar outro terminal.
Alterando a forma de obtenção dos números, dá para usar E/S em vez de CPU (trocando "`cargi 1000/chama aleat`" por uma chamada a uma função similar a `le_int` que lê do gerador de números de t0).
Comentando as chamadas a `imprime_vet`, dá para reduzir a E/S.
Comentando a chamada a `ordena_vet`, dá para reduzir a CPU.

Foi alterado também `so.c`, para executar `a1.maq` e `tela.c` para aumentar o tamanho das filas de E/S.

### Parte I

Altere a sua implementação de processos para manter todos os processos na memória ao mesmo tempo. 
A MMU será usada para proteção de memória e relocação, mas ainda não para memória virtual com uso de área de troca.

Defina a memória principal com tamanho suficiente para conter todos os processos que serão executados.
O tamanho das páginas (e dos quadros) não é especialmente importante, mas deve ser levado em consideração que uma página não pode ser usada por mais de um processo por vez.
Na criação de um processo, coloque todo o conteúdo dele em uma região livre da memória principal.
A alocação da memória principal deve ser feita em quadros.
Crie e inicialize uma tabela de páginas para o processo.
A página 0 do processo deve corresponder ao primeiro quadro usado para esse processo, a página 1 ao segundo etc.
Quando houver troca de processo, altere a tabela a ser usada pela MMU para a tabela do processo que irá executar, não altere a memória.

### Parte II

Foram alterados `mmu.h` e `mmu.c` para incluir a função `mmu_ultimo_endereco`, que o SO pode usar para obter o endereço que causou falha de página.

Implemente memória virtual com tratamento de faltas de página e paginação por demanda.
Reduza o tamanho da memória principal para ser bem menor que o necessário para conter todos os processos.
Por simplicidade, a memória secundária de cada processo vai ser mantida pelo SO na entrada do processo na tabela de processos. Essa memória é inicializada na criação do processo.

Na criação do processo, é criada a tabela de páginas do processo, com todas as páginas marcadas como inválidas, nenhuma delas é colocada na memória principal. As páginas serão colocadas em quadros da memória principal em resposta a interrupções de falta de página causadas pela execução do processo.

Você deve implementar 2 algoritmos de substituição de páginas, e realizar medições para comparar o desempenho do sistema em 4 configurações (cada algoritmo em uma situação folgada (metade da memória necessária) ou apertada (menos de 1/5 da memória)).

### Atualizações

23jan:
- corrigido um bug em tab_pag.c (tava invertido o teste de página válida).
- acrescentados 4 programas .asm (pequeno e grande, limitado por CPU e limitado por E/S), alterações de a1.asm.

24jan:
- mmu agora seta os bits de acessada e alterada na tabela de páginas; alterou um pouco a API da tab_pag
- correção nos programas .asm de ontem (tinha um bug, e tavam demorando demais)
