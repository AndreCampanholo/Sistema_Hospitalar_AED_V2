# Pronto Socorro SUS - V2

**Disciplina:** SCC0202 - Algoritmos e Estruturas de Dados I  
**Professores:** Rudinei e JB  
**Monitores:** Laura e Felipe

## 📋 Descrição do Projeto

Sistema de atendimento médico para um Pronto Socorro (PS) que simula um serviço emergencial com gerenciamento eficiente de pacientes. O sistema utiliza **estruturas de dados avançadas** para garantir:

- ✅ **Busca eficiente** de pacientes (O(log n))
- ✅ **Atendimento por prioridade** com desempate por ordem de chegada
- ✅ **Persistência de dados** em disco

## 🏗️ Estrutura de Dados

### 1. **Árvore Binária de Busca Balanceada (AVL)**
- Armazena todos os pacientes registrados
- Permite busca, inserção e remoção em O(log n)
- Auto-balanceamento para garantir eficiência

### 2. **Fila de Prioridade (Heap Máximo)**
- Gerencia a fila de espera dos pacientes
- **5 níveis de prioridade:**
  - **5** - Emergência (risco de morte)
  - **4** - Muito Urgente (grave e risco de morte)
  - **3** - Urgente (gravidade moderada)
  - **2** - Pouco Urgente (poderia ser atendido em básica)
  - **1** - Não Urgência (sem risco)
- Desempate por ordem de chegada (timestamp)

## 📁 Estrutura do Projeto

```
Trabalho_2/
├── Arvore_Binaria/
│   ├── arvore.h
│   └── arvore.c
├── Fila_Prioridade/
│   ├── fila_prioridade.h
│   └── fila_prioridade.c
├── TAD_Paciente/
│   ├── paciente.h
│   └── paciente.c
├── TAD_functions/
│   ├── functions.h
│   └── functions.c
├── TAD_IO/
│   ├── IO.h
│   └── IO.c
├── main.c
├── Makefile
└── README.md
```

## 🎯 Menu de Operações

```
1 - Registrar paciente
2 - Remover paciente
3 - Listar pacientes
4 - Buscar paciente por ID
5 - Mostrar fila de espera
6 - Dar alta ao paciente
7 - Sair
```

## 🚀 Como Compilar e Executar

### Compilação simples:
```bash
make
```

### Execução:
```bash
./sistema
```

### Compilação + Execução:
```bash
make run
```

### Limpeza de arquivos compilados:
```bash
make clean
```

### Limpeza completa (inclui dados salvos):
```bash
make clean-all
```

### Reconstrução completa:
```bash
make rebuild
```

## 💾 Persistência de Dados

Os dados são salvos automaticamente ao sair do sistema em:
- `Persistencia_Dados/arvore_pacientes.bin` - Árvore de pacientes
- `Persistencia_Dados/fila_espera.bin` - Fila de espera

Ao iniciar o programa, o sistema carrega automaticamente os dados salvos anteriormente.

## 📝 Funcionalidades Principais

### 1. Registrar Paciente
- Insere novo paciente com ID único
- Solicita nome e classificação de prioridade (1-5)
- Insere simultaneamente na árvore e fila

### 2. Remover Paciente
- Remove apenas pacientes que **NÃO** estão aguardando atendimento
- Mantém registros de pacientes já atendidos

### 3. Listar Pacientes
- Exibe todos os pacientes registrados (em ordem de ID)
- Mostra prioridade de cada paciente

### 4. Buscar Paciente por ID
- Busca rápida em O(log n) através da árvore

### 5. Mostrar Fila de Espera
- Lista pacientes em ordem de prioridade
- Destaca ordem de chegada para mesma prioridade

### 6. Dar Alta ao Paciente
- Remove paciente da fila de espera (próximo a ser atendido)
- Mantém registros na árvore

## 🔧 Requisitos do Sistema

- Compilador GCC
- Sistema operacional com suporte a POSIX (Linux/Mac) ou Windows
- Permissão para criar diretório `Persistencia_Dados/`

## 👥 Complexidade de Tempo

| Operação | Complexidade |
|----------|--------------|
| Buscar paciente | O(log n) |
| Inserir paciente | O(log n) |
| Remover paciente | O(log n) |
| Chamar próximo (fila) | O(log n) |
| Listar todos | O(n) |

## 📄 Notas Importantes

- IDs de pacientes devem ser únicos
- Sistema valida entrada do usuário
- Dados persistem entre execuções
- Estruturas antigas (Lista, Fila FIFO, Pilha) foram removidas para V2

---

**Desenvolvido para SCC0202 - USP**
