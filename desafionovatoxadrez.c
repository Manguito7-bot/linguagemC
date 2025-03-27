#include <stdio.h>

int main() {
    
    int bispo = 0, rainha = 0;

    printf("\nTORRE\n");
    // movimenta 5 casas a direita
    for (int movimentoT = 0; movimentoT < 5; movimentoT++)
    {
        printf("Direita\n");
    }


    printf("\nBISPO\n");
    // movimenta 5 casas para a diagonal superior á direita
    while (bispo < 5)
    {
        printf("Cima Direita\n");

        bispo++;
    }
    

    printf("\nRAINHA\n");
    // movimenta 8 casas para a esquerda
    do
    {
        printf("Esquerda\n");
        rainha++;
    } while (rainha < 8);
    
    return 0;
}