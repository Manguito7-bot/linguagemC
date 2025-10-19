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
Peca* acessarFrenteFila(Fila *f);

void inicializarPilha(Pilha *p);
int pilhaVazia(Pilha *p);
int pilhaCheia(Pilha *p);
void push(Pilha *p, Peca pec);
Peca pop(Pilha *p);
Peca* acessarTopoPilha(Pilha *p);

Peca gerarPeca(int id);
void exibirFila(Fila *f);
void exibirPilha(Pilha *p);
void trocarPecaTopoComFrente(Fila *f, Pilha *p);
void trocarBloco(Fila *f, Pilha *p);

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
        printf("1 - Jogar peca da frente da fila\n");
        printf("2 - Reservar peca (fila -> pilha)\n");
        printf("3 - Usar peca reservada (pilha)\n");
        printf("4 - Trocar peca da frente da fila com o topo da pilha\n");
        printf("5 - Trocar os 3 primeiros da fila com as 3 da pilha\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: {
                if (!filaVazia(&fila)) {
                    Peca jogada = dequeue(&fila);
                    printf("Peca jogada: [%c %d]\n", jogada.nome, jogada.id);
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

            case 4: {
                trocarPecaTopoComFrente(&fila, &pilha);
                break;
            }

            case 5: {
                trocarBloco(&fila, &pilha);
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
    if (filaCheia(f)) return;
    f->tras = (f->tras + 1) % TAM_FILA;
    f->itens[f->tras] = p;
    f->tamanho++;
}

Peca dequeue(Fila *f) {
    Peca removida = {'?', -1};
    if (filaVazia(f)) return removida;
    removida = f->itens[f->frente];
    f->frente = (f->frente + 1) % TAM_FILA;
    f->tamanho--;
    return removida;
}

Peca* acessarFrenteFila(Fila *f) {
    if (filaVazia(f)) return NULL;
    return &f->itens[f->frente];
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
    if (pilhaCheia(p)) return;
    p->itens[++p->topo] = pec;
}

Peca pop(Pilha *p) {
    Peca removida = {'?', -1};
    if (pilhaVazia(p)) return removida;
    removida = p->itens[p->topo--];
    return removida;
}

Peca* acessarTopoPilha(Pilha *p) {
    if (pilhaVazia(p)) return NULL;
    return &p->itens[p->topo];
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

// =========================
// Troca simples: topo da pilha com frente da fila
// =========================
void trocarPecaTopoComFrente(Fila *f, Pilha *p) {
    Peca *frente = acessarFrenteFila(f);
    Peca *topo = acessarTopoPilha(p);

    if (frente == NULL || topo == NULL) {
        printf("Nao ha pecas suficientes para trocar.\n");
        return;
    }

    Peca temp = *frente;
    *frente = *topo;
    *topo = temp;

    printf("Troca realizada entre frente da fila e topo da pilha.\n");
}

// =========================
// Troca em bloco (3 da fila <-> 3 da pilha)
// =========================
void trocarBloco(Fila *f, Pilha *p) {
    if (f->tamanho < 3 || p->topo + 1 < 3) {
        printf("Nao ha pecas suficientes para realizar troca em bloco.\n");
        return;
    }

    int idxFila = f->frente;
    for (int i = 0; i < 3; i++) {
        Peca temp = f->itens[idxFila];
        f->itens[idxFila] = p->itens[p->topo - i];
        p->itens[p->topo - i] = temp;
        idxFila = (idxFila + 1) % TAM_FILA;
    }

    printf("Troca realizada entre as 3 primeiras pecas da fila e as 3 da pilha.\n");
}