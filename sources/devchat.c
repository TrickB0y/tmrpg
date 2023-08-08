#include <stdio.h>
#include "../headers/devchat.h"
#define STRING_MAX 20

void enviarMsg(char mensagem[])
{
    printf("TMRPG>> ");
    printf("%s\n", mensagem);
}

void enviarInt(int valor)
{
    printf("TMRPG>> ");
    printf("%d\n", valor);
}

char* receberString()
{
    static char string[STRING_MAX];
    printf("TMRPG>> ");
    scanf_s("%s", string, STRING_MAX);
    return string;
}
int receberInteiro()
{
    int inteiro;
    printf("TMRPG>> ");
    scanf_s("%d", &inteiro);
    return inteiro;
}
