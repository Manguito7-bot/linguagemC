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

// Função para cadastrar territórios
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

// Função para exibir o estado atual do mapa
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

// Função de ataque entre territórios
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
        defensor->tropas -= 1;  // defensor perde 1 tropa

        // Verifica se defensor perdeu todas as tropas
        if (defensor->tropas <= 0) {
            printf("\n================= CONQUISTA! =================\n");
            printf("O territorio %s foi conquistado pelo Exercito %s!\n",
                   defensor->nome, atacante->cor);

            // Transfere 1 tropa do atacante para o novo território
            defensor->tropas = 1;
            atacante->tropas -= 1;

            // Muda a cor (domínio)
            strcpy(defensor->cor, atacante->cor);
        }

    } else if (dadoDefensor > dadoAtacante) {
        printf(">>> Defensor venceu a rodada!\n");
        atacante->tropas -= 1;  // atacante perde 1 tropa
    } else {
        printf(">>> Empate! Nenhum territorio perde tropas.\n");
    }

    printf("\n--- Resultado Atual ---\n");
    printf("%s (Tropas: %d)\n", atacante->nome, atacante->tropas);
    printf("%s (Tropas: %d)\n", defensor->nome, defensor->tropas);
}

// Função para liberar memória
void liberarMemoria(struct Territorio *mapa) {
    free(mapa);
}

// Função principal
int main() {
    struct Territorio *mapa;
    int qtd;
    int opcao;

    srand(time(NULL));  // Garante aleatoriedade nos dados

    printf("=======================================\n");
    printf("  WAR ESTRUTURADO - CADASTRO INICIAL\n");
    printf("=======================================\n");

    printf("\nQuantos territorios deseja cadastrar? ");
    scanf("%d", &qtd);

    // Usando alocação dinâmica de memória malloc
    mapa = (struct Territorio*) malloc(qtd * sizeof(struct Territorio));
    if (mapa == NULL) {
        printf("Erro ao alocar memoria.\n");
        return 1;
    }

    cadastrarTerritorios(mapa, qtd);
    exibirMapa(mapa, qtd);

    // Loop de ataques
    do {
        printf("\nDeseja realizar um ataque? (1 - Sim / 0 - Nao): ");
        scanf("%d", &opcao);

        if (opcao == 1) {
            int idxAtacante, idxDefensor;

            printf("\nDigite o numero do territorio atacante: ");
            scanf("%d", &idxAtacante);
            printf("Digite o numero do territorio defensor: ");
            scanf("%d", &idxDefensor);

            // Ajustando para índice de vetor
            idxAtacante--;
            idxDefensor--;

            // Validação básica
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

    } while (opcao != 0);

    liberarMemoria(mapa);

    printf("\nPrograma encerrado. Memoria liberada com sucesso.\n");
    return 0;
}