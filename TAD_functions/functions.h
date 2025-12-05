
#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "../Arvore_Binaria/arvore.h"
#include "../Fila_Prioridade/fila_prioridade.h"

void imprimir_escolha_operacao(void);
void registrar_paciente(ARVORE *arvore, FILA_PRIORIDADE *fila);
void remover_paciente(ARVORE *arvore, FILA_PRIORIDADE *fila);
void listar_pacientes(ARVORE *arvore);
void buscar_paciente_por_id(ARVORE *arvore);
void mostrar_fila_espera(FILA_PRIORIDADE *fila);
void dar_alta_paciente(FILA_PRIORIDADE *fila);
void salvar_sistema(ARVORE *arvore, FILA_PRIORIDADE *fila);
bool carregar_sistema(ARVORE **arvore, FILA_PRIORIDADE **fila);

#endif
