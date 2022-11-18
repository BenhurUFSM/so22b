#include "tela.h"

#include <string.h>
#include <curses.h>  // tomara que eu não me arrependa!
#include <locale.h>
#include <stdarg.h>
#include <ctype.h>

// fila de números
#define FN_TAM 9  // quantos números cabem numa fila
typedef struct {
  int num[FN_TAM]; // os números
  int n;           // quantos números válidos tem
} fila_de_numeros;
void fn_zera(fila_de_numeros *f)  // esvazia a fila
{
  f->n = 0;
}
int fn_n(fila_de_numeros *f)      // retorna o número de elementor na fila
{
  return f->n;
}
bool fn_cheia(fila_de_numeros *f) // retorna true se a fila estiver cheia
{
  return fn_n(f) >= FN_TAM;
}
bool fn_vazia(fila_de_numeros *f) // retorna true se a fila estiver vazia
{
  return fn_n(f) == 0;
}
void fn_ins(fila_de_numeros *f, int n) // insere n na fila f
{
  if (f->n < FN_TAM) f->num[f->n++] = n;
}
int fn_rem(fila_de_numeros *f)    // remove (e retorna) o próximo da fila
{
  if (f->n <= 0) return 0;
  int r = f->num[--f->n];
  memmove(&(f->num[0]), &(f->num[1]), f->n * sizeof(int));
  return r;
}
int fn_num(fila_de_numeros *f, int n) // retorna o n-ésimo da fila
{
  return f->num[n];
}
// fim da fila de números


#define N_LIN_CONS ((N_LIN)-2-(N_TERM)*2)  // número de linhas pra console

typedef enum {
  nao_sai_da_console,
  deixa_executar_1,
  executa_direto,
} modo_da_console_t;

struct {
  fila_de_numeros entrada[N_TERM];        // uma fila de entrada por terminal
  fila_de_numeros saida[N_TERM];          // uma fila de saída por terminal
  char txt_status[N_COL+1];               // texto da linha de status
  char txt_console[N_LIN_CONS][N_COL+1];  // texto das linhas da console
  char digitando[N_COL+1];                // texto da linha sendo digitada
  modo_da_console_t modo;                 // modo de operação
} tela;

void t_inicio(void)
{
  // inicializa a tela
  for (int t=0; t<N_TERM; t++) {
    fn_zera(&tela.entrada[t]);
    fn_zera(&tela.saida[t]);
  }
  for (int l=0; l<N_LIN_CONS; l++) {
    tela.txt_console[l][0] = '\0';
  }
  tela.digitando[0] = '\0';

  // inicializa o curses
  setlocale(LC_ALL, "");  // para ter suporte a UTF8
  initscr();
  cbreak();      // lê cada char, não espera enter
  noecho();      // não mostra o que é digitado
  timeout(10);  // não espera digitar, retorna ERR se nada foi digitado
  start_color();
  init_pair(1, COLOR_GREEN, COLOR_BLACK);
  init_pair(2, COLOR_YELLOW, COLOR_BLACK);
  init_pair(3, COLOR_BLUE, COLOR_BLACK);
  init_pair(4, COLOR_GREEN, COLOR_BLACK);
  init_pair(5, COLOR_BLACK, COLOR_RED);
}

void t_fim(void)
{
  t_atualiza();
  attron(COLOR_PAIR(5));
  addstr("  digite ENTER para sair  ");
  while (getch() != '\n') {
    ;
  }
  // acaba com o curses
  endwin();
}

bool t_livre(int t)
{
  return !fn_cheia(&tela.saida[t]);
}

void t_print(int t, int n)
{
  fn_ins(&tela.saida[t], n);
}

bool t_tem(int t)
{
  return !fn_vazia(&tela.entrada[t]);
}

int t_le(int t)
{
  return fn_rem(&tela.entrada[t]);
}

void t_ins(int t, int n)
{
  fn_ins(&tela.entrada[t], n);
}

static void insere_string_na_console(char *s)
{
  for(int l=0; l<N_LIN_CONS-1; l++) {
    strncpy(tela.txt_console[l], tela.txt_console[l+1], N_COL);
    tela.txt_console[l][N_COL] = '\0'; // quem definiu strncpy é estúpido!
  }
  strncpy(tela.txt_console[N_LIN_CONS-1], s, N_COL);
  tela.txt_console[N_LIN_CONS-1][N_COL] = '\0'; // grrrr
}

static void insere_strings_na_console(char *s)
{
  while (*s != '\0') {
    char *f = strchr(s, '\n');
    if (f != NULL) {
      *f = '\0';
    }
    insere_string_na_console(s);
    if (f == NULL) break;
    s = f+1;
  }
}

void t_status(char *txt)
{
  // imprime alinhado a esquerda ("-"), max N_COL chars ("*")
  sprintf(tela.txt_status, "%-*s", N_COL, txt);
}

int t_printf(char *formato, ...)
{
  // esta função usa número variável de argumentos. Dá uma olhada em:
  // https://www.geeksforgeeks.org/variadic-functions-in-c/
  char s[sizeof(tela.txt_console)];
  va_list arg;
  va_start(arg, formato);
  int r = vsnprintf(s, sizeof(s), formato, arg);
  insere_strings_na_console(s);
  return r;
}

// retorna o terminal correspondente ao caractere dado, ou -1
static int term(char c)
{
  int t = tolower(c) - 'a';
  if (t >= 0 && t < N_TERM) return t;
  return -1;
}

static void interpreta_entrada(void)
{
  // Comandos aceitos (mudou em relação a t0c!):
  // etn entra o número n no terminal t  ex: eb30
  // lt  lê um número do terminal t (retira da saída)  ex: lc
  // zt  esvazia a saída do terminal t  ex: za
  // p   para a execução
  // s   executa uma instrução
  // c   continua a execução
  char *err = "OK";
  int t, n;
  switch (tolower(tela.digitando[0])) {
    case 'e':
      if ((t = term(tela.digitando[1])) == -1) {
        err = "terminal inválido";
      } else if (sscanf(tela.digitando+2, "%d", &n) != 1) {
        err = "esperava número";
      } else if (fn_cheia(&tela.entrada[t])) {
        err = "fila cheia";
      } else {
        fn_ins(&tela.entrada[t], n);
      }
      break;
    case 'l':
      if ((t = term(tela.digitando[1])) == -1) {
        err = "terminal inválido";
      } else if (fn_vazia(&tela.saida[t])) {
        err = "fila vazia";
      } else {
        fn_rem(&tela.saida[t]);
      }
      break;
    case 'z':
      if ((t = term(tela.digitando[1])) == -1) {
        err = "terminal inválido";
      } else {
        fn_zera(&tela.saida[t]);
      }
      break;
    case 'p':
      tela.modo = nao_sai_da_console;
      break;
    case 's':
      tela.modo = deixa_executar_1;
      break;
    case 'c':
      tela.modo = executa_direto;
      break;
    default:
      err = "não reconhecido";
  }
  t_printf("%s [%s]", tela.digitando, err);
  tela.digitando[0] = '\0';
}

// vê se tem algum caractere digitado no teclado
//   adiciona à linha sendo digitada ou remove se for backspace ou
//   interpreta a linha se for enter
static void verifica_entrada(void)
{
  int ch = getch();
  if (ch == ERR) return;
  int l = strlen(tela.digitando);
  if ((ch == '\b' || ch == 0x7f)) {   // backspace ou del
    if (l > 0) {
      tela.digitando[l-1] = '\0';
    }
  } else if (ch == '\n') {
    interpreta_entrada();
  } else if (ch >= ' ' && ch < 127 && l < N_COL) {
    tela.digitando[l] = ch;
    tela.digitando[l+1] = '\0';
  } // senão, ignora o caractere digitado
}

static void desenha_terminal(int t)
{
  mvprintw(t*2, 0, "S%c%*s", t+'a', N_COL, "");
  mvprintw(t*2+1, 0, "E%c%*s", t+'a', N_COL, "");
  for (int i=0; i<fn_n(&tela.saida[t]); i++) {
    if (i == FN_TAM-1) attron(COLOR_PAIR(5));
    mvprintw(t*2, i*8+2, "%8d", fn_num(&tela.saida[t], i));
    if (i == FN_TAM-1) attroff(COLOR_PAIR(5));
  }
  for (int i=0; i<fn_n(&tela.entrada[t]); i++) {
    mvprintw(t*2+1, i*8+2, "%8d", fn_num(&tela.entrada[t], i));
  }
}

static void desenha_terminais(void)
{
  for (int t=0; t<N_TERM; t++) {
    attron(COLOR_PAIR(1+t%2));
    desenha_terminal(t);
    attroff(COLOR_PAIR(1+t%2));
  }
}

static void desenha_status(void)
{
  attron(COLOR_PAIR(4));
  mvprintw(N_TERM*2, 0, "%-*s", N_COL, tela.txt_status);
  attroff(COLOR_PAIR(4));
}

static void desenha_console(void)
{
  attron(COLOR_PAIR(3));
  for (int l=0; l<N_LIN_CONS; l++) {
    int y = 23 - N_LIN_CONS + l;
    mvprintw(y, 0, "%-*s", N_COL, tela.txt_console[l]);
  }
  attroff(COLOR_PAIR(3));
}

static void desenha_entrada(void)
{
  attron(COLOR_PAIR(4));
  mvprintw(23, 0, "%*s", N_COL, 
           "P=para C=continua S=passo Lt=lê Zt=zera Etn=entra");
  mvprintw(23, 0, "%s", tela.digitando);
  attroff(COLOR_PAIR(4));
}

void t_atualiza(void)
{
  if (tela.modo == deixa_executar_1) tela.modo = nao_sai_da_console;
  do {
    verifica_entrada();

    // desenha a tela
    desenha_terminais();
    desenha_status();
    desenha_console();
    desenha_entrada();

    // manda o curses fazer aparecer tudo isso
    refresh();
  } while (tela.modo == nao_sai_da_console);
}

