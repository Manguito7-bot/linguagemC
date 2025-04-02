#include <stdio.h>


// TORRE
void moverTorre(int casas) {
    if (casas > 0)
    {
        printf("Direita\n");
        moverTorre(casas - 1);
    }
}

// BISPO
void moverBispo(int casas) {
    if (casas > 0)
    {
        printf("Cima Direita\n");
        moverBispo(casas - 1);
    }
}

// RAINHA
void moverRainha(int casas) {
    if (casas > 0)
    {
        printf("Esquerda\n");
        moverRainha(casas - 1);
    }
    
}


int main() {
    printf("\nTORRE\n\n");
    moverTorre(5);
    printf("\nBISPO\n\n");
    moverBispo(5);
    printf("\nRAINHA\n\n");
    moverRainha(8);
    printf("\nCAVALO\n\n");

    // Essa foi feita com loop complexo
    
    //  for (int casasC = 0, casasD = 0; casasC < 1 && casasD < 1; casasC++, casasD++) {
    //  printf("Cima\n", casasC);
    //  printf("Cima\n", casasC);
    //  printf("Direita\n", casasD);
    //}
    
    // Essa com loop aninhado (apesar de não achar necessário o loop aninhado para esse tipo de exercício)

    // CAVALO
    for (int casasC = 0; casasC < 2; casasC++) {
        for (int casasD = 0; casasD < 1; casasD++) {
            printf("Cima\n");
        }
    }
    printf("Direita\n");

    return 0;
}