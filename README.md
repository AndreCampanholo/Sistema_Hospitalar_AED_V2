## Sistema Hospitalar AED - V2

Este projeto simula um sistema de atendimento médico de pacientes em um Pronto Socorro (PS), utilizando Tipos Abstratos de Dados (TADs) em C com eficiência computacional aprimorada através de estruturas de dados balanceadas.

Desenvolvido por:
- André Campanholo Paschoalini - 14558061
- Eduardo Poltroniere da Silva - 16862892
- Pedro Hamamoto da Palma - 16818280

## Estrutura

`main.c` - ponto de entrada e loop do menu.

Diretórios principais / TADs:
- `TAD_Paciente/` - (`paciente.c`, `paciente.h`) cadastro, busca, remoção e gerenciamento de pacientes (id, nome, prioridade).
- `Arvore_Binaria/` - (`arvore.c`, `arvore.h`) árvore binária de busca balanceada (AVL) para armazenar pacientes com busca eficiente O(log n).
- `Fila_Prioridade/` - (`fila_prioridade.c`, `fila_prioridade.h`) fila de prioridade implementada com heap máximo para atendimento por prioridade com desempate por ordem de chegada.
- `TAD_functions/` - (`functions.c`, `functions.h`) implementa as sete operações do menu e a lógica de negócio (registrar, remover, listar, buscar, mostrar fila, dar alta, sair).
- `TAD_IO/` - (`IO.c`, `IO.h`) persistência: `SAVE` e `LOAD` para ler/gravar `arvore_pacientes.bin` e `fila_espera.bin`.

## Principais funcionalidades e onde estão implementadas

- Registrar paciente: `TAD_functions/registrar_paciente` — cria `PACIENTE` com prioridade (1-5), insere na `Arvore_Binaria` e em `Fila_Prioridade`.
- Remover paciente: `TAD_functions/remover_paciente` — só permite apagar paciente se ele NÃO estiver na fila de espera; remove da árvore e apaga o `PACIENTE`.
- Listar pacientes: `TAD_functions/listar_pacientes` — imprime todos os pacientes da árvore em ordem de ID.
- Buscar paciente: `TAD_functions/buscar_paciente_por_id` — busca um paciente específico por ID na árvore em O(log n).
- Mostrar fila: `TAD_functions/mostrar_fila_espera` — imprime a fila de espera ordenada por prioridade e ordem de chegada.
- Dar alta: `TAD_functions/dar_alta_paciente` — remove o próximo paciente da fila (maior prioridade) e mantém seu registro na árvore.
- Sair: encerra o programa salvando os dados automaticamente.
- Salvar/Carregar: `TAD_IO/SAVE` e `TAD_IO/LOAD` carregam e salvam a árvore e fila de pacientes ao iniciar e ao fechar o programa (`main.c`) respectivamente.

## Persistência

- Ao sair (opção de menu), o programa chama `SAVE(arvore, fila)` e grava `arvore_pacientes.bin` e `fila_espera.bin`.
- Ao iniciar, `LOAD(&arvore, &fila)` tenta recarregar os dados.

## Funções da interface

1. Registrar paciente
2. Remover paciente
3. Listar pacientes
4. Buscar paciente por ID
5. Mostrar fila de espera
6. Dar alta ao paciente
7. Sair

## Escolha dos TADs

**TAD Paciente:** O TAD paciente armazena as informações essenciais de um paciente: ID (inteiro único), nome (string) e prioridade (inteiro de 1 a 5). Existem funções de criar, apagar, ler id/nome/prioridade, modificar estes atributos e imprimir as informações de um paciente, todas de custo constante O(1). A prioridade segue a classificação: 5 (Emergência), 4 (Muito Urgente), 3 (Urgente), 2 (Pouco Urgente), 1 (Não Urgência).

**TAD Árvore Binária de Busca Balanceada (AVL):** A árvore AVL foi escolhida para armazenar todos os pacientes do banco de dados, permitindo buscas, inserções e remoções com complexidade O(log n). Cada nó da árvore armazena um ponteiro para `PACIENTE` e ponteiros para os filhos esquerdo e direito. A estrutura inclui auto-balanceamento através de rotações (simples e duplas) mantendo o fator de balanceamento entre -1 e 1. Existem funções de criar, apagar, inserir, remover, buscar, verificar se está vazia, imprimir em ordem (in-ordem e pré-ordem) e contar pacientes. As operações de inserção, remoção e busca possuem complexidade O(log n), enquanto impressão e iteração têm custo O(n).

**TAD Fila de Prioridade (Heap Máximo):** Foi utilizada uma fila de prioridade implementada com heap máximo como estrutura para gerenciar a fila de espera. Cada elemento armazena um `PACIENTE`, sua prioridade (1-5) e um timestamp de chegada para desempate. O heap máximo garante que o paciente com maior prioridade sempre esteja na raiz, e em caso de prioridades iguais, o com menor timestamp (chegou primeiro) tem precedência. A fila tem capacidade configurável (padrão 1000 pacientes) e cresce dinamicamente se necessário. Existem funções de criar, apagar, inserir, remover (do topo), consultar o primeiro, verificar se está vazia/cheia, imprimir ordenado e buscar um paciente específico. As operações de inserção e remoção possuem complexidade O(log n), enquanto busca, impressão e iteração têm custo O(n).

**TAD Functions:** TAD que contém as sete funções da interface do usuário. Esse TAD inclui todos os outros, e usa as funções dele para realizar as operações do hospital. Abaixo, um resumo das funcionalidades de cada uma:

`imprimir_escolha_operacao()`
Exibe no terminal o menu principal de operações (opções **1 a 7**) e retorna ao programa.

`registrar_paciente(ARVORE arvore, FILA_PRIORIDADE fila)`
Cadastra um novo paciente no sistema.
- Lê o **ID** do paciente.
- Se **já existir paciente com esse ID**, informa erro.
- Se **não existir**, lê o nome, solicita a **prioridade** (1-5), cria o `PACIENTE`, insere na `Arvore_Binaria` e também na `Fila_Prioridade`.

`remover_paciente(ARVORE arvore, FILA_PRIORIDADE fila)`
Remove definitivamente um paciente do sistema.

- Lê o **ID**.
- Se **estiver na FILA_PRIORIDADE**, bloqueia a remoção pois o paciente está aguardando atendimento.
- Se **não estiver na fila**, remove da árvore e destrói o registro.
- Se **não existir**, informa que o paciente é inexistente.

`listar_pacientes(ARVORE arvore)`
Exibe todos os pacientes registrados no sistema.

- Imprime a árvore em ordem (in-ordem), mostrando ID, nome e prioridade de cada paciente.
- Se a árvore estiver vazia, informa ao usuário.

`buscar_paciente_por_id(ARVORE arvore)`
Busca um paciente específico pelo seu ID.

- Lê o **ID** a buscar.
- Realiza busca na árvore com complexidade O(log n).
- Se encontrado, exibe os dados do paciente.
- Se não encontrado, informa que o paciente inexiste.

`mostrar_fila_espera(FILA_PRIORIDADE fila)`
Exibe a **fila de espera** ordenada por prioridade.

- Se a fila estiver **vazia**, informa.
- Caso contrário, imprime todos os pacientes da `FILA_PRIORIDADE` ordenados por prioridade (decrescente) e, para mesma prioridade, por ordem de chegada (crescente).

`dar_alta_paciente(FILA_PRIORIDADE fila)`
Chama o próximo paciente para atendimento.

- Remove (**dequeue**) o primeiro paciente da `FILA_PRIORIDADE` (maior prioridade).
- O paciente permanece no banco de dados da árvore para fins de histórico.
- Se havia alguém, imprime o paciente chamado.
- Se a fila estiver vazia, informa ao usuário.

**TAD IO:** TAD responsável pela persistência dos dados. As operações de salvar e de carregar as informações são feitas durante o encerramento e o início do programa, respectivamente. Os dados não são salvos on-the-fly. A implementação salva os pacientes em formato binário reconstruindo a árvore e fila automaticamente ao carregar.

## Compilação

```bash
make
```

Ou manualmente:

```bash
gcc -o sistema main.c TAD_Paciente/paciente.c Arvore_Binaria/arvore.c Fila_Prioridade/fila_prioridade.c TAD_functions/functions.c TAD_IO/IO.c
```

## Execução

```bash
./sistema
```