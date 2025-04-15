#include <stdio.h>
#include <stdlib.h>

#define TAM 10

// Exibe o Tabuleiro
void exibirTabuleiro(int tabuleiro [TAM][TAM]) {
    printf("   ");
    for (char letra = 'A'; letra < 'J'; letra++){
        printf("%c ", letra);
    }
    printf("\n");

    for (int i = 0; i < TAM; i++){
        printf("%2d ", i + 1);
        for (int j = 0; j < TAM; j++){
            printf("%d ", tabuleiro[i][j]);
        }
        printf("\n");
    }
}

// Inicializa o tabuleiro com 0
void inicializarTabuleiro(int tabuleiro[TAM][TAM]) {
    for (int i = 0; i < 10; i++){
        for (int j = 0; j < 10; j++){
            tabuleiro[i][j] = 0;
        }
    }
}

// usado para aplicar o cone, a cruz e o octaedro
void aplicarHabilidade(int tabuleiro[TAM][TAM], int habilidade[][5], int tam, int origemLinha, int origemColuna) {
    int centro = tam / 2;   // tam é o tamanho da matriz da habilidade
    for (int i = 0; i < tam; i++) {
        for (int j = 0; j < tam; j++) {
            int linha = origemLinha - centro + i;   // origemLinha é a posição onde a habilidade será centralizada no tabuleiro
            int coluna = origemColuna - centro + j;   // origemColuna é a posição onde a habilidade será centralizada no tabuleiro
            if (linha >= 0 && linha < TAM && coluna >= 0 && coluna < TAM && habilidade[i][j] == 1) {
                tabuleiro[linha][coluna] = 5;   // para aparecer o número 5 onde for a área de efeito 1
            }
        }
    }
}

// Cone
void criarCone(int habilidade[5][5]) {
    int modelo[5][5] = {
        {0, 0, 1, 0, 0},
        {0, 1, 1, 1, 0},
        {1, 1, 1, 1, 1},
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0}
    };
    for (int i = 0; i < 5; i++)
        for (int j = 0; j < 5; j++)
            habilidade[i][j] = modelo[i][j];
}

// Cruz
void criarCruz(int hab[5][5]) {
    for (int i = 0; i < 5; i++)
        for (int j = 0; j < 5; j++)
            hab[i][j] = (i == 2 || j == 2) ? 1 : 0;
}

// Octaedro (pesquisei formas de deixar o código mais simples, e descobri o abs)
void criarOctaedro(int hab[5][5]) {
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            hab[i][j] = (abs(i - 1) + abs(j - 1) <= 1) ? 1 : 0;   // abs é o valor absoluto de um inteiro, ele é sempre positivo
}

// Função principal, exibe os "resultados"
int main() {
    int tabuleiro[TAM][TAM];
    int habilidade[5][5];

    inicializarTabuleiro(tabuleiro);

    criarCone(habilidade);
    aplicarHabilidade(tabuleiro, habilidade, 5, 2, 2);

    criarCruz(habilidade);
    aplicarHabilidade(tabuleiro, habilidade, 5, 5, 5);

    criarOctaedro(habilidade);
    aplicarHabilidade(tabuleiro, habilidade, 3, 8, 8);

    exibirTabuleiro(tabuleiro);

    return 0;
}