#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAM_FILA 5
#define TAM_PILHA 3

// =========================
// Estrutura da peça
// =========================
typedef struct {
    char nome;
    int id;
} Peca;

// =========================
// Estrutura da fila circular
// =========================
typedef struct {
    Peca itens[TAM_FILA];
    int frente;
    int tras;
    int tamanho;
} Fila;

// =========================
// Estrutura da pilha
// =========================
typedef struct {
    Peca itens[TAM_PILHA];
    int topo;
} Pilha;

// =========================
// Protótipos
// =========================
void inicializarFila(Fila *f);
int filaVazia(Fila *f);
int filaCheia(Fila *f);
void enqueue(Fila *f, Peca p);
Peca dequeue(Fila *f);

void inicializarPilha(Pilha *p);
int pilhaVazia(Pilha *p);
int pilhaCheia(Pilha *p);
void push(Pilha *p, Peca pec);
Peca pop(Pilha *p);

Peca gerarPeca(int id);
void exibirFila(Fila *f);
void exibirPilha(Pilha *p);

// =========================
// Função principal
// =========================
int main() {
    Fila fila;
    Pilha pilha;
    int opcao;
    int idPeca = 0;

    srand(time(NULL));
    inicializarFila(&fila);
    inicializarPilha(&pilha);

    // Inicializa a fila com TAM_FILA peças
    for (int i = 0; i < TAM_FILA; i++) {
        enqueue(&fila, gerarPeca(idPeca++));
    }

    do {
        printf("\n=== TETRIS STACK - FILA E PILHA DE PECAS ===\n");
        exibirFila(&fila);
        exibirPilha(&pilha);

        printf("\nOpcoes:\n");
        printf("1 - Jogar peca\n");
        printf("2 - Reservar peca\n");
        printf("3 - Usar peca reservada\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: {
                if (!filaVazia(&fila)) {
                    Peca jogada = dequeue(&fila);
                    printf("Peca jogada: [%c %d]\n", jogada.nome, jogada.id);

                    // Gerar nova peça para manter fila cheia
                    enqueue(&fila, gerarPeca(idPeca++));
                } else {
                    printf("Fila vazia! Nao ha peca para jogar.\n");
                }
                break;
            }

            case 2: {
                if (!filaVazia(&fila)) {
                    if (!pilhaCheia(&pilha)) {
                        Peca reservada = dequeue(&fila);
                        push(&pilha, reservada);
                        printf("Peca reservada: [%c %d]\n", reservada.nome, reservada.id);

                        // Gerar nova peça para manter fila cheia
                        enqueue(&fila, gerarPeca(idPeca++));
                    } else {
                        printf("Pilha cheia! Nao e possivel reservar mais pecas.\n");
                    }
                } else {
                    printf("Fila vazia! Nao ha peca para reservar.\n");
                }
                break;
            }

            case 3: {
                if (!pilhaVazia(&pilha)) {
                    Peca usada = pop(&pilha);
                    printf("Peca usada da reserva: [%c %d]\n", usada.nome, usada.id);
                } else {
                    printf("Pilha vazia! Nao ha peca reservada para usar.\n");
                }
                break;
            }

            case 0:
                printf("Saindo do jogo...\n");
                break;

            default:
                printf("Opcao invalida!\n");
        }

    } while (opcao != 0);

    return 0;
}

// =========================
// Implementação da Fila
// =========================
void inicializarFila(Fila *f) {
    f->frente = 0;
    f->tras = -1;
    f->tamanho = 0;
}

int filaVazia(Fila *f) {
    return f->tamanho == 0;
}

int filaCheia(Fila *f) {
    return f->tamanho == TAM_FILA;
}

void enqueue(Fila *f, Peca p) {
    if (filaCheia(f)) {
        printf("Erro: fila cheia\n");
        return;
    }
    f->tras = (f->tras + 1) % TAM_FILA;
    f->itens[f->tras] = p;
    f->tamanho++;
}

Peca dequeue(Fila *f) {
    Peca removida = {'?', -1};
    if (filaVazia(f)) {
        printf("Erro: fila vazia\n");
        return removida;
    }
    removida = f->itens[f->frente];
    f->frente = (f->frente + 1) % TAM_FILA;
    f->tamanho--;
    return removida;
}

// =========================
// Implementação da Pilha
// =========================
void inicializarPilha(Pilha *p) {
    p->topo = -1;
}

int pilhaVazia(Pilha *p) {
    return p->topo == -1;
}

int pilhaCheia(Pilha *p) {
    return p->topo == TAM_PILHA - 1;
}

void push(Pilha *p, Peca pec) {
    if (pilhaCheia(p)) {
        printf("Erro: pilha cheia\n");
        return;
    }
    p->itens[++p->topo] = pec;
}

Peca pop(Pilha *p) {
    Peca removida = {'?', -1};
    if (pilhaVazia(p)) {
        printf("Erro: pilha vazia\n");
        return removida;
    }
    removida = p->itens[p->topo--];
    return removida;
}

// =========================
// Funções auxiliares
// =========================
Peca gerarPeca(int id) {
    Peca nova;
    char tipos[] = {'I', 'O', 'T', 'L'};
    int index = rand() % 4;
    nova.nome = tipos[index];
    nova.id = id;
    return nova;
}

void exibirFila(Fila *f) {
    printf("\nFila de pecas: ");
    if (filaVazia(f)) {
        printf("[vazia]");
    } else {
        int idx = f->frente;
        for (int i = 0; i < f->tamanho; i++) {
            printf("[%c %d] ", f->itens[idx].nome, f->itens[idx].id);
            idx = (idx + 1) % TAM_FILA;
        }
    }
    printf("\n");
}

void exibirPilha(Pilha *p) {
    printf("Pilha de reserva (Topo -> Base): ");
    if (pilhaVazia(p)) {
        printf("[vazia]");
    } else {
        for (int i = p->topo; i >= 0; i--) {
            printf("[%c %d] ", p->itens[i].nome, p->itens[i].id);
        }
    }
    printf("\n");
}