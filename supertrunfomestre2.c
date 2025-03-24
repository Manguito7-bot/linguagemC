#include <stdio.h>

int main() {

    char pais[20] = "Brasil";
    char pais2[10] = "Canadá";
    char primeiroAtributo, segundoAtributo;
    int valorVencedor1, valorVencedor2, resultado, resultado1, resultado2, populacao1 = 25000, populacao2 = 600000, pontosTuristicos1 = 21, pontosTuristicos2 = 20, area1 = 1522, area2 = 600, pib1 = 490, pib2 = 300, densidadeDemografica1 = 182, densidadeDemografica2 = 290;

    printf("** SEJA BEM-VINDO AO JOGO **\n");
    printf("Escolha um atributo da Carta 1 (Brasil)\n");
    printf("A. População\n");
    printf("B. Pontos Túristicos\n");
    printf("C. Área\n");
    printf("D. PIB\n");
    printf("E. Densidade Demográfica\n");
    scanf(" %c", &primeiroAtributo);

    printf("Atributo escolhido do Brasil:\n");
    switch (primeiroAtributo)
    {
    case 'A':
    case 'a':
        printf("Você escolheu a População\n");
        printf("País 1: %s\n", pais);
        printf("País 2: %s\n", pais2);
        printf("População 1: %d\n", populacao1);
        printf("População 2: %d\n", populacao2);
        populacao1 > populacao2 ? printf("Brasil ganhou\n") : printf("Canadá ganhou\n");
        resultado1 = populacao1;
        resultado2 = populacao2;
        break;
    case 'B':
    case 'b':
        printf("Você escolheu os Pontos Túristicos\n");
        printf("País 1: %s\n", pais);
        printf("País 2: %s\n", pais2);
        printf("Pontos túristicos 1: %d\n", pontosTuristicos1);
        printf("Pontos túristicos 2: %d\n", pontosTuristicos2);
        pontosTuristicos1 > pontosTuristicos2 ? printf("Brasil ganhou\n") : printf("Canadá ganhou\n");
        resultado1 = pontosTuristicos1;
        resultado2 = pontosTuristicos2;
        break;
    case 'C':
    case 'c':
        printf("Você escolheu a Área\n");
        printf("País 1: %s\n", pais);
        printf("País 2: %s\n", pais2);
        printf("Área 1: %d\n", area1);
        printf("Área 2: %d\n", area2);
        area1 > area2 ? printf("Brasil ganhou\n") : printf("Canadá ganhou\n");
        resultado1 = area1;
        resultado2 = area2;
        break;
    case 'D':
    case 'd':
        printf("Você escolheu o PIB\n");
        printf("País 1: %s\n", pais);
        printf("País 2: %s\n", pais2);
        printf("PIB 1: %d\n", pib1);
        printf("PIB 2: %d\n", pib2);
        pib1 > pib2 ? printf("Brasil ganhou\n") : printf("Canadá ganhou\n");
        resultado1 = pib1;
        resultado2 = pib2;
        break;
    case 'E':
    case 'e':
        printf("Você escolheu a Densidade Demográfica\n");
        printf("País 1: %s\n", pais);
        printf("País 2: %s\n", pais2);
        printf("Densidade demográfica 1: %d\n", densidadeDemografica1);
        printf("Densidade demográfica 2: %d\n", densidadeDemografica2);
        densidadeDemografica1 < densidadeDemografica2 ? printf("Brasil ganhou\n") : printf("Canadá ganhou\n");
        resultado1 = densidadeDemografica1;
        resultado2 = densidadeDemografica2;
        break;
    default:
        printf("Opção inválida\n");
        return 1;
    }

    printf("Escolha o segundo atributo\n\n");
    printf("Escolha um atributo DIFERENTE do anterior (da Carta 2 (Canadá))\n");
    printf("A. População\n");
    printf("B. Pontos Túristicos\n");
    printf("C. Área\n");
    printf("D. PIB\n");
    printf("E. Densidade Demográfica\n");
    
    printf("Escolha a comparação do segundo atributo: \n");
    scanf(" %c", &segundoAtributo);

    printf("Atributo escolhido do Canadá:\n");

    if (primeiroAtributo == segundoAtributo)
    {
        printf("Você escolheu o mesmo atributo\n");
        return 1;
    } else {
        switch (segundoAtributo)
        {
        case 'A':
        case 'a':
            printf("Você escolheu a População\n");
            printf("País 1: %s\n", pais);
            printf("País 2: %s\n", pais2);
            printf("População 1: %d\n", populacao1);
            printf("População 2: %d\n", populacao2);
            populacao1 < populacao2 ? printf("Brasil ganhou\n") : printf("Canadá ganhou\n");
            resultado1 += populacao1;
            resultado2 += populacao2;
            break;
        case 'B':
        case 'b':
            printf("Você escolheu os Pontos Túristicos\n");
            printf("País 1: %s\n", pais);
            printf("País 2: %s\n", pais2);
            printf("Pontos túristicos 1: %d\n", pontosTuristicos1);
            printf("Pontos túristicos 2: %d\n", pontosTuristicos2);
            pontosTuristicos1 > pontosTuristicos2 ? printf("Brasil ganhou\n") : printf("Canadá ganhou\n");
            resultado1 += pontosTuristicos1;
            resultado2 += pontosTuristicos2;
            break;
        case 'C':
        case 'c':
            printf("Você escolheu a Área\n");
            printf("País 1: %s\n", pais);
            printf("País 2: %s\n", pais2);
            printf("Área 1: %d\n", area1);
            printf("Área 2: %d\n", area2);
            area1 < area2 ? printf("Brasil ganhou\n") : printf("Canadá ganhou\n");
            resultado1 += area1;
            resultado2 += area2;
            break;
        case 'D':
        case 'd':
            printf("Você escolheu o PIB\n");
            printf("País 1: %s\n", pais);
            printf("País 2: %s\n", pais2);
            printf("PIB 1: %d\n", pib1);
            printf("PIB 2: %d\n", pib2);
            pib1 < pib2 ? printf("Brasil ganhou\n") : printf("Canadá ganhou\n");
            resultado1 += pib1;
            resultado2 += pib2;
            break;
        case 'E':
        case 'e':
            printf("Você escolheu a Densidade Demográfica\n");
            printf("País 1: %s\n", pais);
            printf("País 2: %s\n", pais2);
            printf("Densidade demográfica 1: %d\n", densidadeDemografica1);
            printf("Densidade demográfica 2: %d\n", densidadeDemografica2);
            densidadeDemografica1 < densidadeDemografica2 ? printf("Brasil ganhou\n") : printf("Canadá ganhou\n");
            resultado1 += densidadeDemografica1;
            resultado2 += densidadeDemografica2;
            break;
        default:
            printf("Opção inválida\n");
            return 1;
        }
    }
    
    printf("\n");
    printf("Resultados Finais:\n\n");

    printf("Soma dos valores dos atributos escolhidos:\n");
    printf("Soma dos atributos para o Brasil: %d\n", resultado1);
    printf("Soma dos atributos para o Canadá: %d\n", resultado2);
    
    if (resultado1 > resultado2)
    {
        printf("Carta 1 venceu\n");
    } else if (resultado1 < resultado2)
    {
        printf("Carta 2 venceu\n");
    } else {
        printf("Empate\n");
    }

    return 0;
}