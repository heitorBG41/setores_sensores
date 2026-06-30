#include "menu.h"
#include <stdio.h>
#include <stdlib.h>

int menu_principal(void) {
    int opcao;
    printf("|-------------MENU SENSORES ------------|\n");
    printf("1. criar novo sensor\n");
    printf("2. registrar setor novo\n");
    printf("3. listar sensores\n");
    printf("4. listar setores\n");
    printf("5. menu de pesquisa\n");
    printf("6. menu de relatorios\n");
    printf("7. retirar o sensor de um setor\n");
    printf("8. menu de arquivos\n");
    printf("0. sair do programa\n");
    printf(":::: ");
    scanf("%i", &opcao);
    getchar();
    return opcao;
}

int menu_pesquisar() 
{
    int opcao;
    printf("------------MENU PESQUISA------------\n");
    printf("1.Pesquisar por tipo de sensor\n");
    printf("2.Pesquisar por descricao de setor\n");
    printf("0.Voltar para o menu principal\n");
    printf(":::: ");
    scanf("%i", &opcao);
    getchar();
    return opcao;
}

int menu_relatorios() 
{
    int opcao;
    printf("------------MENU RELATORIOS------------\n");
    printf("1.relatorio de sensores geral\n");
    printf("2.relatorio de sensores por tipo\n");
    printf("3.relatorio de setores\n");
    printf("4.relatorio de leituras por local\n");
    printf("5.relatorio de leituras por todos os locais\n");
    printf("6.relatorio de variacao de leitura por setor e por sensor\n");
    printf("7.relatorio de medias de leitura por sensor considerando todos os setores\n");
    printf("0.voltar para o menu principal\n");
    printf("::::");
    scanf("%i", &opcao);
    getchar();
    return opcao;
}

int menu_arquivos(void) 
{
    int opcao;
    printf("------------MENU ARQUIVOS------------\n");
    printf("1. exportar arquivo para binario\n");
    printf("2. exportar arquivo para .csv\n");
    printf("3. exportar arquivo para html\n");
    printf("4. importar arquivo binario\n");
    printf("0. voltar\n");
    printf(":::::");
    scanf("%i", &opcao);
    getchar();
    return opcao;
}