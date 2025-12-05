#ifndef ITEM_H
#define ITEM_H

#include <stdbool.h>

typedef struct paciente PACIENTE;

// Prioridades
#define EMERGENCIA 5
#define MUITO_URGENTE 4
#define URGENTE 3
#define POUCO_URGENTE 2
#define NAO_URGENCIA 1

PACIENTE *paciente_criar(int id, const char *nome, int prioridade);
bool paciente_apagar(PACIENTE **paciente);
void paciente_imprimir(PACIENTE *paciente);
int paciente_get_id(PACIENTE *paciente);
char *paciente_get_nome(PACIENTE *paciente);
int paciente_get_prioridade(PACIENTE *paciente);
bool paciente_set_id(PACIENTE *paciente, int id);
bool paciente_set_nome(PACIENTE *paciente, const char *nome);
bool paciente_set_prioridade(PACIENTE *paciente, int prioridade);
const char *paciente_descricao_prioridade(int prioridade);

#endif
