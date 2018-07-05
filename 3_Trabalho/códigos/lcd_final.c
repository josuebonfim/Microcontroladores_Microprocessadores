/***************************************************************************************
 * Example project of "lcd16x2_msp43x" library
 *
 * Use the following pins
 * - P1.0 - P1.3    = 4 bit data line
 * - P1.6           = EN pin
 * - P1.7           = RS pin
 *
 * configuration of pins/port can be modified in the .h file
 *
 * author: Haroldo Amaral - agaelema@globo.com
 * 2017/12/28
 ***************************************************************************************/
#include <msp430.h>
#include <stdint.h>
#include "lcd16x2_msp43x.h"



#define BTN BIT3

void main(void)
{
    WDTCTL = WDTPW + WDTHOLD;
    PM5CTL0 &= ~LOCKLPM5;

    P1DIR = 0xFF;
    P1OUT = 0x00;
    P2DIR &= ~BTN;
    P2REN |= BTN;
    P2OUT |= BTN;


    while(1)
    {
        lcd16x2_Init();

        lcd16x2_SetPosition(0,0);
        lcd16x2_PrintString("Pressione BTN");

        lcd16x2_SetPosition(1,0);
        lcd16x2_PrintString("Para iniciar");

        while(P2IN&BTN);
        while((P2IN & BTN) == 0);

        lcd16x2_Init();
        lcd16x2_SetPosition(0,0);
        lcd16x2_PrintString(" abrindo bureta");


        while(P2IN&BTN);
        while((P2IN & BTN) == 0);

        lcd16x2_Init();

        lcd16x2_SetPosition(0,0);
        lcd16x2_PrintString("Ligando mistura-");

        lcd16x2_SetPosition(1,0);
        lcd16x2_PrintString("dor    magnetico");

        while(P2IN&BTN);
        while((P2IN & BTN) == 0);

        lcd16x2_Init();

        lcd16x2_SetPosition(0,0);
        lcd16x2_PrintString("   Aguardando");

        lcd16x2_SetPosition(1,0);
        lcd16x2_PrintString("    Deteccao");

        while(P2IN&BTN);
        while((P2IN & BTN) == 0);

        lcd16x2_Init();

        lcd16x2_SetPosition(0,0);
        lcd16x2_PrintString("Ponto Detectado");

        while(P2IN&BTN);
        while((P2IN & BTN) == 0);

        lcd16x2_Init();

        lcd16x2_SetPosition(0,0);
        lcd16x2_PrintString("    Processo");

        lcd16x2_SetPosition(1,0);
        lcd16x2_PrintString("   Finalizado");

        while(P2IN&BTN);
        while((P2IN & BTN) == 0);
    }
}

