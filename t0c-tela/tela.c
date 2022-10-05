#include "tela.h"

#include <string.h>
#include <curses.h>  // tomara que eu não me arrependa!
#include <locale.h>
#include <stdarg.h>

// fila de números
#define FN_TAM 5  // quantos números cabem numa fila
typedef struct {
  int num[FN_TAM]; // os números
  int n;           // quantos números válidos tem
} fila_de_numeros;
void fn_zera(fila_de_numeros *f)
{
  f->n = 0;
}
int fn_n(fila_de_numeros *f)
{
  return f->n;
}
bool fn_cheia(fila_de_numeros *f)
{
  return fn_n(f) >= FN_TAM;
}
bool fn_vazia(fila_de_numeros *f)
{
  return fn_n(f) == 0;
}
void fn_ins(fila_de_numeros *f, int n)
{
  if (f->n < FN_TAM) f->num[f->n++] = n;
}
int fn_rem(fila_de_numeros *f)
{
  if (f->n <= 0) return 0;
  int r = f->num[--f->n];
  memmove(&(f->num[0]), &(f->num[1]), f->n * sizeof(int));
  return r;
}
int fn_num(fila_de_numeros *f, int n)
{
  return f->num[n];
}
// fim da fila de números


#define N_LIN 24  // número de linhas na tela
#define N_COL 80  // número de colunas na tela
#define N_TERM 8  // número de terminais, cada um ocupa 2 linhas na tela
#define N_LIN_CONS ((N_LIN)-1-(N_TERM)*2)  // número de linhas pra console

struct {
  fila_de_numeros entrada[N_TERM];
  fila_de_numeros saida[N_TERM];
  char txt_console[N_LIN_CONS][N_COL+1];
  char digitando[N_COL+1];
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

int t_printf(char *formato, ...)
{
  char s[sizeof(tela.txt_console)];
  va_list arg;
  va_start(arg, formato);
  int r = vsnprintf(s, sizeof(s), formato, arg);
  insere_strings_na_console(s);
  return r;
}

static void interpreta_entrada(void)
{
  int t = tela.digitando[0] - 'a';
  if (t >= 0 && t < N_TERM) {
    if (tela.digitando[1] == 'z') { // limpa a saída do terminal
      fn_zera(&tela.saida[t]);
    } else { // entra um número no terminal
      int n;
      if (sscanf(tela.digitando+1, "%d", &n) == 1) {
        if (!fn_cheia(&tela.entrada[t])) {
          fn_ins(&tela.entrada[t], n);
        }
      }
    }
  }
  t_printf(tela.digitando);
  tela.digitando[0] = '\0';
}

static void verifica_entrada(void)
{
  int ch = getch();
  if (ch == ERR) return;
  int l = strlen(tela.digitando);
  if ((ch == '\b' || ch == 0x7f) && l > 0) {   // backspace ou del
    tela.digitando[l-1] = '\0';
  } else if (ch == '\n') {
    interpreta_entrada();
  } else if (ch >= ' ' && ch < 127 && l < N_COL) {
    tela.digitando[l] = ch;
    tela.digitando[l+1] = '\0';
  } // senão, ignora o caractere digitado
  else {
    char s[10];
    sprintf(s, "[%x]", ch);
    strcat(tela.digitando, s);
  }
}

static void desenha_terminal(int t)
{
  mvprintw(t*2, 0, "%80s", "");
  mvprintw(t*2+1, 0, "%80s", "");
  for (int i=0; i<fn_n(&tela.saida[t]); i++) {
    if (i == FN_TAM-1) attron(COLOR_PAIR(5));
    mvprintw(t*2, i*8, "%d", fn_num(&tela.saida[t], i));
    if (i == FN_TAM-1) attroff(COLOR_PAIR(5));
  }
  for (int i=0; i<fn_n(&tela.entrada[t]); i++) {
    mvprintw(t*2+1, i*8, "%d", fn_num(&tela.entrada[t], i));
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

static void desenha_console(void)
{
  attron(COLOR_PAIR(3));
  for (int l=0; l<N_LIN_CONS; l++) {
    int y = 23 - N_LIN_CONS + l;
    mvprintw(y, 0, "%80s", "");
    mvprintw(y, 0, "%s", tela.txt_console[l]);
  }
  attroff(COLOR_PAIR(3));
}

static void desenha_entrada(void)
{
  attron(COLOR_PAIR(4));
  mvprintw(23, 0, "%79s", "");
  mvprintw(23, 0, "%s", tela.digitando);
  attroff(COLOR_PAIR(4));
}

void t_atualiza(void)
{
  verifica_entrada();

  // desenha a tela:
  //   duas linhas para cada terminal, 
  //   tantas linhas da console,
  //   uma linha de entrada
  //clear();
  desenha_terminais();
  desenha_console();
  desenha_entrada();

  // manda o curses fazer aparecer tudo isso
  refresh();
}

