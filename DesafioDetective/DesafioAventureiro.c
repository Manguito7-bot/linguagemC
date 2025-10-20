#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// =====================
// Estrutura da Mansão
// =====================
typedef struct Sala {
    char nome[50];
    char pista[100]; // pista associada à sala (pode ser vazia)
    struct Sala *esquerda;
    struct Sala *direita;
} Sala;

// =====================
// Estrutura da BST de Pistas
// =====================
typedef struct NoPista {
    char pista[100];
    struct NoPista *esquerda;
    struct NoPista *direita;
} NoPista;

// =====================
// Funções para Sala
// =====================
Sala* criarSala(const char *nome, const char *pista) {
    Sala *nova = (Sala*) malloc(sizeof(Sala));
    if (nova == NULL) {
        printf("Erro ao alocar memória para a sala.\n");
        exit(1);
    }
    strcpy(nova->nome, nome);
    strcpy(nova->pista, pista);
    nova->esquerda = NULL;
    nova->direita = NULL;
    return nova;
}

void liberarMansao(Sala *raiz) {
    if (raiz != NULL) {
        liberarMansao(raiz->esquerda);
        liberarMansao(raiz->direita);
        free(raiz);
    }
}

// =====================
// Funções para Pistas (BST)
// =====================
NoPista* inserirPista(NoPista *raiz, const char *pista) {
    if (raiz == NULL) {
        NoPista *novo = (NoPista*) malloc(sizeof(NoPista));
        if (novo == NULL) {
            printf("Erro ao alocar memória para pista.\n");
            exit(1);
        }
        strcpy(novo->pista, pista);
        novo->esquerda = NULL;
        novo->direita = NULL;
        return novo;
    }

    int cmp = strcmp(pista, raiz->pista);
    if (cmp < 0) {
        raiz->esquerda = inserirPista(raiz->esquerda, pista);
    } else if (cmp > 0) {
        raiz->direita = inserirPista(raiz->direita, pista);
    }
    // se for igual, não insere duplicada
    return raiz;
}

void exibirPistasOrdenadas(NoPista *raiz) {
    if (raiz != NULL) {
        exibirPistasOrdenadas(raiz->esquerda);
        printf("- %s\n", raiz->pista);
        exibirPistasOrdenadas(raiz->direita);
    }
}

void liberarPistas(NoPista *raiz) {
    if (raiz != NULL) {
        liberarPistas(raiz->esquerda);
        liberarPistas(raiz->direita);
        free(raiz);
    }
}

// =====================
// Exploração da Mansão
// =====================
void explorarMansao(Sala *raiz, NoPista **pistas) {
    Sala *atual = raiz;
    char escolha;

    printf("\n Bem-vindo(a) à Detective Quest - Coleta de Pistas!\n");
    printf("Você começará no Hall de Entrada.\n");

    while (1) {
        printf("\nVocê está em: %s\n", atual->nome);

        // Coleta automática de pista, se existir
        if (strlen(atual->pista) > 0) {
            *pistas = inserirPista(*pistas, atual->pista);
            printf("📜 Você encontrou uma pista: \"%s\"\n", atual->pista);
        } else {
            printf("📭 Nenhuma pista neste cômodo.\n");
        }

        printf("\nPara onde deseja ir?\n");
        if (atual->esquerda != NULL) printf("[e] Esquerda -> %s\n", atual->esquerda->nome);
        if (atual->direita != NULL) printf("[d] Direita -> %s\n", atual->direita->nome);
        printf("[s] Sair e ver pistas\n");

        printf("Escolha: ");
        scanf(" %c", &escolha);

        if (escolha == 'e' && atual->esquerda != NULL) {
            atual = atual->esquerda;
        } 
        else if (escolha == 'd' && atual->direita != NULL) {
            atual = atual->direita;
        } 
        else if (escolha == 's') {
            printf("\n Exploração encerrada pelo detetive.\n");
            break;
        } 
        else {
            printf("\n Opção inválida ou caminho inexistente.\n");
        }
    }
}

// =====================
// Programa Principal
// =====================
int main() {
    // ---- Criação manual da mansão (Árvore Binária) ----
    Sala *hall = criarSala("Hall de Entrada", "Pegada de sapato");
    hall->esquerda = criarSala("Sala de Estar", "Relógio quebrado");
    hall->direita = criarSala("Cozinha", "Xícara com batom");

    hall->esquerda->esquerda = criarSala("Jardim", "");
    hall->esquerda->direita = criarSala("Biblioteca", "Livro rasgado");

    hall->direita->esquerda = criarSala("Despensa", "Garrafa vazia");
    hall->direita->direita = criarSala("Sala de Jantar", "");

    hall->esquerda->direita->esquerda = criarSala("Porão", "Chave enferrujada");
    hall->direita->direita->direita = criarSala("Varanda", "Pegada de lama");

    // ---- Árvore BST para pistas ----
    NoPista *pistasColetadas = NULL;

    // ---- Exploração ----
    explorarMansao(hall, &pistasColetadas);

    // ---- Exibe pistas coletadas ----
    printf("\n Pistas coletadas (ordem alfabética):\n");
    if (pistasColetadas == NULL) {
        printf("Nenhuma pista foi coletada.\n");
    } else {
        exibirPistasOrdenadas(pistasColetadas);
    }

    // ---- Liberação de memória ----
    liberarMansao(hall);
    liberarPistas(pistasColetadas);

    return 0;
}