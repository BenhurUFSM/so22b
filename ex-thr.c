#include <stdio.h>
#include <pthread.h>

#define Nrep 5000
#define Nthr 2

volatile int x;

void *f(void *a)
{
  for (int i=0; i<Nrep; i++) x++;
}

int main()
{
  pthread_t v[Nthr];
  for (int t=0; t<Nthr; t++) {
    pthread_create(&v[t], NULL, f, NULL);
  }
  for (int t=0; t<Nthr; t++) {
    pthread_join(v[t], NULL);
  }
  printf("%d/%d\n", x, Nrep*Nthr);
}
