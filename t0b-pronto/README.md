## t0 - simulador de uma CPU

t0b-pronto

Adição de teste de pronto para dispositivos de E/S. 
Esses testes possibilitam a implementação de dispositivos que são mais lentos que a CPU.
Antes de se fazer uma operação de E/S, o programa deve agora consultar o dispositivo para saber se ele está apto a realizar essa operação.
A execução de E/S em um dispositivo não pronto resulta em erro de execução (ERR_OCUP).

Para isso, ao registrar um dispositivo, além dar funções de leitura e escrita deve-se também informar uma função que retorna um bool que diz se o dispositivo está pronto ou não para realizar uma operação de leitura ou escrita.

Quando se registra o dispositivo `n` no controlador de E/S, ele cria mais dois dispositivos de leitura:
- `n+100` - quando lido, retorna 1 se dispositivo `n` pode ser lido
- `n+200` - quando lido, retorna 1 se dispositivo `n` pode ser escrito

 

