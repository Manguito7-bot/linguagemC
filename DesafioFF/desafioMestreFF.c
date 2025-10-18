#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

#define MAX_COMP 20

typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
    int prioridade;
} Componente;

// ===============================
// Funcoes auxiliares
// ===============================
void removerQuebraLinha(char *str) {
    size_t len = strlen(str);
    if (len > 0 && str[len - 1] == '\n') {
        str[len - 1] = '\0';
    }
}

void trocar(Componente *a, Componente *b) {
    Componente temp = *a;
    *a = *b;
    *b = temp;
}

// ===============================
// Funcao segura para ler numero do menu
// ===============================
int lerOpcaoMenu(int min, int max) {
    char buffer[20];
    int numero;
    char *endptr;

    while (1) {
        printf("Escolha uma opcao: ");
        if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
            continue;
        }
        removerQuebraLinha(buffer);

        // Verifica se contem apenas digitos
        int valido = 1;
        for (size_t i = 0; i < strlen(buffer); i++) {
            if (!isdigit((unsigned char)buffer[i])) {
                valido = 0;
                break;
            }
        }

        if (!valido) {
            printf("Entrada invalida. Digite apenas numeros entre %d e %d.\n", min, max);
            continue;
        }

        numero = (int)strtol(buffer, &endptr, 10);
        if (numero < min || numero > max) {
            printf("Opcao fora do intervalo. Digite um numero entre %d e %d.\n", min, max);
            continue;
        }

        return numero;
    }
}

// ===============================
// Mostrar componentes
// ===============================
void mostrarComponentes(Componente vetor[], int tamanho) {
    printf("\n=== LISTA DE COMPONENTES ===\n");
    if (tamanho == 0) {
        printf("Nenhum componente cadastrado.\n");
        return;
    }
    for (int i = 0; i < tamanho; i++) {
        printf("[%d] Nome: %-20s | Tipo: %-15s | Quantidade: %-5d | Prioridade: %d\n",
               i + 1,
               vetor[i].nome,
               vetor[i].tipo,
               vetor[i].quantidade,
               vetor[i].prioridade);
    }
}

// ===============================
// Cadastrar componentes
// ===============================
void cadastrarComponente(Componente vetor[], int *tamanho) {
    if (*tamanho >= MAX_COMP) {
        printf("\nLimite maximo de componentes atingido.\n");
        return;
    }

    Componente novo;
    printf("\n=== CADASTRAR COMPONENTE ===\n");
    printf("Nome: ");
    fgets(novo.nome, sizeof(novo.nome), stdin);
    removerQuebraLinha(novo.nome);

    printf("Tipo: ");
    fgets(novo.tipo, sizeof(novo.tipo), stdin);
    removerQuebraLinha(novo.tipo);

    printf("Quantidade: ");
    scanf("%d", &novo.quantidade);
    getchar(); // limpa buffer

    printf("Prioridade (1 a 10): ");
    scanf("%d", &novo.prioridade);
    getchar(); // limpa buffer

    vetor[*tamanho] = novo;
    (*tamanho)++;

    printf("Componente '%s' cadastrado com sucesso!\n", novo.nome);
}

// ===============================
// Ordenacoes
// ===============================
void bubbleSortNome(Componente vetor[], int tamanho) {
    int comparacoes = 0;
    for (int i = 0; i < tamanho - 1; i++) {
        for (int j = 0; j < tamanho - i - 1; j++) {
            comparacoes++;
            if (strcmp(vetor[j].nome, vetor[j + 1].nome) > 0) {
                trocar(&vetor[j], &vetor[j + 1]);
            }
        }
    }
    printf("Comparacoes (Bubble Sort Nome): %d\n", comparacoes);
}

void insertionSortTipo(Componente vetor[], int tamanho) {
    int comparacoes = 0;
    for (int i = 1; i < tamanho; i++) {
        Componente chave = vetor[i];
        int j = i - 1;
        while (j >= 0 && strcmp(vetor[j].tipo, chave.tipo) > 0) {
            comparacoes++;
            vetor[j + 1] = vetor[j];
            j--;
        }
        comparacoes++;
        vetor[j + 1] = chave;
    }
    printf("Comparacoes (Insertion Sort Tipo): %d\n", comparacoes);
}

void selectionSortPrioridade(Componente vetor[], int tamanho) {
    int comparacoes = 0;
    for (int i = 0; i < tamanho - 1; i++) {
        int min = i;
        for (int j = i + 1; j < tamanho; j++) {
            comparacoes++;
            if (vetor[j].prioridade < vetor[min].prioridade) {
                min = j;
            }
        }
        if (min != i) {
            trocar(&vetor[i], &vetor[min]);
        }
    }
    printf("Comparacoes (Selection Sort Prioridade): %d\n", comparacoes);
}

// ===============================
// Medir tempo de execucao
// ===============================
void medirTempo(void (*algoritmo)(Componente[], int), Componente vetor[], int tamanho) {
    clock_t inicio = clock();
    algoritmo(vetor, tamanho);
    clock_t fim = clock();
    double tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
    printf("Tempo de execucao: %.6f segundos\n", tempo);
}

// ===============================
// Verificar se esta ordenado por nome
// ===============================
int estaOrdenadoPorNome(Componente vetor[], int tamanho) {
    for (int i = 0; i < tamanho - 1; i++) {
        if (strcmp(vetor[i].nome, vetor[i + 1].nome) > 0) {
            return 0;
        }
    }
    return 1;
}

// ===============================
// Busca binaria por nome
// ===============================
int buscaBinariaPorNome(Componente vetor[], int tamanho, char chave[]) {
    int inicio = 0, fim = tamanho - 1, comparacoes = 0;
    while (inicio <= fim) {
        int meio = (inicio + fim) / 2;
        comparacoes++;
        int cmp = strcmp(chave, vetor[meio].nome);
        if (cmp == 0) {
            printf("Comparacoes (Busca Binaria): %d\n", comparacoes);
            return meio;
        } else if (cmp < 0) {
            fim = meio - 1;
        } else {
            inicio = meio + 1;
        }
    }
    printf("Comparacoes (Busca Binaria): %d\n", comparacoes);
    return -1;
}

// ===============================
// Submenu de ordenacao
// ===============================
void submenuOrdenacao(Componente componentes[], int total) {
    int opcaoOrdenar;
    do {
        printf("\n=== MENU DE ORDENACAO ===\n");
        printf("1. Ordenar por nome (Bubble Sort)\n");
        printf("2. Ordenar por tipo (Insertion Sort)\n");
        printf("3. Ordenar por prioridade (Selection Sort)\n");
        printf("0. Cancelar e voltar\n");
        opcaoOrdenar = lerOpcaoMenu(0, 3);

        switch (opcaoOrdenar) {
            case 1:
                medirTempo(bubbleSortNome, componentes, total);
                mostrarComponentes(componentes, total);
                break;
            case 2:
                medirTempo(insertionSortTipo, componentes, total);
                mostrarComponentes(componentes, total);
                break;
            case 3:
                medirTempo(selectionSortPrioridade, componentes, total);
                mostrarComponentes(componentes, total);
                break;
            case 0:
                printf("Voltando ao menu inicial...\n");
                break;
            default:
                printf("Opcao invalida.\n");
        }
    } while (opcaoOrdenar != 0);
}

// ===============================
// Menu principal
// ===============================
int main() {
    Componente componentes[MAX_COMP];
    int total = 0;
    int opcao;

    do {
        printf("\n==============================\n");
        printf("SISTEMA DE MONTAGEM DA TORRE\n");
        printf("==============================\n");
        printf("1. Cadastrar componente\n");
        printf("2. Mostrar componentes\n");
        printf("3. Ordenar componentes\n");
        printf("4. Buscar componente-chave (Binaria)\n");
        printf("0. Sair\n");
        opcao = lerOpcaoMenu(0, 4);

        switch (opcao) {
            case 1:
                cadastrarComponente(componentes, &total);
                mostrarComponentes(componentes, total);
                break;
            case 2:
                mostrarComponentes(componentes, total);
                break;
            case 3:
                submenuOrdenacao(componentes, total);
                break;
            case 4: {
                if (total == 0) {
                    printf("\nNenhum componente cadastrado.\n");
                    break;
                }

                if (!estaOrdenadoPorNome(componentes, total)) {
                    printf("\nE necessario ordenar a lista por NOME antes de usar a busca binaria.\n");
                    printf("Pressione ENTER para voltar ao menu...");
                    getchar();
                    break;
                }

                char chave[30];
                printf("Digite o nome do componente-chave: ");
                fgets(chave, sizeof(chave), stdin);
                removerQuebraLinha(chave);

                int pos = buscaBinariaPorNome(componentes, total, chave);
                if (pos != -1) {
                    printf("\nComponente encontrado!\n");
                    printf("Nome: %s | Tipo: %s | Quantidade: %d | Prioridade: %d\n",
                           componentes[pos].nome,
                           componentes[pos].tipo,
                           componentes[pos].quantidade,
                           componentes[pos].prioridade);
                } else {
                    printf("\nComponente '%s' nao encontrado.\n", chave);
                }
                break;
            }
            case 0:
                printf("\nEncerrando o sistema...\n");
                break;
        }

    } while (opcao != 0);

    return 0;
}