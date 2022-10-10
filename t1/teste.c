#include "contr.h"

int main()
{
  contr_t *contr = contr_cria();
  contr_laco(contr);
  contr_destroi(contr);
  return 0;
}
