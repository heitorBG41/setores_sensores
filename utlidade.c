#include "utilidade.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "variaveis.h"

void limpar_tela(void) 
{
    system("clear");
}

void botao_pause(void) 
{
    char pause;
    printf("pressione enter para continuar\n");
    scanf("%c", &pause);
}

void retirar_enter(string str) 
{
    str[strlen(str) - 1] = '\0';
}