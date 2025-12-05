#ifndef IO_H
#define IO_H

#include "../Arvore_Binaria/arvore.h"
#include "../Fila_Prioridade/fila_prioridade.h"
#include <stdbool.h>

bool SAVE(ARVORE *arvore, FILA_PRIORIDADE *fila);
bool LOAD(ARVORE **arvore, FILA_PRIORIDADE **fila);

#endif
