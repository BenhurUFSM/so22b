CC = gcc
CFLAGS = -Wall -Werror

OBJS = exec.o cpu_estado.o es.o mem.o rel.o term.o teste.o
MAQS = ex1.maq ex2.maq ex3.maq
TARGETS = teste montador

all: ${TARGETS}

# para gerar o programa de teste, precisa de todos os .o)
teste: ${OBJS}

# para gerar teste.o, precisa, além do teste.c, dos arquivos .maq
teste.o: teste.c ${MAQS}

# para transformar um .asm em .maq, precisamos do montador
%.maq: %.asm montador
	./montador $*.asm > $*.maq

clean:
	rm ${OBJS} ${TARGETS} ${MAQS}
