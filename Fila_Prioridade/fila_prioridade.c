#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "fila_prioridade.h"
#include "../TAD_Paciente/paciente.h"

typedef struct elemento_fila_
{
    PACIENTE *paciente;
    int prioridade; // 5 = máxima, 1 = mínima
    time_t timestamp; // Para desempate por ordem de chegada
} ELEMENTO_FILA;

struct fila_prioridade_
{
    ELEMENTO_FILA *heap;
    int tamanho;
    int capacidade;
};

// Funções auxiliares privadas
static int _pai(int i)
{
    return (i - 1) / 2;
}

static int _filho_esquerdo(int i)
{
    return 2 * i + 1;
}

static int _filho_direito(int i)
{
    return 2 * i + 2;
}

// Comparação: retorna true se e1 deve estar acima de e2 no heap
static bool _comparar_prioridade(ELEMENTO_FILA e1, ELEMENTO_FILA e2)
{
    if (e1.prioridade != e2.prioridade)
        return e1.prioridade > e2.prioridade; // Maior prioridade primeiro
    else
        return e1.timestamp < e2.timestamp; // Mesma prioridade: menor timestamp primeiro (chegou antes)
}

static void _trocar(ELEMENTO_FILA *a, ELEMENTO_FILA *b)
{
    ELEMENTO_FILA temp = *a;
    *a = *b;
    *b = temp;
}

// Sobe o elemento para manter propriedade do heap máximo
static void _sobe(FILA_PRIORIDADE *fila, int indice)
{
    while (indice > 0 && _comparar_prioridade(fila->heap[indice], fila->heap[_pai(indice)]))
    {
        _trocar(&fila->heap[indice], &fila->heap[_pai(indice)]);
        indice = _pai(indice);
    }
}

// Desce o elemento para manter propriedade do heap máximo
static void _desce(FILA_PRIORIDADE *fila, int indice)
{
    int maior = indice;
    int esq = _filho_esquerdo(indice);
    int dir = _filho_direito(indice);

    if (esq < fila->tamanho && _comparar_prioridade(fila->heap[esq], fila->heap[maior]))
        maior = esq;

    if (dir < fila->tamanho && _comparar_prioridade(fila->heap[dir], fila->heap[maior]))
        maior = dir;

    if (maior != indice)
    {
        _trocar(&fila->heap[indice], &fila->heap[maior]);
        _desce(fila, maior);
    }
}

// ========== FUNÇÕES PÚBLICAS ==========

FILA_PRIORIDADE *fila_prioridade_criar(int capacidade_maxima)
{
    if (capacidade_maxima <= 0)
        capacidade_maxima = 100; // Capacidade padrão

    FILA_PRIORIDADE *fila = (FILA_PRIORIDADE *)malloc(sizeof(FILA_PRIORIDADE));
    if (fila != NULL)
    {
        fila->heap = (ELEMENTO_FILA *)malloc(sizeof(ELEMENTO_FILA) * capacidade_maxima);
        if (fila->heap != NULL)
        {
            fila->tamanho = 0;
            fila->capacidade = capacidade_maxima;
            return fila;
        }
        free(fila);
    }
    return NULL;
}

bool fila_prioridade_apagar(FILA_PRIORIDADE **fila)
{
    if (fila != NULL && *fila != NULL)
    {
        // Não liberamos os pacientes aqui, pois eles são gerenciados pela árvore
        if ((*fila)->heap != NULL)
        {
            free((*fila)->heap);
            (*fila)->heap = NULL;
        }
        free(*fila);
        *fila = NULL;
        return true;
    }
    return false;
}

bool fila_prioridade_inserir(FILA_PRIORIDADE *fila, PACIENTE *paciente, int prioridade)
{
    if (fila == NULL || paciente == NULL || prioridade < 1 || prioridade > 5)
        return false;

    if (fila_prioridade_cheia(fila))
    {
        printf("Fila de prioridade cheia!\n");
        return false;
    }

    ELEMENTO_FILA novo;
    novo.paciente = paciente;
    novo.prioridade = prioridade;
    novo.timestamp = time(NULL);

    fila->heap[fila->tamanho] = novo;
    _sobe(fila, fila->tamanho);
    fila->tamanho++;

    return true;
}

PACIENTE *fila_prioridade_remover(FILA_PRIORIDADE *fila, int *prioridade_saida)
{
    if (fila == NULL || fila_prioridade_vazia(fila))
        return NULL;

    PACIENTE *paciente = fila->heap[0].paciente;
    if (prioridade_saida != NULL)
        *prioridade_saida = fila->heap[0].prioridade;

    fila->heap[0] = fila->heap[fila->tamanho - 1];
    fila->tamanho--;

    if (fila->tamanho > 0)
        _desce(fila, 0);

    return paciente;
}

PACIENTE *fila_prioridade_primeiro(FILA_PRIORIDADE *fila)
{
    if (fila == NULL || fila_prioridade_vazia(fila))
        return NULL;
    return fila->heap[0].paciente;
}

int fila_prioridade_tamanho(FILA_PRIORIDADE *fila)
{
    if (fila != NULL)
        return fila->tamanho;
    return -1;
}

bool fila_prioridade_vazia(FILA_PRIORIDADE *fila)
{
    if (fila != NULL)
        return fila->tamanho == 0;
    return true;
}

bool fila_prioridade_cheia(FILA_PRIORIDADE *fila)
{
    if (fila != NULL)
        return fila->tamanho >= fila->capacidade;
    return true;
}

void fila_prioridade_imprimir(FILA_PRIORIDADE *fila)
{
    if (fila == NULL || fila_prioridade_vazia(fila))
    {
        printf("Fila de espera vazia.\n");
        return;
    }

    printf("\n=== FILA DE ESPERA (Ordenada por Prioridade) ===\n");
    printf("%-5s %-30s %-15s\n", "Prio.", "Nome do Paciente", "ID");
    printf("-------------------------------------------------\n");

    // Cria um vetor temporário para ordenar por prioridade
    ELEMENTO_FILA *temp = (ELEMENTO_FILA *)malloc(sizeof(ELEMENTO_FILA) * fila->tamanho);
    if (temp != NULL)
    {
        memcpy(temp, fila->heap, sizeof(ELEMENTO_FILA) * fila->tamanho);

        // Ordena por prioridade e timestamp
        for (int i = 0; i < fila->tamanho - 1; i++)
        {
            for (int j = i + 1; j < fila->tamanho; j++)
            {
                if (!_comparar_prioridade(temp[i], temp[j]))
                {
                    _trocar(&temp[i], &temp[j]);
                }
            }
        }

        const char *desc_prioridade[] = {"", "Não Urgência", "Pouco Urgente", "Urgente", "Muito Urgente", "Emergência"};

        for (int i = 0; i < fila->tamanho; i++)
        {
            int prio = temp[i].prioridade;
            const char *prio_str = (prio >= 1 && prio <= 5) ? desc_prioridade[prio] : "Desconhecida";
            printf("%-5s %-30s %-15d\n", prio_str, paciente_get_nome(temp[i].paciente), paciente_get_id(temp[i].paciente));
        }

        free(temp);
    }
    printf("-------------------------------------------------\n");
}

void fila_prioridade_esvaziar(FILA_PRIORIDADE *fila)
{
    if (fila != NULL)
    {
        // Não liberamos os pacientes aqui, apenas o heap
        fila->tamanho = 0;
    }
}

PACIENTE *fila_prioridade_buscar_paciente(FILA_PRIORIDADE *fila, int id_paciente)
{
    if (fila == NULL)
        return NULL;

    for (int i = 0; i < fila->tamanho; i++)
    {
        if (paciente_get_id(fila->heap[i].paciente) == id_paciente)
            return fila->heap[i].paciente;
    }
    return NULL;
}
