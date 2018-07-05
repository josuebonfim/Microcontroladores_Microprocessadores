#include <msp430g2533.h>
#include "ishan.h"
#include "hd44780.h"

#define BTN  BIT3


float temperature=0;
void main()

{

    WDTCTL = WDTPW + WDTHOLD; // Stop watchdog timer

    //setup DCO to 1MHZ
//  BCSCTL2 = CALBC1_1MHZ;
    BCSCTL1 = CALBC1_16MHZ;
    DCOCTL = CALDCO_16MHZ;

    P1DIR &= ~BTN;
    P1REN |= BTN;
    P1OUT |= BTN;

  // P1REN |= BIT5;

 InitializeLcm();
 ClearLcmScreen();


    for(;;)
    {

    while(P1IN&BTN); //espera o botao ser pressionado
    ClearLcmScreen();
    while((P1IN & BTN) == 0); //espera soltar o botao
    delay_ms(100);
    LcmSetCursorPosition(0,0);
    PrintStr("PRESSIONE O BTN");
    LcmSetCursorPosition(1,0);
    PrintStr("  PARA INICIAR");

    while(P1IN&BTN); //espera o botao ser pressionado
    ClearLcmScreen();
    while((P1IN & BTN) == 0); //espera soltar o botao
    delay_ms(100);
    LcmSetCursorPosition(0,0);
    PrintStr("   AGUARDANDO");
    LcmSetCursorPosition(1,0);
    PrintStr("    DETECCAO");

    while(P1IN&BTN); //espera o botao ser pressionado
    ClearLcmScreen();
    while((P1IN & BTN) == 0); //espera soltar o botao
    delay_ms(100);
    LcmSetCursorPosition(0,0);
    PrintStr("    PROCESSO");
    LcmSetCursorPosition(1,0);
    PrintStr("   FINALIZADO");

    }

}
