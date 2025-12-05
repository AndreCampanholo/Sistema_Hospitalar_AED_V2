#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "paciente.h"

struct paciente
{
   int id;
   char nome[100];
   int prioridade;
};

PACIENTE *paciente_criar(int id, const char *nome, int prioridade)
{
   PACIENTE *paciente = (PACIENTE *)malloc(sizeof(PACIENTE));
   if (paciente != NULL)
   {
      paciente->id = id;
      snprintf(paciente->nome, sizeof(paciente->nome), "%s", nome ? nome : "");
      paciente->prioridade = (prioridade >= 1 && prioridade <= 5) ? prioridade : NAO_URGENCIA;
      return paciente;
   }
   return NULL;
}

bool paciente_apagar(PACIENTE **paciente)
{
   if (paciente != NULL && *paciente != NULL)
   {
      free(*paciente);
      *paciente = NULL;
      return true;
   }
   return false;
}

void paciente_imprimir(PACIENTE *paciente)
{
   if (paciente != NULL)
   {
      const char *prio_str = paciente_descricao_prioridade(paciente->prioridade);
      printf("ID: %-10d | Nome: %-30s | Prioridade: %s\n", paciente->id, paciente->nome, prio_str);
   }
}

int paciente_get_id(PACIENTE *paciente)
{
   if (paciente != NULL)
      return (paciente->id);
   exit(1);
}

char *paciente_get_nome(PACIENTE *paciente)
{
   if (paciente != NULL)
      return (paciente->nome);
   return NULL;
}

int paciente_get_prioridade(PACIENTE *paciente)
{
   if (paciente != NULL)
      return paciente->prioridade;
   return -1;
}

bool paciente_set_id(PACIENTE *paciente, int id)
{
   if (paciente != NULL)
   {
      paciente->id = id;
      return (true);
   }
   return (false);
}

bool paciente_set_nome(PACIENTE *paciente, const char *nome)
{
   if (paciente != NULL && nome != NULL)
   {
      snprintf(paciente->nome, sizeof(paciente->nome), "%s", nome);
      return true;
   }
   return false;
}

bool paciente_set_prioridade(PACIENTE *paciente, int prioridade)
{
   if (paciente != NULL && prioridade >= 1 && prioridade <= 5)
   {
      paciente->prioridade = prioridade;
      return true;
   }
   return false;
}

const char *paciente_descricao_prioridade(int prioridade)
{
   switch (prioridade)
   {
   case EMERGENCIA:
      return "Emergência (Risco de morte)";
   case MUITO_URGENTE:
      return "Muito Urgente (Grave)";
   case URGENTE:
      return "Urgente (Moderado)";
   case POUCO_URGENTE:
      return "Pouco Urgente (Básica)";
   case NAO_URGENCIA:
      return "Não Urgência";
   default:
      return "Desconhecida";
   }
}