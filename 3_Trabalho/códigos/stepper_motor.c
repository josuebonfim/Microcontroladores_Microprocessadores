#include <msp430g2553.h>
#include <legacymsp430.h>

#define COIL1 BIT0
#define COIL2 BIT1
#define COIL3 BIT2
#define BTN BIT3
#define COIL4 BIT4
#define COOLER BIT6
#define COILS (COIL1 + COIL2 + COIL3 + COIL4)
#define Speed_1 1000
#define Speed_2 5000
#define Speed_3 10000
#define Speed Speed_3
#define Dcycle 50

/*
    Frequências:    100Hz   20Hz    1Hz     0,5Hz
    Tloop:          5       25      500     1000
*/

volatile unsigned int i = 0;
int Direcao = 0;
volatile unsigned int count = 0;

void main (void)
{
    WDTCTL = WDTPW + WDTHOLD;

    BCSCTL1 = CALBC1_1MHZ;
    DCOCTL = CALDCO_1MHZ;

    P1DIR &= ~BTN;              // Habilita resistor de pull-up
    P1REN |= BTN;               // Habilita resistor de pull-up
    P1OUT |= BTN;               // Define estado inicial do port1

    P1DIR |= COILS;
    P1OUT &= ~COILS;

//---------------------------------------
    P1DIR |= COOLER;
    P1SEL |= COOLER;
    P1SEL2 &= ~(COOLER);
    P1OUT &= ~(COOLER);
//---------------------------------------

    P1IES |= BTN;               // Definição da borda subida/descida
    P1IE |= BTN;                // Habilitando a interrupção p/ P1.3
    P1IFG = 0x00;               // Registrador referente a flag

    TA0CTL = TACLR;
    TA0CTL = MC_0;
    TA0CCR0 = Speed-1;
    TA0CTL = TASSEL_2 + MC_1 + ID_0 + TAIE;


//---------------------------------------
    TA0CCR1 = Speed/(100/Dcycle)-1;
    TA0CCTL0 &= ~CAP;
    TA0CCTL1 = OUTMOD_7;
//---------------------------------------

    _BIS_SR(GIE + LPM0_bits);

  }

interrupt(TIMER0_A1_VECTOR) TA0_ISR(void)
{

    switch(i){
        case(0):
            P1OUT = (P1OUT|COIL1)&(~(COIL2+COIL3+COIL4));
            if (Direcao) i++;
            else i=7;
            break;
        case(1):
            P1OUT = (P1OUT|(COIL1+COIL2))&(~(COIL3+COIL4));
            if (Direcao) i++;
            else i--;
            break;
        case(2):
            P1OUT = (P1OUT|COIL2)&(~(COIL1+COIL3+COIL4));
            if (Direcao) i++;
            else i--;
            break;
        case(3):
            P1OUT = (P1OUT|(COIL2+COIL3))&(~(COIL1+COIL4));
            if (Direcao) i++;
            else i--;
            break;
        case(4):
            P1OUT = (P1OUT|COIL3)&(~(COIL1+COIL2+COIL4));
            if (Direcao) i++;
            else i--;
            break;
        case(5):
            P1OUT = (P1OUT|(COIL3+COIL4))&(~(COIL1+COIL2));
            if (Direcao) i++;
            else i--;
            break;
        case(6):
            P1OUT = (P1OUT|COIL4)&(~(COIL1+COIL2+COIL3));
            if (Direcao) i++;
            else i--;
            break;
        case(7):
            P1OUT = (P1OUT|(COIL1+COIL4))&(~(COIL2+COIL3));
            if (Direcao) i=0;
            else i--;
            break;
    }

    TA0CTL &= ~TAIFG;
}

interrupt(PORT1_VECTOR) Interrupcao_P1(void)
{
    Direcao ^= 1;     // Troca a direção
    P1IFG = 0x00;               // Zera a flag
}
//Stepper_motor.c
//Exibindo Stepper_motor.c…