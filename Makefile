# Makefile para Pronto Socorro SUS - V2
CC = gcc
CFLAGS = -Wall -Wextra -std=c99

SOURCES = main.c \
          TAD_Paciente/paciente.c \
          Arvore_Binaria/arvore.c \
          Fila_Prioridade/fila_prioridade.c \
          TAD_functions/functions.c \
          TAD_IO/IO.c

OBJECTS = $(SOURCES:.c=.o)
EXECUTABLE = sistema

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^
	@echo "Compilação concluída! Execute com: ./$(EXECUTABLE)"

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

run: $(EXECUTABLE)
	./$(EXECUTABLE)

clean:
	rm -f $(OBJECTS) $(EXECUTABLE)
	@echo "Arquivos compilados removidos."

clean-all: clean
	rm -rf Persistencia_Dados/
	@echo "Limpeza completa realizada."

rebuild: clean all

.PHONY: all run clean clean-all rebuild
