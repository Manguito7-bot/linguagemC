#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAM_FILA 5

// Estrutura da peça
typedef struct {
    char nome;
    int id;
} Peca;

// Estrutura da fila
typedef struct {
    Peca itens[TAM_FILA];
    int frente;
    int tras;
    int tamanho;
} Fila;

// Protótipos
void inicializarFila(Fila *f);
int filaVazia(Fila *f);
int filaCheia(Fila *f);
void enqueue(Fila *f, Peca p);
Peca dequeue(Fila *f);
Peca gerarPeca(int id);
void exibirFila(Fila *f);

int main() {
    Fila fila;
    inicializarFila(&fila);
    srand(time(NULL));

    int opcao;
    int idPeca = 0;

    // Inicializa a fila com TAM_FILA peças
    for (int i = 0; i < TAM_FILA; i++) {
        enqueue(&fila, gerarPeca(idPeca++));
    }

    do {
        printf("\n=== TETRIS STACK - FILA DE PECAS FUTURAS ===\n");
        exibirFila(&fila);
        printf("\nOpcoes:\n");
        printf("1 - Jogar peca (dequeue)\n");
        printf("2 - Inserir nova peca (enqueue)\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                if (!filaVazia(&fila)) {
                    Peca jogada = dequeue(&fila);
                    printf("Peca jogada: [%c %d]\n", jogada.nome, jogada.id);
                } else {
                    printf("Fila vazia! Nao ha pecas para jogar.\n");
                }
                break;

            case 2:
                if (!filaCheia(&fila)) {
                    Peca nova = gerarPeca(idPeca++);
                    enqueue(&fila, nova);
                    printf("Nova peca inserida: [%c %d]\n", nova.nome, nova.id);
                } else {
                    printf("Fila cheia! Nao e possivel inserir nova peca.\n");
                }
                break;

            case 0:
                printf("Saindo do jogo...\n");
                break;

            default:
                printf("Opcao invalida!\n");
        }

    } while (opcao != 0);

    return 0;
}

// Função para inicializar a fila
void inicializarFila(Fila *f) {
    f->frente = 0;
    f->tras = -1;
    f->tamanho = 0;
}

// Verifica se a fila está vazia
int filaVazia(Fila *f) {
    return f->tamanho == 0;
}

// Verifica se a fila está cheia
int filaCheia(Fila *f) {
    return f->tamanho == TAM_FILA;
}

// Inserir no final da fila
void enqueue(Fila *f, Peca p) {
    if (filaCheia(f)) {
        printf("Erro: fila cheia\n");
        return;
    }
    f->tras = (f->tras + 1) % TAM_FILA;
    f->itens[f->tras] = p;
    f->tamanho++;
}

// Remover da frente da fila
Peca dequeue(Fila *f) {
    Peca removida;
    if (filaVazia(f)) {
        printf("Erro: fila vazia\n");
        removida.nome = '?';
        removida.id = -1;
        return removida;
    }
    removida = f->itens[f->frente];
    f->frente = (f->frente + 1) % TAM_FILA;
    f->tamanho--;
    return removida;
}

// Gera peça com nome aleatório e id sequencial
Peca gerarPeca(int id) {
    Peca nova;
    char tipos[] = {'I', 'O', 'T', 'L'};
    int index = rand() % 4;
    nova.nome = tipos[index];
    nova.id = id;
    return nova;
}

// Exibir a fila atual
void exibirFila(Fila *f) {
    printf("\nFila de pecas:\n");
    if (filaVazia(f)) {
        printf("[vazia]\n");
        return;
    }
    int idx = f->frente;
    for (int i = 0; i < f->tamanho; i++) {
        printf("[%c %d] ", f->itens[idx].nome, f->itens[idx].id);
        idx = (idx + 1) % TAM_FILA;
    }
    printf("\n");
}