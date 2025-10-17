#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>


// Definindo struct

struct Territorio {
    char nome[30];
    char cor[10];
    int tropas;
};


// Protótipos

void cadastrarTerritorios(struct Territorio *mapa, int qtd);
void exibirMapa(struct Territorio *mapa, int qtd);
void atacar(struct Territorio *atacante, struct Territorio *defensor);
void liberarMemoria(struct Territorio *mapa);
void atribuirMissao(char *destino, char *missoes[], int totalMissoes);
int verificarMissao(char *missao, struct Territorio *mapa, int tamanho, char *corJogador);


// Cadastrar territórios

void cadastrarTerritorios(struct Territorio *mapa, int qtd) {
    for (int i = 0; i < qtd; i++) {
        printf("\n --- Cadastrando Territorio %d ---\n", i + 1);
        printf("Nome do territorio: ");
        scanf(" %29s", mapa[i].nome);

        printf("Cor do Exercito (ex: Azul, Verde): ");
        scanf(" %9s", mapa[i].cor);

        printf("Numero de tropas: ");
        scanf("%d", &mapa[i].tropas);
    }
}


// Exibir mapa

void exibirMapa(struct Territorio *mapa, int qtd) {
    printf("\n=======================================\n");
    printf("      MAPA DO MUNDO - ESTADO ATUAL\n");
    printf("=======================================\n");
    for (int i = 0; i < qtd; i++) {
        printf("\nTERRITORIO: %d\n", i + 1);
        printf("  - Nome: %s\n", mapa[i].nome);
        printf("  - Dominado por: Exercito %s\n", mapa[i].cor);
        printf("  - Tropas: %d\n", mapa[i].tropas);
    }
    printf("\n");
}


// Ataque

void atacar(struct Territorio *atacante, struct Territorio *defensor) {
    int dadoAtacante = (rand() % 6) + 1;
    int dadoDefensor = (rand() % 6) + 1;

    printf("\n=======================================\n");
    printf("          BATALHA EM ANDAMENTO\n");
    printf("=======================================\n");

    printf("%s (%s) atacando %s (%s)\n",
           atacante->nome, atacante->cor,
           defensor->nome, defensor->cor);

    printf("Dado do atacante: %d\n", dadoAtacante);
    printf("Dado do defensor: %d\n", dadoDefensor);

    if (dadoAtacante > dadoDefensor) {
        printf(">>> Atacante venceu a rodada!\n");
        defensor->tropas -= 1;

        if (defensor->tropas <= 0) {
            printf("\n================= CONQUISTA! =================\n");
            printf("O territorio %s foi conquistado pelo Exercito %s!\n",
                   defensor->nome, atacante->cor);
            defensor->tropas = 1;
            atacante->tropas -= 1;
            strcpy(defensor->cor, atacante->cor);
        }

    } else if (dadoDefensor > dadoAtacante) {
        printf(">>> Defensor venceu a rodada!\n");
        atacante->tropas -= 1;
    } else {
        printf(">>> Empate! Nenhum territorio perde tropas.\n");
    }

    printf("\n--- Resultado Atual ---\n");
    printf("%s (Tropas: %d)\n", atacante->nome, atacante->tropas);
    printf("%s (Tropas: %d)\n", defensor->nome, defensor->tropas);
}


// Liberar memória

void liberarMemoria(struct Territorio *mapa) {
    free(mapa);
}


// Atribuir missão

void atribuirMissao(char *destino, char *missoes[], int totalMissoes) {
    int indice = rand() % totalMissoes;
    strcpy(destino, missoes[indice]);
}


// Verificar missão

int verificarMissao(char *missao, struct Territorio *mapa, int tamanho, char *corJogador) {
    int territoriosDominados = 0;
    int tropasVermelhas = 0;

    for (int i = 0; i < tamanho; i++) {
        if (strcmp(mapa[i].cor, corJogador) == 0) {
            territoriosDominados++;
        }
        if (strcmp(mapa[i].cor, "Vermelho") == 0) {
            tropasVermelhas += mapa[i].tropas;
        }
    }

    if (strstr(missao, "Conquistar 3 territorios") != NULL) {
        if (territoriosDominados >= 3) return 1;
    }

    if (strstr(missao, "Eliminar todas as tropas vermelhas") != NULL) {
        if (tropasVermelhas == 0) return 1;
    }

    if (strstr(missao, "Dominar todo o mapa") != NULL) {
        if (territoriosDominados == tamanho) return 1;
    }

    return 0;
}


// Função principal

int main() {
    struct Territorio *mapa;
    int qtd;
    int opcao;

    srand(time(NULL));

    printf("=======================================\n");
    printf("  WAR ESTRUTURADO - CADASTRO INICIAL\n");
    printf("=======================================\n");

    printf("\nQuantos territorios deseja cadastrar? ");
    scanf("%d", &qtd);

    mapa = (struct Territorio*) malloc(qtd * sizeof(struct Territorio));
    if (mapa == NULL) {
        printf("Erro ao alocar memoria.\n");
        return 1;
    }

    cadastrarTerritorios(mapa, qtd);
    exibirMapa(mapa, qtd);

    
    // Sistema de Missões
    
    char *missoes[] = {
        "Conquistar 3 territorios",
        "Eliminar todas as tropas vermelhas",
        "Dominar todo o mapa",
        "Conquistar 2 territorios",
        "Manter pelo menos 5 tropas em um territorio"
    };
    int totalMissoes = sizeof(missoes) / sizeof(missoes[0]);

    // Alocar espaço dinâmico para armazenar missão do jogador
    char *missaoJogador = (char*) malloc(100 * sizeof(char));
    atribuirMissao(missaoJogador, missoes, totalMissoes);

    // Escolher cor do jogador
    char corJogador[10];
    printf("\nQual a sua cor de exercito? ");
    scanf(" %9s", corJogador);

    printf("\n>>> SUA MISSAO: %s\n", missaoJogador);

    
    // Loop de Ações
    
    do {
        printf("\n========== MENU ==========\n");
        printf("1 - Atacar\n");
        printf("2 - Verificar missao\n");
        printf("0 - Sair\n");
        printf("==========================\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        if (opcao == 1) {
            int idxAtacante, idxDefensor;

            printf("\nDigite o numero do territorio atacante: ");
            scanf("%d", &idxAtacante);
            printf("Digite o numero do territorio defensor: ");
            scanf("%d", &idxDefensor);

            idxAtacante--;
            idxDefensor--;

            if (idxAtacante < 0 || idxAtacante >= qtd || idxDefensor < 0 || idxDefensor >= qtd) {
                printf("Indice invalido!\n");
                continue;
            }
            if (idxAtacante == idxDefensor) {
                printf("Um territorio nao pode atacar a si mesmo!\n");
                continue;
            }
            if (strcmp(mapa[idxAtacante].cor, mapa[idxDefensor].cor) == 0) {
                printf("Voce nao pode atacar um territorio da mesma cor!\n");
                continue;
            }
            if (mapa[idxAtacante].tropas < 2) {
                printf("O atacante precisa ter pelo menos 2 tropas para atacar!\n");
                continue;
            }

            atacar(&mapa[idxAtacante], &mapa[idxDefensor]);
            exibirMapa(mapa, qtd);
        }

        else if (opcao == 2) {
            if (verificarMissao(missaoJogador, mapa, qtd, corJogador)) {
                printf("\n Missao concluida: %s\n", missaoJogador);
                printf("Voce venceu o jogo!\n");
                break;
            } else {
                printf("\n Missao ainda nao concluida.\n");
                printf("Missao: %s\n", missaoJogador);
            }
        }

    } while (opcao != 0);

    liberarMemoria(mapa);
    free(missaoJogador);

    printf("\nPrograma encerrado. Memoria liberada com sucesso.\n");
    return 0;
}