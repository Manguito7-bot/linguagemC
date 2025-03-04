#include <stdio.h>

int main(){

    char estado1, estado2;
    char codigo1[5], codigo2[5];
    char cidade1[50], cidade2[50];
    unsigned long long int populacao1, populacao2;
    int pontos_turisticos1, pontos_turisticos2;
    float area1, area2, pib1, pib2;
    float densidade_populacional1, densidade_populacional2;
    float pib_per_capita1, pib_per_capita2;
    float superPoder1, superPoder2;
    int compararPopulacao, compararArea, compararPib, compararPontos, compararDensidade, compararPoder, compararPibPer;


    printf("Carta 1: \n");

    printf("Estado: ");
    scanf(" %c", &estado1);

    printf("Digite o código: ");
    scanf("%s", codigo1);

    printf("Digite o nome da cidade: ");
    scanf(" %s", &cidade1);

    printf("Digite a populção da cidade: ");
    scanf("%llu", &populacao1);

    printf("Digite a área da cidade em km²: ");
    scanf("%f", &area1);

    printf("Digite o PIB da cidade : ");
    scanf("%f", &pib1);

    printf("Digite a quantidade de pontos túristicos na cidade: ");
    scanf("%d", &pontos_turisticos1);

    densidade_populacional1 = (float) populacao1 / area1;

    pib_per_capita1 = (float) pib1 / populacao1;

    superPoder1 = populacao1 + area1 + pib1 + pontos_turisticos1 + densidade_populacional1 + pib_per_capita1;
    

    printf("\n");

    printf("Dados da carta 1: \n");

    printf("Estado: %c\n", estado1);
    printf("Código: %s\n", codigo1);
    printf("Nome da cidade: %s\n", cidade1);
    printf("População: %llu\n", populacao1);
    printf("Área: %.2f km²\n", area1);
    printf("PIB: %.2f bilhões de reais \n", pib1);
    printf("Número de Pontos Turísticos: %d\n", pontos_turisticos1);
    printf("Densidade populacional: %.2f hab/km²\n", densidade_populacional1);
    printf("Pib Per Capita: %.2f reais\n", pib_per_capita1);
    printf("Super Poder: %.2f\n", superPoder1);
    printf("\n");


    printf("Carta 2: \n");

    printf("Estado: ");
    scanf(" %c", &estado2);

    printf("Digite o código: ");
    scanf("%s", codigo2);

    printf("Digite o nome da segunda cidade: ");
    scanf("%s", &cidade2);

    printf("Digite a populção da segunda cidade: ");
    scanf("%llu", &populacao2);

    printf("Digite a área da segunda cidade em km²: ");
    scanf("%f", &area2);

    printf("Digite o PIB da segunda cidade: ");
    scanf("%f", &pib2);

    printf("Digite a quantidade de pontos túristicos da segunda cidade: ");
    scanf("%d", &pontos_turisticos2);

    densidade_populacional2 = (float) populacao2 / area2;
    
    pib_per_capita2 = (float) pib2 / populacao2;

    superPoder2 = populacao2 + area2 + pib2 + pontos_turisticos2 + densidade_populacional2 + pib_per_capita2;

    printf("\n");
    
    printf("Dados da Carta 2: \n");

    printf("Segundo estado: %c\n", estado2);
    printf("Segundo Código: %s\n", codigo2);
    printf("Nome da segunda cidade: %s\n", cidade2);
    printf("População da segunda cidade: %llu\n", populacao2);
    printf("Área da segunda cidade: %.2f km²\n", area2);
    printf("PIB da segunda cidade: %.2f bilhões de reais\n", pib2);
    printf("Número de Pontos Turísticos da segunda cidade: %d\n", pontos_turisticos2);
    printf("Densidade populacional: %.2f hab/km²\n", densidade_populacional2);
    printf("Pib Per Capita: %.2f reais\n", pib_per_capita2);
    printf("Super Poder: %.2f\n", superPoder2);
    printf("\n");

    printf("Comparação de Cartas: \n");
    
    compararPopulacao = populacao1 > populacao2;
    compararArea = area1 > area2;
    compararPib = pib1 > pib2;
    compararPontos = pontos_turisticos1 > pontos_turisticos2;
    compararDensidade = densidade_populacional1 < densidade_populacional2;
    compararPibPer = pib_per_capita1 > pib_per_capita2;
    compararPoder = superPoder1 > superPoder2;

    printf("População:");
    printf("Área:");
    printf("Pib:");
    printf("Pontos Túristicos: ");
    printf("Densidade populacional: ");
    printf("Pib Per Capita: ");
    printf("Super Poder: ");

    return 0;
}