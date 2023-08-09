#include <stdio.h>
#include <string.h>
#include "../headers/game.h"
#include "../headers/devchat.h"
#define BAG_SIZE 11
#define ALL_ITEMS_QUANTITY 6
#define ITEM_NAME_LENGTH 10
#define NO_ITEM 0
#define STACKABLE_ITEM 666666
#define NOT_STACKABLE_ITEM 696969
#define STACK_MAX 2000
#define ITEM_WEAPON 300
#define ITEM_HEAD 266
#define ITEM_CHEST 444
#define ITEM_LEGS 777
#define ITEM_BOOT 357
#define ITEM_NECK 656
#define ITEM_RING 808
#define COMMAND_LENG 20
#define MESSAGE_LENG 50

static char gamerunning;
static int rightHand;
static int leftHand;
static int head;
static int chest;
static int legs;
static int feets;
static int neck;
static int fingerR;
static int fingerL;
static int quantHandR;
static int quantHandL;

static int bag[BAG_SIZE];
static int quantStrg[BAG_SIZE];

static char itensNames[ALL_ITEMS_QUANTITY][ITEM_NAME_LENGTH] = 
{
    "NOTHING","espada" , "escudo" , "capacete" , "peitoral" , "bota" 
};
static int itensSpecification[ALL_ITEMS_QUANTITY] = 
{
    NO_ITEM , NOT_STACKABLE_ITEM , NOT_STACKABLE_ITEM , NOT_STACKABLE_ITEM , NOT_STACKABLE_ITEM , NOT_STACKABLE_ITEM
};
static int itemType[ALL_ITEMS_QUANTITY] =
{
    NO_ITEM , ITEM_WEAPON , ITEM_WEAPON , ITEM_HEAD , ITEM_CHEST , ITEM_BOOT
};

void initEmptyBag()
{
    for(int i = 0; i < BAG_SIZE; i++)
    {
        bag[i] = NO_ITEM;
        quantStrg[i] = NO_ITEM;
    }
}

void startgame()
{
    gamerunning = 1;
    initEmptyBag();
    while (gamerunning)
    {
        getcommand();
    }
}

void stopgame()
{
    gamerunning = 0;
}

void give(char equip, int itemCode, int quantity)
{
    if (itensSpecification[itemCode] == NOT_STACKABLE_ITEM)
    {
        switch(equip)
        {
            case 'a':
                rightHand = itemCode;
                quantHandR = NOT_STACKABLE_ITEM;
                break;

            case 'b':
                leftHand = itemCode;
                quantHandL = NOT_STACKABLE_ITEM;
                break;

            case 'c':
                head = itemCode;
                break;

            case 'd':
                chest = itemCode;
                break;

            case 'e':
                legs = itemCode;
                break;

            case 'f':
                feets = itemCode;
                break;

            case 'g':
                neck = itemCode;
                break;

            case 'h':
                fingerR = itemCode;
                break;

            case 'i':
                fingerL = itemCode;
                break;
        }
    }
    else if (itensSpecification[itemCode] == STACKABLE_ITEM)
    {
        if (equip == 'a')
        {
            if (quantHandR == 0)
            {
                rightHand = itemCode;
                quantHandR = quantity;
            }
            else if (quantity + quantHandR < STACK_MAX)
            {
                rightHand = itemCode;
                quantHandR += quantity;
            }
            else if (quantity + quantHandR > STACK_MAX)
            {
                rightHand = itemCode;
                quantHandR = STACK_MAX;
            }
        }
        else if(equip == 'b')
        {
            if (quantHandL == 0)
            {
                leftHand = itemCode;
                quantHandL = quantity;
            }
            else if (quantity + quantHandL < STACK_MAX)
            {
                leftHand = itemCode;
                quantHandL += quantity;
            }
            else if (quantity + quantHandL > STACK_MAX)
            {
                leftHand = itemCode;
                quantHandL = STACK_MAX;
            }
        }
    }
}

void itemWithdraw(int bagSlot, char equip, int quantity)
{

}

void itemDeposit(int bagSlot, char equip, int quantity)
{

}

void getcommand()
{
    char* commando = receberString();
    if (strcmp(commando, "/quit") == 0)
    {
        stopgame();
    }
    else if (strcmp(commando,"/give") == 0)
    {
        enviarMsg("digite id do item:");
        int itemId;
        itemId = receberInteiro();
        if (itemId > 0 && itemId < ALL_ITEMS_QUANTITY)
        {
            if (itensSpecification[itemId] == NOT_STACKABLE_ITEM)
            {
                int itemTipo = itemType[itemId];
                int equipDestiny;
                switch (itemTipo)
                {
                    case ITEM_WEAPON:
                        enviarMsg("Escolha aonde o item sera equipado:");
                        enviarMsg("[1]Mao direita.  [2]Mao esquerda.");
                        equipDestiny = receberInteiro();
                        if (equipDestiny == 1)
                        {
                            if (rightHand == 0)
                            {
                                give('a', itemId, NOT_STACKABLE_ITEM);
                                enviarMsg("Item enviado a mao direita.");
                            }
                            else enviarMsg("Erro! mao ocupada. nenhum item foi enviado.");

                        }
                        else if (equipDestiny == 2)
                        {
                            if (leftHand == 0)
                            {
                                give('b', itemId, NOT_STACKABLE_ITEM);
                                enviarMsg("Item enviado a mao esquerda.");
                            }
                            else enviarMsg("Erro! mao ocupada. nenhum item foi enviado.");
                        }
                        else
                        {
                            enviarMsg("Erro! opcao desconhecida. nenhum item foi enviado.");
                        }
                        break;

                    case ITEM_HEAD:
                        enviarMsg("Escolha aonde o item sera equipado:");
                        enviarMsg("[1]Mao direita.  [2]Mao esquerda.");
                        enviarMsg("[3]Cabeca.");
                        equipDestiny = receberInteiro();
                        if (equipDestiny == 1)
                        {
                            if (rightHand == 0)
                            {
                                give('a', itemId, NOT_STACKABLE_ITEM);
                                enviarMsg("Item enviado a mao direita.");
                            }
                            else enviarMsg("Erro! mao ocupada. nenhum item foi enviado.");
                        }
                        else if (equipDestiny == 2)
                        {
                            if (leftHand == 0)
                            {
                                give('b', itemId, NOT_STACKABLE_ITEM);
                                enviarMsg("Item enviado a mao esquerda.");
                            }
                            else enviarMsg("Erro! mao ocupada. nenhum item foi enviado.");
                        }
                        else if (equipDestiny == 3)
                        {
                            if (head == 0)
                            {
                                give('c', itemId, NOT_STACKABLE_ITEM);
                                enviarMsg("O item foi equipado na cabeca.");
                            }
                            else enviarMsg("Erro! já a algo equipado na cabeca. nenhum item foi enviado.");
                        }
                        else
                        {
                            enviarMsg("Erro! opcao desconhecida. nenhum item foi enviado.");
                        }
                        break;

                    case ITEM_CHEST:
                        enviarMsg("Escolha aonde o item sera equipado:");
                        enviarMsg("[1]Mao direita.  [2]Mao esquerda.");
                        enviarMsg("[3]Peito.");
                        equipDestiny = receberInteiro();
                        if (equipDestiny == 1)
                        {
                            if (rightHand == 0)
                            {
                                give('a', itemId, NOT_STACKABLE_ITEM);
                                enviarMsg("Item enviado a mao direita.");
                            }
                            else enviarMsg("Erro! mao ocupada. nenhum item foi enviado.");
                        }
                        else if (equipDestiny == 2)
                        {
                            if (leftHand == 0)
                            {
                                give('b', itemId, NOT_STACKABLE_ITEM);
                                enviarMsg("Item enviado a mao esquerda.");
                            }
                            else enviarMsg("Erro! mao ocupada. nenhum item foi enviado.");
                        }
                        else if (equipDestiny == 3)
                        {
                            if (chest == 0)
                            {
                                give('d', itemId, NOT_STACKABLE_ITEM);
                                enviarMsg("O item foi equipado no peito.");
                            }
                            else enviarMsg("Erro! já a algo equipado no peito. nenhum item foi enviado.");
                        }
                        else
                        {
                            enviarMsg("Erro! opcao desconhecida. nenhum item foi enviado.");
                        }
                        break;
                        
                    case ITEM_LEGS:
                        enviarMsg("Escolha aonde o item sera equipado:");
                        enviarMsg("[1]Mao direita.  [2]Mao esquerda.");
                        enviarMsg("[3]Pernas.");
                        equipDestiny = receberInteiro();
                        if (equipDestiny == 1)
                        {
                            if (rightHand == 0)
                            {
                                give('a', itemId, NOT_STACKABLE_ITEM);
                                enviarMsg("Item enviado a mao direita.");
                            }
                            else enviarMsg("Erro! mao ocupada. nenhum item foi enviado.");
                        }
                        else if (equipDestiny == 2)
                        {
                            if (leftHand == 0)
                            {
                                give('b', itemId, NOT_STACKABLE_ITEM);
                                enviarMsg("Item enviado a mao esquerda.");
                            }
                            else enviarMsg("Erro! mao ocupada. nenhum item foi enviado.");
                        }
                        else if (equipDestiny == 3)
                        {
                            if (legs == 0)
                            {
                                give('e', itemId, NOT_STACKABLE_ITEM);
                                enviarMsg("O item foi equipado nas pernas.");
                            }
                            else enviarMsg("Erro! já a algo equipado nas pernas. nenhum item foi enviado.");
                        }
                        else
                        {
                            enviarMsg("Erro! opcao desconhecida. nenhum item foi enviado.");
                        }
                        break;
                        
                    case ITEM_BOOT:
                        enviarMsg("Escolha aonde o item sera equipado:");
                        enviarMsg("[1]Mao direita.  [2]Mao esquerda.");
                        enviarMsg("[3]Pes.");
                        equipDestiny = receberInteiro();
                        if (equipDestiny == 1)
                        {
                            if (rightHand == 0)
                            {
                                give('a', itemId, NOT_STACKABLE_ITEM);
                                enviarMsg("Item enviado a mao direita.");
                            }
                            else enviarMsg("Erro! mao ocupada. nenhum item foi enviado.");
                        }
                        else if (equipDestiny == 2)
                        {
                            if (leftHand == 0)
                            {
                                give('b', itemId, NOT_STACKABLE_ITEM);
                                enviarMsg("Item enviado a mao esquerda.");
                            }
                            else enviarMsg("Erro! mao ocupada. nenhum item foi enviado.");
                        }
                        else if (equipDestiny == 3)
                        {
                            if (feets == 0)
                            {
                                give('f', itemId, NOT_STACKABLE_ITEM);
                                enviarMsg("O item foi equipado nos pes.");
                            }
                            else enviarMsg("Erro! já a algo equipado nos pes. nenhum item foi enviado.");
                        }
                        else
                        {
                            enviarMsg("Erro! opcao desconhecida. nenhum item foi enviado.");
                        }
                        break;
                        
                    case ITEM_NECK:
                        enviarMsg("Escolha aonde o item sera equipado:");
                        enviarMsg("[1]Mao direita.  [2]Mao esquerda.");
                        enviarMsg("[3]Pescoco.");
                        equipDestiny = receberInteiro();
                        if (equipDestiny == 1)
                        {
                            if (rightHand == 0)
                            {
                                give('a', itemId, NOT_STACKABLE_ITEM);
                                enviarMsg("Item enviado a mao direita.");
                            }
                            else enviarMsg("Erro! mao ocupada. nenhum item foi enviado.");
                        }
                        else if (equipDestiny == 2)
                        {
                            if (leftHand == 0)
                            {
                                give('b', itemId, NOT_STACKABLE_ITEM);
                                enviarMsg("Item enviado a mao esquerda.");
                            }
                            else enviarMsg("Erro! mao ocupada. nenhum item foi enviado.");
                        }
                        else if (equipDestiny == 3)
                        {
                            if (neck == 0)
                            {
                                give('g', itemId, NOT_STACKABLE_ITEM);
                                enviarMsg("O item foi equipado no pescoco.");
                            }
                            else enviarMsg("Erro! já a algo equipado no pescoco. nenhum item foi enviado.");
                        }
                        else
                        {
                            enviarMsg("Erro! opcao desconhecida. nenhum item foi enviado.");
                        }
                        break;
                        
                    case ITEM_RING:
                        enviarMsg("Escolha aonde o item sera equipado:");
                        enviarMsg("[1]Mao direita.  [2]Mao esquerda.");
                        enviarMsg("[3]Anel mao direita.");
                        enviarMsg("[4]Anel mao esquerda.");
                        equipDestiny = receberInteiro();
                        if (equipDestiny == 1)
                        {
                            if (rightHand == 0)
                            {
                                give('a', itemId, NOT_STACKABLE_ITEM);
                                enviarMsg("Item enviado a mao direita.");
                            }
                            else enviarMsg("Erro! mao ocupada. nenhum item foi enviado.");
                        }
                        else if (equipDestiny == 2)
                        {
                            if (leftHand == 0)
                            {
                                give('b', itemId, NOT_STACKABLE_ITEM);
                                enviarMsg("Item enviado a mao esquerda.");
                            }
                            else enviarMsg("Erro! mao ocupada. nenhum item foi enviado.");
                        }
                        else if (equipDestiny == 3)
                        {
                            if (fingerR == 0)
                            {
                                give('h', itemId, NOT_STACKABLE_ITEM);
                                enviarMsg("O anel foi equipado na mao direita.");
                            }
                            else enviarMsg("Erro! ja ha um anel em uso na mao direita. nenhum item foi enviado.");
                        }
                        else if (equipDestiny == 4)
                        {
                            if (fingerL == 0)
                            {
                                give('i', itemId, NOT_STACKABLE_ITEM);
                                enviarMsg("O anel foi equipado na mao esquerda.");
                            }
                            else enviarMsg("Erro! ja ha um anel em uso na mao esquerda. nenhum item foi enviado.");
                        }
                        else
                        {
                            enviarMsg("Erro! opcao desconhecida. nenhum item foi enviado.");
                        }
                        break;
    
                }
                
            }
            else if (itensSpecification[itemId] == STACKABLE_ITEM)
            {
                int quantidade;
                enviarMsg("Diga a quantidade. Max 2000:");
                quantidade = receberInteiro();
                if (quantidade > 0 && quantidade <= STACK_MAX)
                {
                    int equipDestiny;
                    enviarMsg("Escolha aonde o item sera equipado.");
                    enviarMsg("[1]Mao direita.  [2]Mao esquerda.");
                    equipDestiny = receberInteiro();
                    if (equipDestiny == 1)
                    {
                        if (rightHand == 0 || rightHand == itemId)
                        {
                            give('a', itemId, quantidade);
                            enviarMsg("Item enviado para mao direita.");
                            enviarMsg("Caso a quantidade for excedida o valor final sera 2000.");
                        }
                        else enviarMsg("Erro! a mao esta ocupada com um item diferente. nenhum item foi enviado.");
                    }
                    else if (equipDestiny == 2)
                    {
                        if (leftHand == 0 || leftHand == itemId)
                        {
                            give('b', itemId, quantidade);
                            enviarMsg("Item enviado para mao esquerda.");
                            enviarMsg("Caso a quantidade for excedida o valor final sera 2000.");
                        }
                        else enviarMsg("Erro! a mao esta ocupada com um item diferente. nenhum item foi enviado.");
                    }
                    else enviarMsg("Erro! opcao desconhecida. nenhum item foi enviado.");
                }
                else enviarMsg("Erro! valor invalido. nenhum item foi enviado.");
            }
        }
        else enviarMsg("item desconhecido.");
    }
    else if (strcmp(commando, "!maos") == 0)
    {
        if (rightHand == NO_ITEM)
        {
            enviarMsg("mao direita vazia!");
        }
        else
        {
            char item_msg[MESSAGE_LENG] = "esta equipado na mao direita:";
            sprintf(item_msg , "%s %s" , item_msg , itensNames[rightHand]);
            enviarMsg(item_msg);
            if (itensSpecification[rightHand] != NOT_STACKABLE_ITEM && itensSpecification[rightHand] == STACKABLE_ITEM)
            {
                char quant_msg[MESSAGE_LENG] = "quantidade:";
                sprintf(quant_msg, "%s %d", quant_msg , quantHandR);
                enviarMsg(quant_msg);
            }
        }
        if (leftHand == NO_ITEM)
        {
            enviarMsg("mao esquerda vazia!");
        }
        else
        {
            char item_msg[MESSAGE_LENG] = "esta equipado na mao esquerda:";
            sprintf(item_msg, "%s %s" , item_msg , itensNames[leftHand]);
            enviarMsg(item_msg);
            if (itensSpecification[leftHand] != NOT_STACKABLE_ITEM && itensSpecification[leftHand] == STACKABLE_ITEM)
            {
                char quant_msg[MESSAGE_LENG] = "quantidade:";
                sprintf(quant_msg, "%s %d" , quant_msg , quantHandL);
                enviarMsg(quant_msg);
            }
        }

    }
    else if (strcmp(commando, "!equipamento") == 0)
    {
        if (head == NO_ITEM)
        {
            enviarMsg("nada na cabeca!");
        }
        else
        {
            char item_msg[MESSAGE_LENG] = "esta equipado na cabeca:";
            sprintf(item_msg , "%s %s" , item_msg , itensNames[head]);
            enviarMsg(item_msg);
        }
        if (chest == NO_ITEM)
        {
            enviarMsg("nada no peito!");
        }
        else
        {
            char item_msg[MESSAGE_LENG] = "esta equipado no peito:";
            sprintf(item_msg, "%s %s" , item_msg , itensNames[chest]);
            enviarMsg(item_msg);
        }
        if (legs == NO_ITEM)
        {
            enviarMsg("nada nas pernas!");
        }
        else
        {
            char item_msg[MESSAGE_LENG] = "esta equipado nas pernas:";
            sprintf(item_msg, "%s %s" , item_msg , itensNames[legs]);
            enviarMsg(item_msg);
        }
        if (feets == NO_ITEM)
        {
            enviarMsg("nada nos pes!");
        }
        else
        {
            char item_msg[MESSAGE_LENG] = "esta equipado nos pes:";
            sprintf(item_msg, "%s %s" , item_msg , itensNames[feets]);
            enviarMsg(item_msg);
        }
        if (neck == NO_ITEM)
        {
            enviarMsg("nada no pescoco!");
        }
        else
        {
            char item_msg[MESSAGE_LENG] = "esta equipado no pescoco:";
            sprintf(item_msg, "%s %s" , item_msg , itensNames[neck]);
            enviarMsg(item_msg);
        }
        if (fingerR == NO_ITEM)
        {
            enviarMsg("nenhum anel equipado na mao direita!");
        }
        else
        {
            char item_msg[MESSAGE_LENG] = "anel equipado na mao direita:";
            sprintf(item_msg, "%s %s" , item_msg , itensNames[fingerR]);
            enviarMsg(item_msg);
        }
        if (fingerL == NO_ITEM)
        {
            enviarMsg("nenhum anel equipado na mao esquerda!");
        }
        else
        {
            char item_msg[MESSAGE_LENG] = "anel equipado na mao esquerda:";
            sprintf(item_msg, "%s %s" , item_msg , itensNames[fingerL]);
            enviarMsg(item_msg);
        }
    }
    else if (strcmp(commando, "!equipar") == 0)
    {
        if (itemType[rightHand] == NO_ITEM || itemType[rightHand] == ITEM_WEAPON && itemType[leftHand] == NO_ITEM || itemType[leftHand] == ITEM_WEAPON)
        {
            enviarMsg("nada nas mao para equipar!");
        }
        else
        {
            if (rightHand != 0)
            {
                char equip_msg[MESSAGE_LENG];
                switch(itemType[rightHand])
                {
                    case NO_ITEM:
                        enviarMsg("nao ha itens na mao direita.");
                        break;

                    case ITEM_WEAPON:
                        enviarMsg("o item da mao direita nao pode ser enviado.");
                        break;

                    case ITEM_HEAD:
                        sprintf(equip_msg , "[1]mao direita. equipar: %s na cabeca?" , itensNames[rightHand]);
                        enviarMsg(equip_msg);
                        break;

                    case ITEM_CHEST:
                        sprintf(equip_msg , "[1]mao direita. equipar: %s no peito?" , itensNames[rightHand]);
                        enviarMsg(equip_msg);
                        break;

                    case ITEM_LEGS:
                        sprintf(equip_msg , "[1]mao direita. equipar: %s nas pernas?" , itensNames[rightHand]);
                        enviarMsg(equip_msg);
                        break;

                    case ITEM_BOOT:
                        sprintf(equip_msg , "[1]mao direita. equipar: %s nos pes?" , itensNames[rightHand]);
                        enviarMsg(equip_msg);
                        break;

                    case ITEM_NECK:
                        sprintf(equip_msg , "[1]mao direita. equipar: %s no pescoco?" , itensNames[rightHand]);
                        enviarMsg(equip_msg);
                        break;

                    case ITEM_RING:
                        sprintf(equip_msg , "[1]mao direita. equipar: %s nos dedos da mao?" , itensNames[rightHand]);
                        enviarMsg(equip_msg);
                        break;
                };
            }
            if (leftHand != 0)
            {
                char equip_msg[MESSAGE_LENG];
                switch (itemType[leftHand])
                {
                    case NO_ITEM:
                        enviarMsg("nao ha itens na mao esquerda.");
                        break;

                    case ITEM_WEAPON:
                        enviarMsg("o item da mao direita nao pode ser enviado.");
                        break;

                    case ITEM_HEAD:
                        sprintf(equip_msg , "[2]mao esquerda. equipar: %s na cabeca?" , itensNames[leftHand]);
                        enviarMsg(equip_msg);
                        break;

                    case ITEM_CHEST:
                        sprintf(equip_msg , "[2]mao esquerda. equipar: %s no peito?" , itensNames[leftHand]);
                        enviarMsg(equip_msg);
                        break;

                    case ITEM_LEGS:
                        sprintf(equip_msg , "[2]mao esquerda. equipar: %s nas pernas?" , itensNames[leftHand]);
                        enviarMsg(equip_msg);
                        break;

                    case ITEM_BOOT:
                        sprintf(equip_msg , "[2]mao esquerda. equipar: %s nos pes?" , itensNames[leftHand]);
                        enviarMsg(equip_msg);
                        break;

                    case ITEM_NECK:
                        sprintf(equip_msg , "[2]mao esquerda. equipar: %s no pescoco?" , itensNames[leftHand]);
                        enviarMsg(equip_msg);
                        break;

                    case ITEM_RING:
                        sprintf(equip_msg , "[2]mao esquerda. equipar: %s nos dedos da mao?" , itensNames[leftHand]);
                        enviarMsg(equip_msg);
                        break;
                }
            }
            int opcao_escolhida = receberInteiro();
            if (opcao_escolhida == 1)
            {
                switch (itemType[rightHand])
                {
                    case NO_ITEM:
                        enviarMsg("nao prestou atencao? NAO TEM NADA AI!");
                        break;

                    case ITEM_WEAPON:
                        enviarMsg("eu falei! NAO DA PRA EQUIPAR ESSE ITEM!");
                        break;

                    case ITEM_HEAD:
                        if (head != NO_ITEM)
                        {
                            enviarMsg("nao foi possivel equipar item porque ja ha algo equipado");
                        }
                        else
                        {
                            head = rightHand;
                            rightHand = NO_ITEM;
                            enviarMsg("item equipado na cabeca.");
                        }
                        break;

                    case ITEM_CHEST:
                        if (chest != NO_ITEM)
                        {
                            enviarMsg("nao foi possivel equipar item porque ja ha algo equipado");
                        }
                        else
                        {
                            chest = rightHand;
                            rightHand = NO_ITEM;
                            enviarMsg("item equipado no peito.");
                        }
                        break;

                    case ITEM_LEGS:
                        if (legs != NO_ITEM)
                        {
                            enviarMsg("nao foi possivel equipar item porque ja ha algo equipado");
                        }
                        else
                        {
                            legs = rightHand;
                            rightHand = NO_ITEM;
                            enviarMsg("item equipado nas pernas.");
                        }
                        break;

                    case ITEM_BOOT:
                        if (feets != NO_ITEM)
                        {
                            enviarMsg("nao foi possivel equipar item porque ja ha algo equipado");
                        }
                        else
                        {
                            feets = rightHand;
                            rightHand = NO_ITEM;
                            enviarMsg("item equipado nos pes.");
                        }
                        break;

                    case ITEM_NECK:
                        if (neck != NO_ITEM)
                        {
                            enviarMsg("nao foi possivel equipar item porque ja ha algo equipado");
                        }
                        else
                        {
                            neck = rightHand;
                            rightHand = NO_ITEM;
                            enviarMsg("item equipado no pescoco");
                        }
                        break;
                    
                    case ITEM_RING:
                        enviarMsg("selecione: [1]dedo mao direita. [2]dedo mao esquerda.");
                        int anel_slct = receberInteiro();
                        if (anel_slct == 1)
                        {
                            if (fingerR != NO_ITEM)
                            {
                                enviarMsg("dedo ja possui um anel!");
                            }
                            else
                            {
                                fingerR = rightHand;
                                rightHand = NO_ITEM;
                                enviarMsg("anel equipado no dedo da mao direita.");
                            }
                        }
                        else if (anel_slct == 2)
                        {
                            if (fingerL != NO_ITEM)
                            {
                                enviarMsg("dedo ja possui um anel!");
                            }
                            else
                            {
                                fingerL = rightHand;
                                rightHand = NO_ITEM;
                                enviarMsg("anel equipado no dedo da mao esquerda.");
                            }
                        }
                        else
                        {
                            enviarMsg("valor nao reconhecido!");
                        }
                        break;
                }
            }
            else if (opcao_escolhida == 2)
            {
                switch (itemType[leftHand])
                {
                    case NO_ITEM:
                        enviarMsg("nao prestou atencao? NAO TEM NADA AI!");
                        break;

                    case ITEM_WEAPON:
                        enviarMsg("eu falei! NAO DA PRA EQUIPAR ESSE ITEM!");
                        break;

                    case ITEM_HEAD:
                        if (head != NO_ITEM)
                        {
                            enviarMsg("nao foi possivel equipar item porque ja ha algo equipado");
                        }
                        else
                        {
                            head = leftHand;
                            leftHand = NO_ITEM;
                            enviarMsg("item equipado na cabeca.");
                        }
                        break;

                    case ITEM_CHEST:
                        if (chest != NO_ITEM)
                        {
                            enviarMsg("nao foi possivel equipar item porque ja ha algo equipado");
                        }
                        else
                        {
                            chest = leftHand;
                            leftHand = NO_ITEM;
                            enviarMsg("item equipado no peito.");
                        }
                        break;

                    case ITEM_LEGS:
                        if (legs != NO_ITEM)
                        {
                            enviarMsg("nao foi possivel equipar item porque ja ha algo equipado");
                        }
                        else
                        {
                            legs = leftHand;
                            leftHand = NO_ITEM;
                            enviarMsg("item equipado nas pernas.");
                        }
                        break;

                    case ITEM_BOOT:
                        if (feets != NO_ITEM)
                        {
                            enviarMsg("nao foi possivel equipar item porque ja ha algo equipado");
                        }
                        else
                        {
                            feets = leftHand;
                            leftHand = NO_ITEM;
                            enviarMsg("item equipado nos pes.");
                        }
                        break;

                    case ITEM_NECK:
                        if (neck != NO_ITEM)
                        {
                            enviarMsg("nao foi possivel equipar item porque ja ha algo equipado");
                        }
                        else
                        {
                            neck = leftHand;
                            leftHand = NO_ITEM;
                            enviarMsg("item equipado no pescoco.");
                        }
                        break;
                    
                    case ITEM_RING:
                        enviarMsg("selecione: [1]dedo mao direita. [2]dedo mao esquerda.");
                        int anel_slct = receberInteiro();
                        if (anel_slct == 1)
                        {
                            if(fingerR != NO_ITEM)
                            {
                                enviarMsg("dedo ja possui um anel!");
                            }
                            else
                            {
                                fingerR = leftHand;
                                leftHand = NO_ITEM;
                                enviarMsg("anel equipado no dedo da mao direita.");
                            }
                        }
                        else if (anel_slct == 2)
                        {
                            if(fingerL != NO_ITEM)
                            {
                                enviarMsg("dedo ja possui um anel!");
                            }
                            else
                            {
                                fingerL = leftHand;
                                leftHand = NO_ITEM;
                                enviarMsg("anel equipado no dedo da mao esquerda.");
                            }
                        }
                        else
                        {
                            enviarMsg("valor nao reconhecido!");
                        }
                        break;
                }
            }
            else
            {
                enviarMsg("valor nao reconhecido!");
            }
        }
    }
    else if (strcmp(commando , "!mochila") == 0)
    {
        char slot1_msg[MESSAGE_LENG] = "slot [1]:";
        char slot2_msg[MESSAGE_LENG] = "slot [2]:";
        char slot3_msg[MESSAGE_LENG] = "slot [3]:";
        char slot4_msg[MESSAGE_LENG] = "slot [4]:";
        char slot5_msg[MESSAGE_LENG] = "slot [5]:";
        char slot6_msg[MESSAGE_LENG] = "slot [6]:";
        char slot7_msg[MESSAGE_LENG] = "slot [7]:";
        char slot8_msg[MESSAGE_LENG] = "slot [8]:";
        char slot9_msg[MESSAGE_LENG] = "slot [9]:";
        char slot10_msg[MESSAGE_LENG] = "slot [10]:";
        if (bag[1] == NO_ITEM)
        {
            sprintf(slot1_msg , "%s %s" , slot1_msg , "NADA");
            enviarMsg(slot1_msg);
        }
        else
        {
            if (itensSpecification[bag[1]] == NOT_STACKABLE_ITEM)
            {
                sprintf(slot1_msg , "%s %s" , slot1_msg , itensNames[bag[1]]);
                enviarMsg(slot1_msg);
            }
            else if (itensSpecification[bag[1]] == STACKABLE_ITEM)
            {
                sprintf(slot1_msg , "%s %s quantidade: %d" , slot1_msg , itensNames[bag[1]] , quantStrg[1]);
                enviarMsg(slot1_msg);
            }
        }
        if (bag[2] == NO_ITEM)
        {
            sprintf(slot2_msg , "%s %s" , slot2_msg , "NADA");
            enviarMsg(slot2_msg);
        }
        else
        {
            if (itensSpecification[bag[2]] == NOT_STACKABLE_ITEM)
            {
                sprintf(slot2_msg , "%s %s" , slot2_msg , itensNames[bag[2]]);
                enviarMsg(slot2_msg);
            }
            else if (itensSpecification[bag[2]] == STACKABLE_ITEM)
            {
                sprintf(slot2_msg , "%s %s quantidade: %d" , slot2_msg , itensNames[bag[2]] , quantStrg[2]);
                enviarMsg(slot2_msg);
            }
        }
        if (bag[3] == NO_ITEM)
        {
            sprintf(slot3_msg , "%s %s" , slot3_msg , "NADA");
            enviarMsg(slot3_msg);
        }
        else
        {
            if (itensSpecification[bag[3]] == NOT_STACKABLE_ITEM)
            {
                sprintf(slot3_msg , "%s %s" , slot3_msg , itensNames[bag[3]]);
                enviarMsg(slot3_msg);
            }
            else if (itensSpecification[bag[3]] == STACKABLE_ITEM)
            {
                sprintf(slot3_msg , "%s %s quantidade: %d" , slot3_msg , itensNames[bag[3]] , quantStrg[3]);
                enviarMsg(slot3_msg);
            }
        }
        if (bag[4] == NO_ITEM)
        {
            sprintf(slot4_msg , "%s %s" , slot4_msg , "NADA");
            enviarMsg(slot4_msg);
        }
        else
        {
            if (itensSpecification[bag[4]] == NOT_STACKABLE_ITEM)
            {
                sprintf(slot4_msg , "%s %s" , slot4_msg , itensNames[bag[4]]);
                enviarMsg(slot4_msg);
            }
            else if (itensSpecification[bag[4]] == STACKABLE_ITEM)
            {
                sprintf(slot4_msg , "%s %s quantidade: %d" , slot4_msg , itensNames[bag[4]] , quantStrg[4]);
                enviarMsg(slot4_msg);
            }
        }
        if (bag[5] == NO_ITEM)
        {
            sprintf(slot5_msg , "%s %s" , slot5_msg , "NADA");
            enviarMsg(slot5_msg);
        }
        else
        {
            if (itensSpecification[bag[5]] == NOT_STACKABLE_ITEM)
            {
                sprintf(slot5_msg , "%s %s" , slot5_msg , itensNames[bag[5]]);
                enviarMsg(slot5_msg);
            }
            else if (itensSpecification[bag[5]] == STACKABLE_ITEM)
            {
                sprintf(slot5_msg , "%s %s quantidade: %d" , slot5_msg , itensNames[bag[5]] , quantStrg[5]);
                enviarMsg(slot5_msg);
            }
        }
        if (bag[6] == NO_ITEM)
        {
            sprintf(slot6_msg , "%s %s" , slot6_msg , "NADA");
            enviarMsg(slot6_msg);
        }
        else
        {
            if (itensSpecification[bag[6]] == NOT_STACKABLE_ITEM)
            {
                sprintf(slot6_msg , "%s %s" , slot6_msg , itensNames[bag[6]]);
                enviarMsg(slot6_msg);
            }
            else if (itensSpecification[bag[6]] == STACKABLE_ITEM)
            {
                sprintf(slot6_msg , "%s %s quantidade: %d" , slot6_msg , itensNames[bag[6]] , quantStrg[6]);
                enviarMsg(slot6_msg);
            }
        }
        if (bag[7] == NO_ITEM)
        {
            sprintf(slot7_msg , "%s %s" , slot7_msg , "NADA");
            enviarMsg(slot7_msg);
        }
        else
        {
            if (itensSpecification[bag[7]] == NOT_STACKABLE_ITEM)
            {
                sprintf(slot7_msg , "%s %s" , slot7_msg , itensNames[bag[7]]);
                enviarMsg(slot7_msg);
            }
            else if (itensSpecification[bag[7]] == STACKABLE_ITEM)
            {
                sprintf(slot7_msg , "%s %s quantidade: %d" , slot7_msg , itensNames[bag[7]] , quantStrg[7]);
                enviarMsg(slot7_msg);
            }
        }
        if (bag[8] == NO_ITEM)
        {
            sprintf(slot8_msg , "%s %s" , slot8_msg , "NADA");
            enviarMsg(slot8_msg);
        }
        else
        {
            if (itensSpecification[bag[8]] == NOT_STACKABLE_ITEM)
            {
                sprintf(slot8_msg , "%s %s" , slot8_msg , itensNames[bag[8]]);
                enviarMsg(slot8_msg);
            }
            else if (itensSpecification[bag[8]] == STACKABLE_ITEM)
            {
                sprintf(slot8_msg , "%s %s quantidade: %d" , slot8_msg , itensNames[bag[8]] , quantStrg[8]);
                enviarMsg(slot8_msg);
            }
        }
        if (bag[9] == NO_ITEM)
        {
            sprintf(slot9_msg , "%s %s" , slot9_msg , "NADA");
            enviarMsg(slot9_msg);
        }
        else
        {
            if (itensSpecification[bag[9]] == NOT_STACKABLE_ITEM)
            {
                sprintf(slot9_msg , "%s %s" , slot9_msg , itensNames[bag[9]]);
                enviarMsg(slot9_msg);
            }
            else if (itensSpecification[bag[9]] == STACKABLE_ITEM)
            {
                sprintf(slot9_msg , "%s %s quantidade: %d" , slot9_msg , itensNames[bag[9]] , quantStrg[9]);
                enviarMsg(slot9_msg);
            }
        }
        if (bag[10] == NO_ITEM)
        {
            sprintf(slot10_msg , "%s %s" , slot10_msg , "NADA");
            enviarMsg(slot10_msg);
        }
        else
        {
            if (itensSpecification[bag[10]] == NOT_STACKABLE_ITEM)
            {
                sprintf(slot10_msg , "%s %s" , slot10_msg , itensNames[bag[10]]);
                enviarMsg(slot10_msg);
            }
            else if (itensSpecification[bag[10]] == STACKABLE_ITEM)
            {
                sprintf(slot10_msg , "%s %s quantidade: %d" , slot10_msg , itensNames[bag[10]] , quantStrg[10]);
                enviarMsg(slot10_msg);
            }
        }
    }
    else enviarMsg("Comando nao reconhecido!");
}
