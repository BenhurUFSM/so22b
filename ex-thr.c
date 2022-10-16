// programa para exemplificar uma condição de corrida usando threads
//
// o programa cria Nthr threads, cada uma delas incrementa a variável global "x" Nrep vezes.
// 
// altere os valores de Nrep e Nthr para ver discrepâncias no número de incrementos registrados.
// execute várias vezes com cada configuração para ver se muda.
// o programa usa a biblioteca pthreads; dependendo do compilador, talvez tenha que compilar com "-lpthread"

#include <stdio.h>
#include <pthread.h>

#define Nrep 5000
#define Nthr 2

// a variável global que será incrementada
// é declarada volátil para impedir que o compilador otimize os acessos à variável e
//   transforme o laço em x+=Nrep (experimente compilar com -O3 com e sem volatile
//   com Nrep grande)
volatile int x;

// A função executada pelas threads
// pthreads exige que receba e retorne void *
void *f(void *a)
{
  for (int i=0; i<Nrep; i++) x++;
  return NULL;
}

int main()
{
  // descritores das threads
  pthread_t v[Nthr];
  // cria as threads (o primeiro NULL diz para usar parâmetros default,
  //   o segundo é o argumento passado para f)
  for (int t=0; t<Nthr; t++) {
    pthread_create(&v[t], NULL, f, NULL);
  }
  // espera as threads terminarem. o NULL é para ignorar o valor de retorno
  for (int t=0; t<Nthr; t++) {
    pthread_join(v[t], NULL);
  }
  // imprime o valor final de x, e quanto deveria ser
  printf("%d/%d\n", x, Nrep*Nthr);
}
