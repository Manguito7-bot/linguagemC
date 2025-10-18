#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_ITENS 10

// ==============================
// Definição da struct Item
// ==============================
// A struct representa um item na mochila, com nome, tipo e quantidade.
typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
} Item;

// ==============================
// Vetor global de itens e contador
// ==============================
Item mochila[MAX_ITENS];
int totalItens = 0;

// ==============================
// Função para inserir um novo item
// ==============================
void inserirItem() {
    if (totalItens >= MAX_ITENS) {
        printf("\n  Mochila cheia! Nao e possivel adicionar mais itens.\n");
        return;
    }

    Item novo;
    printf("\n=== CADASTRO DE ITEM ===\n");
    printf("Nome do item: ");
    scanf(" %29[^\n]", novo.nome); // Lê até 29 caracteres (evita overflow)
    printf("Tipo (arma, municao, cura...): ");
    scanf(" %19[^\n]", novo.tipo);
    printf("Quantidade: ");
    scanf("%d", &novo.quantidade);

    mochila[totalItens] = novo;
    totalItens++;

    printf("\n Item '%s' adicionado com sucesso!\n", novo.nome);
}

// ==============================
// Função para remover um item pelo nome
// ==============================
void removerItem() {
    if (totalItens == 0) {
        printf("\n  A mochila esta vazia.\n");
        return;
    }

    char nome[30];
    printf("\n=== REMOVER ITEM ===\n");
    printf("Informe o nome do item a remover: ");
    scanf(" %29[^\n]", nome);

    int encontrado = -1;
    for (int i = 0; i < totalItens; i++) {
        if (strcmp(mochila[i].nome, nome) == 0) {
            encontrado = i;
            break;
        }
    }

    if (encontrado != -1) {
        // Desloca os itens seguintes para preencher a posição removida
        for (int i = encontrado; i < totalItens - 1; i++) {
            mochila[i] = mochila[i + 1];
        }
        totalItens--;
        printf("\n  Item '%s' removido com sucesso!\n", nome);
    } else {
        printf("\n Item '%s' nao encontrado.\n", nome);
    }
}

// ==============================
// Função para listar todos os itens da mochila
// ==============================
void listarItens() {
    printf("\n=== ITENS NA MOCHILA ===\n");
    if (totalItens == 0) {
        printf("Nenhum item cadastrado.\n");
    } else {
        for (int i = 0; i < totalItens; i++) {
            printf("[%d] Nome: %s | Tipo: %s | Quantidade: %d\n", i + 1, mochila[i].nome, mochila[i].tipo, mochila[i].quantidade);
        }
    }
}

// ==============================
// Função para buscar um item pelo nome
// ==============================
void buscarItem() {
    if (totalItens == 0) {
        printf("\n  A mochila esta vazia.\n");
        return;
    }

    char nome[30];
    printf("\n=== BUSCAR ITEM ===\n");
    printf("Informe o nome do item: ");
    scanf(" %29[^\n]", nome);

    int encontrado = 0;
    for (int i = 0; i < totalItens; i++) {
        if (strcmp(mochila[i].nome, nome) == 0) {
            printf("\n Item encontrado:\n");
            printf("Nome: %s\n", mochila[i].nome);
            printf("Tipo: %s\n", mochila[i].tipo);
            printf("Quantidade: %d\n", mochila[i].quantidade);
            encontrado = 1;
            break;
        }
    }

    if (!encontrado) {
        printf("\n Item '%s' nao encontrado.\n", nome);
    }
}

// ==============================
// Função principal com menu
// ==============================
int main() {
    int opcao;

    do {
        printf("\n============================\n");
        printf("  SISTEMA DE INVENTARIO\n");
        printf("============================\n");
        printf("1. Cadastrar item\n");
        printf("2. Remover item\n");
        printf("3. Listar itens\n");
        printf("4. Buscar item\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        getchar(); // limpa buffer do teclado

        switch (opcao) {
            case 1:
                inserirItem();
                listarItens();
                break;
            case 2:
                removerItem();
                listarItens();
                break;
            case 3:
                listarItens();
                break;
            case 4:
                buscarItem();
                break;
            case 0:
                printf("\n Encerrando o programa...\n");
                break;
            default:
                printf("\n Opcao invalida. Tente novamente.\n");
        }
    } while (opcao != 0);

    return 0;
}