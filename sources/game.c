#include <stdio.h>
#include <string.h>
#include "../headers/game.h"
#include "../headers/devchat.h"
#define BAG_SIZE 10
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
        bag[i] = 0;
        quantStrg[i] = 0;
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
    else enviarMsg("Comando nao reconhecido!");
}
