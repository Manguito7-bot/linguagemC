#include <stdio.h>
#include <string.h>

// Definindo struct
struct Territorio {
    char nome[30];
    char cor[10];
    int tropas;
};

int main() {
    // Vetor de 5 elementos do tipo Territorio
    struct Territorio territorios[5];
    
    // Título 
    printf("=======================================\n");
    printf("  WAR ESTRUTURADO - CADASTRO INICIAL\n");
    printf("=======================================\n");

    // Mensagem inicial
    printf("\nVamos cadastrar os 5 territorios iniciais do nosso mundo.\n");

    // Loop para preencher os dados dos 5 territorios
    for (int i = 0; i < 5; i++) {
        printf("\n--- Cadastrando Territorio %d ---\n", i + 1);

        printf("Nome do Territorio: ");
        scanf(" %29s", territorios[i].nome);

        printf("Cor do Exercito (ex: Azul, Verde): ");
        scanf(" %9s", territorios[i].cor);

        printf("Numero de Tropas: ");
        scanf("%d", &territorios[i].tropas);
    }
    
    // Mensagem confirmando que o cadastro foi realizado com sucesso
    printf("\nCadastro inicial concluido com sucesso!\n");

    printf("\n=======================================\n");
    printf("      MAPA DO MUNDO - ESTADO ATUAL\n");
    printf("=======================================\n\n");

    // Loop para a exibição dos dados cadastrados pelo usuário

    for (int i = 0; i < 5; i++) {
        printf("TERRITORIO: %d\n", i + 1);
        printf("  - Nome: %s\n", territorios[i].nome);
        printf("  - Dominado por: Exercito %s\n", territorios[i].cor);
        printf("  - Tropas: %d\n\n", territorios[i].tropas);
    }

    return 0;
}