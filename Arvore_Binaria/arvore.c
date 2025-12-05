#include <stdlib.h>
#include <stdio.h>
#include "arvore.h"
#include "../TAD_Paciente/paciente.h"

typedef struct no_arvore_
{
    PACIENTE *paciente;
    struct no_arvore_ *esquerda;
    struct no_arvore_ *direita;
    int altura;
} NO_ARVORE;

struct arvore_
{
    NO_ARVORE *raiz;
    int tamanho;
};

// Funções auxiliares privadas
static int _altura(NO_ARVORE *no)
{
    if (no == NULL)
        return -1;
    return no->altura;
}

static int _max(int a, int b)
{
    return (a > b) ? a : b;
}

static int _fator_balanceamento(NO_ARVORE *no)
{
    if (no == NULL)
        return 0;
    return _altura(no->esquerda) - _altura(no->direita);
}

static void _atualizar_altura(NO_ARVORE *no)
{
    if (no != NULL)
        no->altura = 1 + _max(_altura(no->esquerda), _altura(no->direita));
}

// Rotações para balanceamento
static NO_ARVORE *_rotacao_direita(NO_ARVORE *y)
{
    NO_ARVORE *x = y->esquerda;
    NO_ARVORE *T2 = x->direita;

    x->direita = y;
    y->esquerda = T2;

    _atualizar_altura(y);
    _atualizar_altura(x);

    return x;
}

static NO_ARVORE *_rotacao_esquerda(NO_ARVORE *x)
{
    NO_ARVORE *y = x->direita;
    NO_ARVORE *T2 = y->esquerda;

    y->esquerda = x;
    x->direita = T2;

    _atualizar_altura(x);
    _atualizar_altura(y);

    return y;
}

// Inserção recursiva
static NO_ARVORE *_inserir_recursivo(NO_ARVORE *no, PACIENTE *paciente, bool *inserido)
{
    if (no == NULL)
    {
        NO_ARVORE *novo = (NO_ARVORE *)malloc(sizeof(NO_ARVORE));
        if (novo != NULL)
        {
            novo->paciente = paciente;
            novo->esquerda = NULL;
            novo->direita = NULL;
            novo->altura = 0;
            *inserido = true;
        }
        return novo;
    }

    int id_novo = paciente_get_id(paciente);
    int id_atual = paciente_get_id(no->paciente);

    if (id_novo < id_atual)
    {
        no->esquerda = _inserir_recursivo(no->esquerda, paciente, inserido);
    }
    else if (id_novo > id_atual)
    {
        no->direita = _inserir_recursivo(no->direita, paciente, inserido);
    }
    else
    {
        // ID duplicado - não insere
        return no;
    }

    _atualizar_altura(no);

    int balanceamento = _fator_balanceamento(no);

    // Caso esquerda-esquerda
    if (balanceamento > 1 && paciente_get_id(no->esquerda->paciente) > id_novo)
        return _rotacao_direita(no);

    // Caso direita-direita
    if (balanceamento < -1 && paciente_get_id(no->direita->paciente) < id_novo)
        return _rotacao_esquerda(no);

    // Caso esquerda-direita
    if (balanceamento > 1 && paciente_get_id(no->esquerda->paciente) < id_novo)
    {
        no->esquerda = _rotacao_esquerda(no->esquerda);
        return _rotacao_direita(no);
    }

    // Caso direita-esquerda
    if (balanceamento < -1 && paciente_get_id(no->direita->paciente) > id_novo)
    {
        no->direita = _rotacao_direita(no->direita);
        return _rotacao_esquerda(no);
    }

    return no;
}

// Busca recursiva
static PACIENTE *_buscar_recursivo(NO_ARVORE *no, int id)
{
    if (no == NULL)
        return NULL;

    int id_atual = paciente_get_id(no->paciente);

    if (id < id_atual)
        return _buscar_recursivo(no->esquerda, id);
    else if (id > id_atual)
        return _buscar_recursivo(no->direita, id);
    else
        return no->paciente;
}

// Busca do nó mínimo
static NO_ARVORE *_encontrar_minimo(NO_ARVORE *no)
{
    while (no != NULL && no->esquerda != NULL)
        no = no->esquerda;
    return no;
}

// Remoção recursiva
static NO_ARVORE *_remover_recursivo(NO_ARVORE *no, int id, bool *removido)
{
    if (no == NULL)
        return NULL;

    int id_atual = paciente_get_id(no->paciente);

    if (id < id_atual)
    {
        no->esquerda = _remover_recursivo(no->esquerda, id, removido);
    }
    else if (id > id_atual)
    {
        no->direita = _remover_recursivo(no->direita, id, removido);
    }
    else
    {
        *removido = true;
        // Caso 1: nó folha
        if (no->esquerda == NULL && no->direita == NULL)
        {
            free(no);
            return NULL;
        }
        // Caso 2: só tem filho direito
        else if (no->esquerda == NULL)
        {
            NO_ARVORE *temp = no->direita;
            free(no);
            return temp;
        }
        // Caso 3: só tem filho esquerdo
        else if (no->direita == NULL)
        {
            NO_ARVORE *temp = no->esquerda;
            free(no);
            return temp;
        }
        // Caso 4: tem dois filhos
        else
        {
            NO_ARVORE *minimo = _encontrar_minimo(no->direita);
            PACIENTE *temp_paciente = no->paciente;
            no->paciente = minimo->paciente;
            minimo->paciente = temp_paciente;
            no->direita = _remover_recursivo(no->direita, paciente_get_id(minimo->paciente), removido);
        }
    }

    if (no != NULL)
    {
        _atualizar_altura(no);

        int balanceamento = _fator_balanceamento(no);

        if (balanceamento > 1 && _fator_balanceamento(no->esquerda) >= 0)
            return _rotacao_direita(no);

        if (balanceamento > 1 && _fator_balanceamento(no->esquerda) < 0)
        {
            no->esquerda = _rotacao_esquerda(no->esquerda);
            return _rotacao_direita(no);
        }

        if (balanceamento < -1 && _fator_balanceamento(no->direita) <= 0)
            return _rotacao_esquerda(no);

        if (balanceamento < -1 && _fator_balanceamento(no->direita) > 0)
        {
            no->direita = _rotacao_direita(no->direita);
            return _rotacao_esquerda(no);
        }
    }

    return no;
}

// Limpeza recursiva
static void _apagar_recursivo(NO_ARVORE *no)
{
    if (no != NULL)
    {
        _apagar_recursivo(no->esquerda);
        _apagar_recursivo(no->direita);
        paciente_apagar(&no->paciente);
        free(no);
    }
}

// Impressão em ordem
static void _imprimir_inordem(NO_ARVORE *no)
{
    if (no != NULL)
    {
        _imprimir_inordem(no->esquerda);
        paciente_imprimir(no->paciente);
        _imprimir_inordem(no->direita);
    }
}

// Impressão pré-ordem
static void _imprimir_preordem(NO_ARVORE *no)
{
    if (no != NULL)
    {
        paciente_imprimir(no->paciente);
        _imprimir_preordem(no->esquerda);
        _imprimir_preordem(no->direita);
    }
}

// ========== FUNÇÕES PÚBLICAS ==========

ARVORE *arvore_criar(void)
{
    ARVORE *arvore = (ARVORE *)malloc(sizeof(ARVORE));
    if (arvore != NULL)
    {
        arvore->raiz = NULL;
        arvore->tamanho = 0;
    }
    return arvore;
}

bool arvore_apagar(ARVORE **arvore)
{
    if (arvore != NULL && *arvore != NULL)
    {
        _apagar_recursivo((*arvore)->raiz);
        free(*arvore);
        *arvore = NULL;
        return true;
    }
    return false;
}

bool arvore_inserir(ARVORE *arvore, PACIENTE *paciente)
{
    if (arvore == NULL || paciente == NULL)
        return false;

    bool inserido = false;
    arvore->raiz = _inserir_recursivo(arvore->raiz, paciente, &inserido);

    if (inserido)
        arvore->tamanho++;

    return inserido;
}

PACIENTE *arvore_remover(ARVORE *arvore, int id)
{
    if (arvore == NULL)
        return NULL;

    PACIENTE *pac = arvore_buscar(arvore, id);
    if (pac != NULL)
    {
        bool removido = false;
        arvore->raiz = _remover_recursivo(arvore->raiz, id, &removido);
        if (removido)
            arvore->tamanho--;
        return pac;
    }
    return NULL;
}

PACIENTE *arvore_buscar(ARVORE *arvore, int id)
{
    if (arvore == NULL)
        return NULL;
    return _buscar_recursivo(arvore->raiz, id);
}

int arvore_tamanho(ARVORE *arvore)
{
    if (arvore != NULL)
        return arvore->tamanho;
    return -1;
}

bool arvore_vazia(ARVORE *arvore)
{
    if (arvore != NULL)
        return arvore->tamanho == 0;
    return true;
}

void arvore_imprimir_inordem(ARVORE *arvore)
{
    if (arvore != NULL)
    {
        if (arvore_vazia(arvore))
        {
            printf("Árvore vazia.\n");
            return;
        }
        printf("Pacientes (ordem de ID):\n");
        _imprimir_inordem(arvore->raiz);
    }
}

void arvore_imprimir_preordem(ARVORE *arvore)
{
    if (arvore != NULL)
    {
        if (arvore_vazia(arvore))
        {
            printf("Árvore vazia.\n");
            return;
        }
        _imprimir_preordem(arvore->raiz);
    }
}

void arvore_esvaziar(ARVORE *arvore)
{
    if (arvore != NULL)
    {
        _apagar_recursivo(arvore->raiz);
        arvore->raiz = NULL;
        arvore->tamanho = 0;
    }
}

// Iteração (pré-ordem simples para compatibilidade)
void *arvore_primeiro_no(ARVORE *arvore)
{
    if (arvore != NULL && !arvore_vazia(arvore))
    {
        return (void *)arvore->raiz;
    }
    return NULL;
}

void *arvore_proximo_no(void *no)
{
    NO_ARVORE *atual = (NO_ARVORE *)no;
    if (atual == NULL)
        return NULL;

    if (atual->esquerda != NULL)
        return (void *)atual->esquerda;
    else if (atual->direita != NULL)
        return (void *)atual->direita;

    return NULL;
}

PACIENTE *arvore_no_paciente(void *no)
{
    NO_ARVORE *atual = (NO_ARVORE *)no;
    if (atual != NULL)
        return atual->paciente;
    return NULL;
}
