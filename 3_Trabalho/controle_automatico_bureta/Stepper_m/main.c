#include <msp430g2553.h>
#include <legacymsp430.h>

#define IN_AD BIT1
#define IN_AD_CH INCH_1
#define COIL1 BIT0
#define COIL2 BIT7
#define COIL3 BIT2
#define BTN BIT3
#define COIL4 BIT4
#define COOLER BIT6
#define COILS (COIL1 + COIL2 + COIL3 + COIL4)

#define COLORACAO 500
#define Speed_1 1200
#define Speed_2 5000
#define Speed_3 50000
#define Speed Speed_1
#define Dcycle 6
#define passo_max 200



volatile unsigned int i = 0, passos = 0, start = 0;
int Direcao = 0, flag = 0, flag1 = 1, flag2 = 1, lcd = 0;

void main (void)
{   WDTCTL = WDTPW + WDTHOLD;

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


//---------------------------------------
// Configuração Cooler
    TA0CCR1 = Speed/(100/Dcycle)-1;
    TA0CCTL0 &= ~CAP;
    TA0CCTL1 = OUTMOD_7;
//---------------------------------------

//---------------------------------------
// Configuração LDR conversor AD

    ADC10CTL0 = SREF_0 + ADC10SHT_0 + ADC10ON + ADC10IE;
    ADC10AE0 = IN_AD;
    // Com SHS_0, uma conversao sera requisitada
    // sempre que o bit ADC10SC for setado em ADC10CTL0
    ADC10CTL1 = IN_AD_CH + SHS_1 + ADC10DIV_0 + ADC10SSEL_3 + CONSEQ_2;
    ADC10CTL0 |= ENC;
//---------------------------------------

// Configuração do LCD-------------------

    InitializeLcm();
    ClearLcmScreen();

    ClearLcmScreen();
    delay_ms(100);
    LcmSetCursorPosition(0,0);
    PrintStr("PRESSIONE O BTN");
    LcmSetCursorPosition(1,0);
    PrintStr("  PARA INICIAR");
//---------------------------------------

    _BIS_SR(GIE + LPM0_bits);

  }

interrupt(TIMER0_A1_VECTOR) TA0_ISR(void)
{
    //64*64+32 contagem para uma volta completa

    if ((passos <= passo_max)&&(start)){

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

    passos++;
    if((passos>passo_max)&&(flag))
        TA0CTL = MC_0;
    }

    TA0CTL &= ~TAIFG;

    if((start)&&(flag1))
    {
        ClearLcmScreen();
        //delay_ms(100);
        LcmSetCursorPosition(0,0);
        PrintStr("   AGUARDANDO");
        LcmSetCursorPosition(1,0);
        PrintStr("    DETECCAO");
        flag1 = 0;
    }

    if((lcd)&&(flag2))
    {
        ClearLcmScreen();
       // delay_ms(100);
        LcmSetCursorPosition(0,0);
        PrintStr("PROCESSO");
        LcmSetCursorPosition(1,0);
        PrintStr("FINALIZADO");
        flag2=0;
    }

}



interrupt(ADC10_VECTOR) ADC10_ISR(void){

    //Luz fraca => trocou de cor => tensão baixa => trocar direção e zerar passos
    if(ADC10MEM < COLORACAO){
        if(!flag){
            Direcao ^= 1;     // Troca a direção
            passos = 0;
            lcd = 1;
            flag = 1;
        }

     }
    ADC10CTL0 &= ~ADC10IFG;
}


interrupt(PORT1_VECTOR) Interrupcao_P1(void)
{
    start = 1;
    flag1 = flag2 =1;
    TA0CTL = TASSEL_2 + MC_1 + ID_0 + TAIE;
    P1IFG = 0x00;
}
