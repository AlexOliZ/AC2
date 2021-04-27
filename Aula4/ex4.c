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

        for(i=0 ; i<7 ; i++){
            delay(250);
            // char segment
            // LATB = LATB | segment << 8;
            switch(segment){    
                case 'a':
                    LATBbits.LATB8 = 1;
                    break;
                case 'b':
                    LATBbits.LATB9 = 1;
                    break;
                case 'c':
                    LATBbits.LATB10 = 1;
                    break;
                case 'd':
                    LATBbits.LATB11 = 1;
                    break;
                case 'e':
                    LATBbits.LATB12 = 1;
                    break;
                case 'f':
                    LATBbits.LATB13 = 1;
                    break;
                case 'g':
                    LATBbits.LATB14 = 1;
                    break;
            }
            segment++;
        }
        // meter o ponto a piscar 3 vezes antes de trocar de display
        for(i=0 ; i<3 ; i++){
            LATBbits.LATB15 = 1;
            delay(125);
            LATBbits.LATB15 = 0;
        }
        segment = 'a';
    }   
    return 1;
}