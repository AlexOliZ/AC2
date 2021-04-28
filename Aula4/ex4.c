#include <detpic32.h>
#include "delay.c"

int main(void){
    unsigned char segment = 'a';
    unsigned int counter = 0;
    unsigned int i;
    // configurar portos
    TRISDbits.TRISD5 = 0;
    TRISDbits.TRISD6 = 0;
    TRISB = TRISB & 0x00FF;

    while(1){
        LATD = LATD & 0x00FF;
        LATB = LATB & 0x00FF;

        if(counter == 1){
            // display da direita (D5)
            LATDbits.LATD5 = 1;
            LATDbits.LATD6 = 0;
            counter = 0;
        }else{
            // display da esquerda (D6)
            LATDbits.LATD5 = 0;
            LATDbits.LATD6 = 1;
            counter = 1;
        }

        for(i=0 ; i<8 ; i++){
            delay(500);
            printf("%d\n",i);
            // char segment
            // LATB = LATB | segment << 8;
            switch(i){    
                case 1:
                    LATBbits.LATB8 = 1;
                    break;
                case 2:
                    LATBbits.LATB9 = 1;
                    break;
                case 3:
                    LATBbits.LATB10 = 1;
                    break;
                case 4:
                    LATBbits.LATB11 = 1;
                    break;
                case 5:
                    LATBbits.LATB12 = 1;
                    break;
                case 6:
                    LATBbits.LATB13 = 1;
                    break;
                case 7:
                    LATBbits.LATB14 = 1;
                    break;
            }
        }
        // meter o ponto a piscar 3 vezes antes de trocar de display
        for(i=0 ; i<3 ; i++){
            delay(500);
            printf("%d\n",i);
            LATB = LATB & 0x00FF;
            delay(500);
            LATB = 0xFFFF;
        }
        segment = 'a';
    }   
    return 1;
}