CC = gcc
CFLAGS = -Wall -Werror
LDLIBS = -lcurses

OBJS = exec.o cpu_estado.o es.o mem.o rel.o term.o instr.o err.o \
			 tela.o contr.o so.o teste.o
OBJS_MONT = instr.o err.o montador.o
MAQS = ex1.maq ex2.maq ex3.maq ex4.maq
TARGETS = teste montador

all: ${TARGETS}
# para gerar o montador, precisa de todos os .o do montador
montador: ${OBJS_MONT}

# para gerar o programa de teste, precisa de todos os .o)
teste: ${OBJS}

# para gerar contr.o, precisa, além do contr.c, dos arquivos .maq
contr.o: contr.c ${MAQS}

# para transformar um .asm em .maq, precisamos do montador
%.maq: %.asm montador
	./montador $*.asm > $*.maq

clean:
	rm ${OBJS} ${TARGETS} ${MAQS}
