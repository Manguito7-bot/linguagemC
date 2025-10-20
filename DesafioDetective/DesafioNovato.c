#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estrutura que representa uma sala (nó da árvore)
typedef struct Sala {
    char nome[50];
    struct Sala *esquerda;
    struct Sala *direita;
} Sala;

// Função para criar uma nova sala
Sala* criarSala(const char *nome) {
    Sala *nova = (Sala*) malloc(sizeof(Sala));
    if (nova == NULL) {
        printf("Erro ao alocar memória para a sala.\n");
        exit(1);
    }
    strcpy(nova->nome, nome);
    nova->esquerda = NULL;
    nova->direita = NULL;
    return nova;
}

// Função para liberar a memória da árvore
void liberarArvore(Sala *raiz) {
    if (raiz != NULL) {
        liberarArvore(raiz->esquerda);
        liberarArvore(raiz->direita);
        free(raiz);
    }
}

// Função principal de exploração da mansão
void explorarMansao(Sala *raiz) {
    Sala *atual = raiz;
    char escolha;

    printf("\nBem-vindo(a) à Detective Quest!\n");
    printf("Você começará no Hall de entrada.\n");

    while (1) {
        printf("\nVocê está em: %s\n", atual->nome);

        // Verifica se chegou em um nó folha
        if (atual->esquerda == NULL && atual->direita == NULL) {
            printf("Você chegou a um cômodo sem saídas.\n");
            printf("Exploração encerrada!\n");
            break;
        }

        printf("Para onde deseja ir?\n");
        if (atual->esquerda != NULL) printf("[e] Esquerda -> %s\n", atual->esquerda->nome);
        if (atual->direita != NULL) printf("[d] Direita -> %s\n", atual->direita->nome);
        printf("[s] Sair do jogo\n");

        printf("Escolha: ");
        scanf(" %c", &escolha);

        if (escolha == 'e' && atual->esquerda != NULL) {
            atual = atual->esquerda;
        } 
        else if (escolha == 'd' && atual->direita != NULL) {
            atual = atual->direita;
        } 
        else if (escolha == 's') {
            printf("\nVocê decidiu sair da exploração.\n");
            break;
        } 
        else {
            printf("\nOpção inválida ou caminho inexistente.\n");
        }
    }
}

int main() {
    // Criação da árvore de forma manual
    // Hall de entrada
    Sala *hall = criarSala("Hall de entrada");

    // Segundo nível
    hall->esquerda = criarSala("Sala de estar");
    hall->direita = criarSala("Cozinha");

    // Terceiro nível
    hall->esquerda->esquerda = criarSala("Jardim");
    hall->esquerda->direita = criarSala("Biblioteca");

    hall->direita->esquerda = criarSala("Despensa");
    hall->direita->direita = criarSala("Sala de jantar");

    // Quarto nível (folhas)
    hall->esquerda->direita->esquerda = criarSala("Porão");
    hall->direita->direita->direita = criarSala("Varanda");

    // Exploração da mansão
    explorarMansao(hall);

    // Libera memória da árvore
    liberarArvore(hall);

    return 0;
}