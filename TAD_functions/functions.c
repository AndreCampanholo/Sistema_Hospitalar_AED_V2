#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"
#include "../Arvore_Binaria/arvore.h"
#include "../Fila_Prioridade/fila_prioridade.h"
#include "../TAD_Paciente/paciente.h"
#include "../TAD_IO/IO.h"

// Exibe o menu principal
void imprimir_escolha_operacao(void)
{
    printf("\n========== MENU PRINCIPAL ==========\n");
    printf("1 - Registrar paciente\n");
    printf("2 - Remover paciente\n");
    printf("3 - Listar pacientes\n");
    printf("4 - Buscar paciente por ID\n");
    printf("5 - Mostrar fila de espera\n");
    printf("6 - Dar alta ao paciente\n");
    printf("7 - Sair\n");
    printf("====================================\n");
}

// Exibe menu de classificação de prioridade
static int exibir_menu_prioridade(void)
{
    printf("\nClassificação do paciente:\n");
    printf("5 - Emergência (Risco de morte)\n");
    printf("4 - Muito Urgente (Grave e risco de morte)\n");
    printf("3 - Urgente (Gravidade moderada)\n");
    printf("2 - Pouco Urgente (Poderia ser atendido em básica)\n");
    printf("1 - Não Urgência (Sem risco)\n");
    printf("Escolha a prioridade: ");
    
    int prioridade;
    if (scanf("%d", &prioridade) != 1 || prioridade < 1 || prioridade > 5)
    {
        while (getchar() != '\n');
        printf("Prioridade inválida! Usando Não Urgência.\n");
        return NAO_URGENCIA;
    }
    return prioridade;
}

// Registra um novo paciente
void registrar_paciente(ARVORE *arvore, FILA_PRIORIDADE *fila)
{
    if (arvore == NULL || fila == NULL)
    {
        printf("Erro: Árvore ou fila inválida.\n");
        return;
    }

    int id;
    printf("\n--- Registrar Novo Paciente ---\n");
    printf("Digite o ID do paciente: ");
    
    if (scanf("%d", &id) != 1)
    {
        while (getchar() != '\n');
        printf("ID inválido!\n");
        return;
    }
    getchar();

    // Verifica se já existe paciente com este ID
    if (arvore_buscar(arvore, id) != NULL)
    {
        printf("Erro: Já existe um paciente com ID %d no sistema.\n", id);
        return;
    }

    char nome[100];
    printf("Digite o nome do paciente: ");
    if (fgets(nome, 99, stdin) == NULL)
    {
        printf("Erro ao ler nome.\n");
        return;
    }
    nome[strcspn(nome, "\n")] = '\0';

    if (strlen(nome) == 0)
    {
        printf("Nome não pode estar vazio.\n");
        return;
    }

    int prioridade = exibir_menu_prioridade();
    while (getchar() != '\n');

    // Cria o paciente
    PACIENTE *paciente = paciente_criar(id, nome, prioridade);
    if (paciente == NULL)
    {
        printf("Erro ao criar paciente.\n");
        return;
    }

    // Insere na árvore
    if (!arvore_inserir(arvore, paciente))
    {
        printf("Erro ao inserir paciente na árvore.\n");
        paciente_apagar(&paciente);
        return;
    }

    // Insere na fila de prioridade
    if (!fila_prioridade_inserir(fila, paciente, prioridade))
    {
        printf("Erro ao inserir paciente na fila de espera.\n");
        arvore_remover(arvore, id);
        return;
    }

    printf("Paciente %s (ID: %d) registrado com sucesso em prioridade: %s\n",
           nome, id, paciente_descricao_prioridade(prioridade));
}

// Remove um paciente do sistema
void remover_paciente(ARVORE *arvore, FILA_PRIORIDADE *fila)
{
    if (arvore == NULL || fila == NULL)
    {
        printf("Erro: Árvore ou fila inválida.\n");
        return;
    }

    int id;
    printf("\n--- Remover Paciente ---\n");
    printf("Digite o ID do paciente a remover: ");
    
    if (scanf("%d", &id) != 1)
    {
        while (getchar() != '\n');
        printf("ID inválido!\n");
        return;
    }

    // Verifica se está na fila (se estiver, não pode remover)
    if (fila_prioridade_buscar_paciente(fila, id) != NULL)
    {
        printf("Erro: Paciente %d está aguardando atendimento. Não pode ser removido.\n", id);
        return;
    }

    // Remove da árvore
    PACIENTE *paciente = arvore_remover(arvore, id);
    if (paciente != NULL)
    {
        printf("Paciente %d (%s) removido com sucesso.\n", id, paciente_get_nome(paciente));
        paciente_apagar(&paciente);
    }
    else
    {
        printf("Paciente com ID %d não encontrado.\n", id);
    }
}

// Lista todos os pacientes
void listar_pacientes(ARVORE *arvore)
{
    if (arvore == NULL)
    {
        printf("Erro: Árvore inválida.\n");
        return;
    }

    printf("\n--- LISTA DE PACIENTES REGISTRADOS ---\n");
    if (arvore_vazia(arvore))
    {
        printf("Nenhum paciente registrado.\n");
        return;
    }

    arvore_imprimir_inordem(arvore);
    printf("Total de pacientes: %d\n", arvore_tamanho(arvore));
}

// Busca um paciente por ID
void buscar_paciente_por_id(ARVORE *arvore)
{
    if (arvore == NULL)
    {
        printf("Erro: Árvore inválida.\n");
        return;
    }

    int id;
    printf("\n--- Buscar Paciente ---\n");
    printf("Digite o ID do paciente: ");
    
    if (scanf("%d", &id) != 1)
    {
        while (getchar() != '\n');
        printf("ID inválido!\n");
        return;
    }

    PACIENTE *paciente = arvore_buscar(arvore, id);
    if (paciente != NULL)
    {
        printf("Paciente encontrado:\n");
        paciente_imprimir(paciente);
    }
    else
    {
        printf("Paciente com ID %d não encontrado.\n", id);
    }
}

// Exibe a fila de espera
void mostrar_fila_espera(FILA_PRIORIDADE *fila)
{
    if (fila == NULL)
    {
        printf("Erro: Fila inválida.\n");
        return;
    }

    fila_prioridade_imprimir(fila);
}

// Dar alta ao paciente (remove da fila)
void dar_alta_paciente(FILA_PRIORIDADE *fila)
{
    if (fila == NULL)
    {
        printf("Erro: Fila inválida.\n");
        return;
    }

    printf("\n--- Dar Alta ao Paciente ---\n");
    
    PACIENTE *paciente = fila_prioridade_primeiro(fila);
    if (paciente == NULL)
    {
        printf("Nenhum paciente na fila de espera.\n");
        return;
    }

    int prioridade = 0;
    paciente = fila_prioridade_remover(fila, &prioridade);
    
    if (paciente != NULL)
    {
        printf("Paciente %d (%s) foi atendido e removido da fila.\n",
               paciente_get_id(paciente), paciente_get_nome(paciente));
        printf("Paciente permanece nos registros do hospital.\n");
    }
}

// Salva o sistema em disco
void salvar_sistema(ARVORE *arvore, FILA_PRIORIDADE *fila)
{
    if (SAVE(arvore, fila))
    {
        printf("Sistema salvo com sucesso.\n");
    }
    else
    {
        printf("Erro ao salvar o sistema.\n");
    }
}

// Carrega o sistema do disco
bool carregar_sistema(ARVORE **arvore, FILA_PRIORIDADE **fila)
{
    return LOAD(arvore, fila);
}