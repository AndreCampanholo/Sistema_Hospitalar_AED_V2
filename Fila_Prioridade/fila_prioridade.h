#ifndef FILA_PRIORIDADE_H
#define FILA_PRIORIDADE_H

#include "../TAD_Paciente/paciente.h"
#include <stdbool.h>
#include <time.h>

typedef struct fila_prioridade_ FILA_PRIORIDADE;

// Prioridades: 5 = Emergência, 4 = Muito Urgente, 3 = Urgente, 2 = Pouco Urgente, 1 = Não Urgência
#define EMERGENCIA 5
#define MUITO_URGENTE 4
#define URGENTE 3
#define POUCO_URGENTE 2
#define NAO_URGENCIA 1

// Operações básicas
FILA_PRIORIDADE *fila_prioridade_criar(int capacidade_maxima);
bool fila_prioridade_apagar(FILA_PRIORIDADE **fila);
bool fila_prioridade_inserir(FILA_PRIORIDADE *fila, PACIENTE *paciente, int prioridade);
PACIENTE *fila_prioridade_remover(FILA_PRIORIDADE *fila, int *prioridade_saida);
PACIENTE *fila_prioridade_primeiro(FILA_PRIORIDADE *fila);

// Consultas
int fila_prioridade_tamanho(FILA_PRIORIDADE *fila);
bool fila_prioridade_vazia(FILA_PRIORIDADE *fila);
bool fila_prioridade_cheia(FILA_PRIORIDADE *fila);
void fila_prioridade_imprimir(FILA_PRIORIDADE *fila);

// Limpeza
void fila_prioridade_esvaziar(FILA_PRIORIDADE *fila);

// Busca de paciente na fila
PACIENTE *fila_prioridade_buscar_paciente(FILA_PRIORIDADE *fila, int id_paciente);

#endif
