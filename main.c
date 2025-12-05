

#include <stdio.h>
#include <stdlib.h>
#include "Arvore_Binaria/arvore.h"
#include "Fila_Prioridade/fila_prioridade.h"
#include "TAD_functions/functions.h"
#include "TAD_IO/IO.h"

int main()
{
    ARVORE *arvore = arvore_criar();           // Árvore de pacientes registrados
    FILA_PRIORIDADE *fila = fila_prioridade_criar(1000); // Fila de espera com prioridades

    // Carrega dados salvos
    if (!carregar_sistema(&arvore, &fila))
    {
        printf("[Aviso] Não foi possível carregar dados anteriores. Iniciando sistema limpo.\n\n");
    }
    else
    {
        printf("[Sucesso] Dados carregados com sucesso.\n\n");
    }

    printf("========================================\n");
    printf("  PRONTO SOCORRO SUS - SISTEMA V2\n");
    printf("========================================\n\n");

    int operacao;

    // Laço principal de operações
    do
    {
        imprimir_escolha_operacao();
        printf("Escolha: ");
        
        if (scanf("%d", &operacao) != 1)
        {
            printf("Entrada inválida.\n");
            while (getchar() != '\n'); // Limpa buffer
            continue;
        }
        printf("\n");

        switch (operacao)
        {
        case 1:
            registrar_paciente(arvore, fila);
            break;
        case 2:
            remover_paciente(arvore, fila);
            break;
        case 3:
            listar_pacientes(arvore);
            break;
        case 4:
            buscar_paciente_por_id(arvore);
            break;
        case 5:
            mostrar_fila_espera(fila);
            break;
        case 6:
            dar_alta_paciente(fila);
            break;
        case 7:
            printf("Encerrando sistema de atendimento médico.\n");
            break;
        default:
            printf("Digite uma operação válida (1-7).\n");
            break;
        }
    } while (operacao != 7);

    // Salva dados antes de sair
    printf("\nSalvando dados do sistema...\n");
    salvar_sistema(arvore, fila);

    // Libera memória
    if (arvore != NULL)
    {
        arvore_apagar(&arvore);
    }
    if (fila != NULL)
    {
        fila_prioridade_apagar(&fila);
    }

    printf("Sistema encerrado com sucesso.\n");
    return 0;
}