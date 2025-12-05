#ifndef ARVORE_H
#define ARVORE_H

#include "../TAD_Paciente/paciente.h"
#include <stdbool.h>

typedef struct arvore_ ARVORE;

// Operações básicas
ARVORE *arvore_criar(void);
bool arvore_apagar(ARVORE **arvore);
bool arvore_inserir(ARVORE *arvore, PACIENTE *paciente);
PACIENTE *arvore_remover(ARVORE *arvore, int id);
PACIENTE *arvore_buscar(ARVORE *arvore, int id);

// Consultas
int arvore_tamanho(ARVORE *arvore);
bool arvore_vazia(ARVORE *arvore);
void arvore_imprimir_inordem(ARVORE *arvore);
void arvore_imprimir_preordem(ARVORE *arvore);

// Iteração
void *arvore_primeiro_no(ARVORE *arvore);
void *arvore_proximo_no(void *no);
PACIENTE *arvore_no_paciente(void *no);

// Limpeza
void arvore_esvaziar(ARVORE *arvore);

#endif
