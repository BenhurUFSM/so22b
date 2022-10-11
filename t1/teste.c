#include "contr.h"
#include "so.h"

int main()
{
  contr_t *contr = contr_cria();
  so_t *so = so_cria(contr);
  contr_informa_so(contr, so);
  contr_laco(contr);
  contr_destroi(contr);
  return 0;
}
