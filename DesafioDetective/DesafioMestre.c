#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM_HASH 17   // tamanho da tabela hash (primo para melhor distribuição)

// ======================
// Estrutura da Mansão
// ======================
typedef struct Sala {
    char nome[50];
    char pista[100];
    struct Sala *esquerda;
    struct Sala *direita;
} Sala;

// ======================
// Estrutura da BST de Pistas
// ======================
typedef struct NoPista {
    char pista[100];
    struct NoPista *esquerda;
    struct NoPista *direita;
} NoPista;

// ======================
// Estrutura da Hash
// ======================
typedef struct HashNode {
    char pista[100];
    char suspeito[50];
    struct HashNode *prox;
} HashNode;

HashNode* tabelaHash[TAM_HASH];

// ======================
// Funções para Hash
// ======================
unsigned int hash(const char *chave) {
    unsigned int h = 0;
    for (int i = 0; chave[i] != '\0'; i++) {
        h = (h * 31) + chave[i];
    }
    return h % TAM_HASH;
}

void inserirHash(const char *pista, const char *suspeito) {
    unsigned int indice = hash(pista);
    HashNode *novo = (HashNode*) malloc(sizeof(HashNode));
    strcpy(novo->pista, pista);
    strcpy(novo->suspeito, suspeito);
    novo->prox = tabelaHash[indice];
    tabelaHash[indice] = novo;
}

const char* buscarSuspeito(const char *pista) {
    unsigned int indice = hash(pista);
    HashNode *atual = tabelaHash[indice];
    while (atual != NULL) {
        if (strcmp(atual->pista, pista) == 0) {
            return atual->suspeito;
        }
        atual = atual->prox;
    }
    return NULL;
}

void liberarHash() {
    for (int i = 0; i < TAM_HASH; i++) {
        HashNode *atual = tabelaHash[i];
        while (atual != NULL) {
            HashNode *temp = atual;
            atual = atual->prox;
            free(temp);
        }
    }
}

// ======================
// Funções para Sala (Árvore)
// ======================
Sala* criarSala(const char *nome, const char *pista) {
    Sala *nova = (Sala*) malloc(sizeof(Sala));
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

// ======================
// Funções para BST de Pistas
// ======================
NoPista* inserirPistaBST(NoPista *raiz, const char *pista) {
    if (raiz == NULL) {
        NoPista *novo = (NoPista*) malloc(sizeof(NoPista));
        strcpy(novo->pista, pista);
        novo->esquerda = novo->direita = NULL;
        return novo;
    }
    int cmp = strcmp(pista, raiz->pista);
    if (cmp < 0) raiz->esquerda = inserirPistaBST(raiz->esquerda, pista);
    else if (cmp > 0) raiz->direita = inserirPistaBST(raiz->direita, pista);
    return raiz;
}

void exibirPistasOrdenadas(NoPista *raiz) {
    if (raiz != NULL) {
        exibirPistasOrdenadas(raiz->esquerda);
        printf("- %s\n", raiz->pista);
        exibirPistasOrdenadas(raiz->direita);
    }
}

void contarPistasPorSuspeito(NoPista *raiz, const char *suspeito, int *contador) {
    if (raiz != NULL) {
        contarPistasPorSuspeito(raiz->esquerda, suspeito, contador);
        const char *sus = buscarSuspeito(raiz->pista);
        if (sus != NULL && strcmp(sus, suspeito) == 0) {
            (*contador)++;
        }
        contarPistasPorSuspeito(raiz->direita, suspeito, contador);
    }
}

void liberarPistas(NoPista *raiz) {
    if (raiz != NULL) {
        liberarPistas(raiz->esquerda);
        liberarPistas(raiz->direita);
        free(raiz);
    }
}

// ======================
// Exploração da Mansão
// ======================
void explorarMansao(Sala *raiz, NoPista **pistas) {
    Sala *atual = raiz;
    char escolha;

    printf("\n Bem-vindo(a) à Detective Quest - Julgamento Final!\n");
    printf("Você começará no Hall de Entrada.\n");

    while (1) {
        printf("\nVocê está em: %s\n", atual->nome);

        if (strlen(atual->pista) > 0) {
            *pistas = inserirPistaBST(*pistas, atual->pista);
            printf(" Você encontrou uma pista: \"%s\"\n", atual->pista);
            const char *sus = buscarSuspeito(atual->pista);
            if (sus) printf(" Suspeito relacionado: %s\n", sus);
        } else {
            printf(" Nenhuma pista neste cômodo.\n");
        }

        printf("\nPara onde deseja ir?\n");
        if (atual->esquerda) printf("[e] Esquerda -> %s\n", atual->esquerda->nome);
        if (atual->direita) printf("[d] Direita -> %s\n", atual->direita->nome);
        printf("[s] Sair e acusar suspeito\n");

        printf("Escolha: ");
        scanf(" %c", &escolha);

        if (escolha == 'e' && atual->esquerda) atual = atual->esquerda;
        else if (escolha == 'd' && atual->direita) atual = atual->direita;
        else if (escolha == 's') {
            printf("\n Exploração encerrada.\n");
            break;
        } else {
            printf("\n Opção inválida ou caminho inexistente.\n");
        }
    }
}

// ======================
// Programa Principal
// ======================
int main() {
    // ---- 1. Criação da Mansão (Árvore Binária) ----
    Sala *hall = criarSala("Hall de Entrada", "Pegada de sapato");
    hall->esquerda = criarSala("Sala de Estar", "Relógio quebrado");
    hall->direita = criarSala("Cozinha", "Xícara com batom");
    hall->esquerda->esquerda = criarSala("Jardim", "");
    hall->esquerda->direita = criarSala("Biblioteca", "Livro rasgado");
    hall->direita->esquerda = criarSala("Despensa", "Garrafa vazia");
    hall->direita->direita = criarSala("Sala de Jantar", "");
    hall->esquerda->direita->esquerda = criarSala("Porão", "Chave enferrujada");
    hall->direita->direita->direita = criarSala("Varanda", "Pegada de lama");

    // ---- 2. Criação da Hash de Pistas -> Suspeitos ----
    inserirHash("Pegada de sapato", "Sr. Black");
    inserirHash("Relógio quebrado", "Sra. White");
    inserirHash("Xícara com batom", "Sra. White");
    inserirHash("Livro rasgado", "Sr. Green");
    inserirHash("Garrafa vazia", "Sr. Black");
    inserirHash("Chave enferrujada", "Sr. Green");
    inserirHash("Pegada de lama", "Sr. Black");

    // ---- 3. Árvore BST para pistas coletadas ----
    NoPista *pistasColetadas = NULL;

    // ---- 4. Exploração da Mansão ----
    explorarMansao(hall, &pistasColetadas);

    // ---- 5. Exibir pistas e acusar ----
    printf("\n Pistas coletadas:\n");
    if (pistasColetadas == NULL) {
        printf("Nenhuma pista foi coletada.\n");
    } else {
        exibirPistasOrdenadas(pistasColetadas);
    }

    // ---- 6. Acusação ----
    char acusado[50];
    printf("\nDigite o nome do suspeito que deseja acusar: ");
    scanf(" %[^\n]", acusado);

    int contador = 0;
    contarPistasPorSuspeito(pistasColetadas, acusado, &contador);

    // ---- 7. Veredito ----
    printf("\n Resultado da investigação:\n");
    if (contador >= 2) {
        printf(" Acusação procedente! %s foi incriminado(a) por %d pistas.\n", acusado, contador);
    } else {
        printf(" Acusação falhou. Apenas %d pista(s) ligam %s ao crime.\n", contador, acusado);
    }

    // ---- 8. Liberação de memória ----
    liberarMansao(hall);
    liberarPistas(pistasColetadas);
    liberarHash();

    return 0;
}